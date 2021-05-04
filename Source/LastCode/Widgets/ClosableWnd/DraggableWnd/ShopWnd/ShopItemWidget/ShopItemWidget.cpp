#include "ShopItemWidget.h"

#include "Widgets/ClosableWnd/DraggableWnd/InventoryWnd/ItemSlot/ItemSlot.h"
#include "Widgets/ClosableWnd/DraggableWnd/InventoryWnd/InventoryWnd.h"
#include "Widgets/ClosableWnd/DraggableWnd/ShopWnd/ShopWnd.h"
#include "Widgets/ClosableWnd/DraggableWnd/ShopWnd/TradeWnd/TradeWnd.h"

#include "Widgets/ClosableWnd/DraggableWnd/InventoryWnd/ItemSlot/InventoryItemSlot.h"

#include "Single/GameInstance/LCGameInstance.h"
#include "Single/PlayerManager/PlayerManager.h"

#include "Components/TextBlock.h"

void UShopItemWidget::NativeConstruct()
{
	Super::NativeConstruct();


}

void UShopItemWidget::UpdateSaleItem(FItemInfo* itemInfo, UShopWnd* shopWnd)
{
	ShopWnd = shopWnd;

	BP_ItemSlot->InitializeSlot(ESlotType::SLT_ITME, itemInfo->ItemCode, ESkillType::SKT_ITEM);
	
	BP_ItemSlot->UpdateItemImage();
	BP_ItemSlot->SetSlotItemCount(0);

	Text_Name->SetText(itemInfo->ItemName);
	Text_Silver->SetText(FText::FromString(FString::FromInt(itemInfo->Price)));
	
}

FReply UShopItemWidget::NativeOnMouseButtonDoubleClick(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent)
{
	// 왼쪽 더블 클릭이 이루어졌다면
	if (InMouseEvent.GetEffectingButton() == EKeys::LeftMouseButton)
		// 아이템 구매
		BuyItem();

	return Super::NativeOnMouseButtonDoubleClick(InGeometry, InMouseEvent);
}

void UShopItemWidget::BuyItem()
{
	auto tradeWnd = ShopWnd->CreateTradeWnd(BP_ItemSlot, true);


	if (!IsValid(tradeWnd)) return;

	tradeWnd->OnTradeButtonClickedEvent.AddLambda(
		[this](UTradeWnd* tradeWnd)
		{
			// 입력 값이 잘못 되었을 경우
			if (tradeWnd->IsInputTextEmpty() || tradeWnd->GetInputTradeCount() == 0) return;

			auto itemInfo = tradeWnd->GetConnectedItemSlot()->GetItemInfo();
			FString itemName = itemInfo->ItemName.ToString();
			FString tradeItemCount = FString::FromInt(tradeWnd->GetInputTradeCount());

			FString contextString;

			// 인벤토리에 추가시킬 아이템 정보를 생성합니다.
			FItemSlotInfo newItemSlotInfo(itemInfo->ItemCode, tradeWnd->GetInputTradeCount(),
				((itemInfo->ItemType == EItemType::Equipment) ? 1 : itemInfo->MaxSlotCount));

			// 인벤토리에 아이템을 추가합니다.
			auto playerInventory = GetManager(UPlayerManager)->GetInventory();
			playerInventory->AddItem(newItemSlotInfo);

			// 소지금 감소
			int32 price = tradeWnd->GetInputTradeCount() * itemInfo->Price;
			GetManager(UPlayerManager)->GetPlayerInfo()->Silver -= price;

			// 인벤토리 창의 은화 갱신
			auto InventoryWnd = playerInventory->GetInventoryWnd();
			if (IsValid(InventoryWnd)) InventoryWnd->UpdateSilver();

			tradeWnd->OnCancelButtonClicked();
		}
	);
}