#include "ShopWnd.h"

#include "Actors/Controllers/PlayerController/PlayableController/PlayableController.h"

#include "Structures/ItemInfo/ItemInfo.h"

#include "ShopItemWidget/ShopItemWidget.h"
#include "TradeWnd/TradeWnd.h"
#include "Widgets/WidgetControllerWidget/WidgetControllerWidget.h"
#include "Widgets/ClosableWnd/DraggableWnd/InventoryWnd/InventoryWnd.h"
#include "Widgets/ClosableWnd/DraggableWnd/InventoryWnd/ItemSlot/InventoryItemSlot.h"

#include "Single/GameInstance/LCGameInstance.h"
#include "Single/PlayerManager/PlayerManager.h"

#include "Components/GridPanel.h"
#include "Components/CanvasPanel.h"
#include "Components/CanvasPanelSlot.h"

UShopWnd::UShopWnd(const FObjectInitializer& ObjInitializer) :
	Super(ObjInitializer)
{
	static ConstructorHelpers::FObjectFinder<UDataTable> DT_SALE_ITEM_INFO(
		TEXT("DataTable'/Game/Resources/DataTable/DT_ItemInfo.DT_ItemInfo'"));
	if (DT_SALE_ITEM_INFO.Succeeded()) DT_SaleItemInfo = DT_SALE_ITEM_INFO.Object;

	static ConstructorHelpers::FClassFinder<UShopItemWidget> BP_SHOP_ITEM_WIDGET(
		TEXT("WidgetBlueprint'/Game/Resources/Blueprints/Widgets/ClosableWnd/DraggableWnd/Shop/BP_ShopItemWidget.BP_ShopItemWidget_C'"));
	if (BP_SHOP_ITEM_WIDGET.Succeeded()) BP_ShopItemWidget = BP_SHOP_ITEM_WIDGET.Class;

	static ConstructorHelpers::FClassFinder<UTradeWnd> BP_TRADE_WND(
		TEXT("WidgetBlueprint'/Game/Resources/Blueprints/Widgets/ClosableWnd/DraggableWnd/Shop/BP_TradeWnd.BP_TradeWnd_C'"));
	if (BP_TRADE_WND.Succeeded()) BP_TradeWnd = BP_TRADE_WND.Class;
}

void UShopWnd::NativeConstruct()
{
	Super::NativeConstruct();

	WndSize = FVector2D(600.0f, 600.0f);

	InitializeSaleItem();
}

void UShopWnd::InitializeSaleItem()
{
	FString contextString;
	TArray<FItemInfo*> saleItemInfo;
	DT_SaleItemInfo->GetAllRows<FItemInfo>(contextString, saleItemInfo);

	const int maxColumnCount = 2;
	int currentColumnCount = 0;

	for (int i = 0; i < saleItemInfo.Num(); ++i)
	{
		if (saleItemInfo[i]->bSaleItem == true)
		{
			UShopItemWidget* shopItemWidget = CreateWidget<UShopItemWidget>(this, BP_ShopItemWidget);
			GridPanel_SaleList->AddChild(shopItemWidget);
			shopItemWidget->UpdateSaleItem(saleItemInfo[i], this);
			UWidgetControllerWidget::SortGridPanelElem(shopItemWidget, maxColumnCount, currentColumnCount);
		}
	}

	FloatingInventoryWnd();
}

void UShopWnd::SaleItem(class UInventoryWnd* inventoryWnd, UItemSlot* itemSlot)
{
	auto tradeWnd = CreateTradeWnd(itemSlot, false);


	if (!IsValid(tradeWnd)) return;

	tradeWnd->OnTradeButtonClickedEvent.AddLambda(
		[this, inventoryWnd](UTradeWnd* tradeWnd)
		{
			auto inventorySlot = Cast<UInventoryItemSlot>(tradeWnd->GetConnectedItemSlot());
			int32 inputCount = tradeWnd->GetInputTradeCount();
			int32 itemPrice = inventorySlot->GetItemInfo()->Price * inputCount;


			// 입력 값이 잘못 되었거나, 입력된 개수가 0인 경우
			if (tradeWnd->IsInputTextEmpty() || inputCount == 0) return;

			// 아이템 판매
			// 아이템 이름을 얻습니다.
			FString itemName = inventorySlot->GetItemInfo()->ItemName.ToString();

			// 판매 개수를 얻습니다.
			FString tradeItemCount = FString::FromInt(tradeWnd->GetInputTradeCount());

			// 아이템 제거
			GetManager(UPlayerManager)->GetInventory()->RemoveItem(
				inventorySlot->GetItemSlotIndex(), inputCount);

			// 은화 획득
			GetManager(UPlayerManager)->GetPlayerInfo()->Silver += itemPrice;

			// 인벤토리 창 은화 갱신
			inventoryWnd->UpdateSilver();

			tradeWnd->OnCancelButtonClicked();
		}
	);
}

UTradeWnd* UShopWnd::CreateTradeWnd(UItemSlot* connectedItemSlot, bool bSaleItem)
{
	if (IsValid(TradeWnd)) return nullptr;
	if (connectedItemSlot->GetItemInfo()->IsEmpty()) return nullptr;

	TradeWnd = CreateWidget<UTradeWnd>(this, BP_TradeWnd);

	CanvasPanel_Trade->AddChild(TradeWnd);

	Cast<UCanvasPanelSlot>(TradeWnd->Slot)->SetSize(FVector2D(300.0f, 200.0f));
	Cast<UCanvasPanelSlot>(TradeWnd->Slot)->SetAnchors(FAnchors(0.5f, 0.5f, 0.5f, 0.5f));
	Cast<UCanvasPanelSlot>(TradeWnd->Slot)->SetAlignment(FVector2D(0.5f, 0.5f));

	// 교환 창 초기화
	TradeWnd->InitializeTradeWnd(connectedItemSlot, bSaleItem, this);

	return TradeWnd;
}

void UShopWnd::CloseTradeWnd()
{
	TradeWnd->RemoveFromParent();
	TradeWnd = nullptr;
}

void UShopWnd::FloatingInventoryWnd()
{
	auto widgetController = GetManager(UPlayerManager)->GetPlayableController()->GetWidgetControllerWidget();

	// 인벤토리 창을 생성합니다.
	auto playerInventoryWnd = GetManager(UPlayerManager)->GetInventory()->CreateInventoryWnd(
		widgetController, EInputModeType::IM_Default, true);

	// Npc 상점 창의 절반 크기를 얻습니다.
	FVector2D ShopWndHalfSize = GetWndSize() * 0.5f;

	// npc 상점 창 위치를 얻습니다.
	FVector2D ShopWndPos = GetCanvasPanelSlot()->GetPosition();

	// 인벤토리 창의 절반 크기를 얻습니다.
	FVector2D playerInventoryWndHalfSize = playerInventoryWnd->GetWndSize() * 0.5f;

	// 인벤토리 창의 위치를 계산합니다.
	FVector2D playerInventoryWndPos =
		ShopWndPos + ((ShopWndHalfSize + playerInventoryWndHalfSize) * FVector2D(1.0f, 0.0f));

	// 인벤토리 창과 상점 창의 높이를 맞춥니다.
	playerInventoryWndPos.Y += playerInventoryWndHalfSize.Y - ShopWndHalfSize.Y;

	// 인벤토리 창의 위치를 설정합니다.
	playerInventoryWnd->GetCanvasPanelSlot()->SetPosition(playerInventoryWndPos);

	// 상점 창이 닫힐 때 인벤토리 창도 닫히도록 합니다.
	OnWndClosedEvent.AddLambda([this](class UClosableWnd* closableWnd)
		{ GetManager(UPlayerManager)->GetInventory()->CloseInventoryWnd(); });

	for (auto slot : playerInventoryWnd->GetItemSlots())
	{
		slot->OnMouseRightButtonClicked.AddLambda(
			[this, slot, playerInventoryWnd](ESlotType itemSlotType)
			{	if (IsValid(TradeWnd)) return;
				SaleItem(playerInventoryWnd, slot); });
	}
}
