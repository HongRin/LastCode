#include "Inventory.h"

#include "Widgets/WidgetControllerWidget/WidgetControllerWidget.h"

#include "Widgets/ClosableWnd/DraggableWnd/InventoryWnd/ItemSlot/InventoryItemSlot.h"
#include "Widgets/ClosableWnd/DraggableWnd/InventoryWnd/InventoryWnd.h"


#include "Single/GameInstance/LCGameInstance.h"
#include "Single/PlayerManager/PlayerManager.h"

UInventory::UInventory()
{
    static ConstructorHelpers::FClassFinder<UInventoryWnd> BP_INVENTORY_WND(
        TEXT("WidgetBlueprint'/Game/Resources/Blueprints/Widgets/ClosableWnd/DraggableWnd/Inventory/BP_InventoryWnd.BP_InventoryWnd_C'"));
    if (BP_INVENTORY_WND.Succeeded()) BP_InventoryWnd = BP_INVENTORY_WND.Class;
}

UInventoryWnd* UInventory::CreateInventoryWnd(UWidgetControllerWidget* widgetController, EInputModeType changeInputMode, bool bShowCursor)
{

	// 이미 인벤토리 창이 띄워져 있다면 띄워진 인벤토리 창을 반환합니다.
	if (IsValid(InventoryWnd)) return InventoryWnd;

	// 인벤토리 창을 생성합니다.
	InventoryWnd = Cast<UInventoryWnd>(
		widgetController->CreateWnd(BP_InventoryWnd, true, changeInputMode, bShowCursor));
	
	InventoryWnd->OnWndClosedEvent.AddLambda(
		[this](class UClosableWnd* closableWnd)
		{ InventoryWnd = nullptr; });


	return InventoryWnd;
}

void UInventory::CloseInventoryWnd()
{
	if (IsValid(InventoryWnd))
	{
		InventoryWnd->CloseThisWnd();
		InventoryWnd = nullptr;
	}
}

void UInventory::ToggleInventoryWnd(UWidgetControllerWidget* widgetController)
{
	if (IsValid(InventoryWnd))
		CloseInventoryWnd();
	else CreateInventoryWnd(widgetController, EInputModeType::IM_GameAndUI, true);
}

FItemSlotInfo* UInventory::GetItemSlotInfo(int32 slotIndex) const
{
	return &GetManager(UPlayerManager)->GetPlayerInfo()->InventoryItemInfos[slotIndex];
}

void UInventory::SwapItem(UInventoryItemSlot* first, UInventoryItemSlot* second)
{
	auto playerInfo = GetManager(UPlayerManager)->GetPlayerInfo();
	TArray<FItemSlotInfo>& inventoryItemInfo = playerInfo->InventoryItemInfos;

	auto tempItemInfo = inventoryItemInfo[first->GetItemSlotIndex()];

	inventoryItemInfo[first->GetItemSlotIndex()] = inventoryItemInfo[second->GetItemSlotIndex()];
	inventoryItemInfo[second->GetItemSlotIndex()] = tempItemInfo;

	first->SetItemInfo(inventoryItemInfo[first->GetItemSlotIndex()].ItemCode);
	second->SetItemInfo(inventoryItemInfo[second->GetItemSlotIndex()].ItemCode);

	first->UpdateInventoryItemSlot();

	second->UpdateInventoryItemSlot();
}

void UInventory::RemoveItem(int32 itemSlotIndex, int32 removeCount)
{
	auto playerInfo = GetManager(UPlayerManager)->GetPlayerInfo();
	auto playerInventoryWnd = InventoryWnd;

	TArray<FItemSlotInfo>& inventoryItemInfo = playerInfo->InventoryItemInfos;

	// 지정한 슬롯의 아이템을 removeCount 만큼 뺍니다.
	inventoryItemInfo[itemSlotIndex].ItemCount -= removeCount;

	// 아이템 개수가 0 이하라면 슬롯을 비웁니다.
	if (inventoryItemInfo[itemSlotIndex].ItemCount <= 0)
		inventoryItemInfo[itemSlotIndex].Clear();

	if (OnInventorySlotChanged.IsBound()) OnInventorySlotChanged.Broadcast();
}
 