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


			// �Է� ���� �߸� �Ǿ��ų�, �Էµ� ������ 0�� ���
			if (tradeWnd->IsInputTextEmpty() || inputCount == 0) return;

			// ������ �Ǹ�
			// ������ �̸��� ����ϴ�.
			FString itemName = inventorySlot->GetItemInfo()->ItemName.ToString();

			// �Ǹ� ������ ����ϴ�.
			FString tradeItemCount = FString::FromInt(tradeWnd->GetInputTradeCount());

			// ������ ����
			GetManager(UPlayerManager)->GetInventory()->RemoveItem(
				inventorySlot->GetItemSlotIndex(), inputCount);

			// ��ȭ ȹ��
			GetManager(UPlayerManager)->GetPlayerInfo()->Silver += itemPrice;

			// �κ��丮 â ��ȭ ����
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

	// ��ȯ â �ʱ�ȭ
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

	// �κ��丮 â�� �����մϴ�.
	auto playerInventoryWnd = GetManager(UPlayerManager)->GetInventory()->CreateInventoryWnd(
		widgetController, EInputModeType::IM_Default, true);

	// Npc ���� â�� ���� ũ�⸦ ����ϴ�.
	FVector2D ShopWndHalfSize = GetWndSize() * 0.5f;

	// npc ���� â ��ġ�� ����ϴ�.
	FVector2D ShopWndPos = GetCanvasPanelSlot()->GetPosition();

	// �κ��丮 â�� ���� ũ�⸦ ����ϴ�.
	FVector2D playerInventoryWndHalfSize = playerInventoryWnd->GetWndSize() * 0.5f;

	// �κ��丮 â�� ��ġ�� ����մϴ�.
	FVector2D playerInventoryWndPos =
		ShopWndPos + ((ShopWndHalfSize + playerInventoryWndHalfSize) * FVector2D(1.0f, 0.0f));

	// �κ��丮 â�� ���� â�� ���̸� ����ϴ�.
	playerInventoryWndPos.Y += playerInventoryWndHalfSize.Y - ShopWndHalfSize.Y;

	// �κ��丮 â�� ��ġ�� �����մϴ�.
	playerInventoryWnd->GetCanvasPanelSlot()->SetPosition(playerInventoryWndPos);

	// ���� â�� ���� �� �κ��丮 â�� �������� �մϴ�.
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
