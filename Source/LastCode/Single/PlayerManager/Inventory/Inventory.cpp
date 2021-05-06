#include "Inventory.h"

#include "Actors/Characters/PlayerCharacter/PlayableCharacter.h"
#include "Components/SkillController/SkillControllerComponent.h"

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

int32 UInventory::GetSlotIndexByCode(FName code) const
{
	for (int i = 0; i < GetManager(UPlayerManager)->GetPlayerInfo()->InventoryItemInfos.Num(); ++i)
	{
		if (GetManager(UPlayerManager)->GetPlayerInfo()->InventoryItemInfos[i].ItemCode == code)
		{
			return i;
		}
	}

	return 0;
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

bool UInventory::AddItem(FItemSlotInfo& newItemSlotInfo)
{
	int32 addCount = newItemSlotInfo.ItemCount;

	UE_LOG(LogTemp, Warning, TEXT("AddItem"));

	Action(fnFillSlot, (FItemSlotInfo&, TArray<FItemSlotInfo>&, int32)) =
		[](FItemSlotInfo& newItemSlotInfo, TArray<FItemSlotInfo>& inventoryItemInfos, int32 slotIndex)
	{
		// 아이템을 추가할 수 있는 여유 공간이 존재한다면
		int32 addableItemCount = inventoryItemInfos[slotIndex].MaxSlotCount - inventoryItemInfos[slotIndex].ItemCount;
		if (addableItemCount > 0)
		{
			// 추가할 수 있는 여유 공간을 매꾸며, 아이템을 최대한 채웁니다.
			for (int32 i = 0;
				((i < addableItemCount) && newItemSlotInfo.ItemCount > 0);
				++i)
			{
				// 아이템을 추가합니다.
				++inventoryItemInfos[slotIndex].ItemCount;

				// 추가한 아이템을 제외합니다.
				--newItemSlotInfo.ItemCount;

				UE_LOG(LogTemp, Warning, TEXT("fnFillSlot"));
			}
		}
	};

	auto playerInfo = GetManager(UPlayerManager)->GetPlayerInfo();
	TArray<FItemSlotInfo>& inventoryItemInfos = playerInfo->InventoryItemInfos;

	if (newItemSlotInfo.ItemCount <= 0) return true;

	for (int32 i = 0; i < playerInfo->InventorySlotCount; ++i)
	{
		// 만약 추가하려는 아이템과 동일한 아이템을 갖는 슬롯을 찾았다면
		if (inventoryItemInfos[i].IsSameItem(newItemSlotInfo))
		{
			// 아이템 채우기
			fnFillSlot(newItemSlotInfo, inventoryItemInfos, i);

			// 인벤토리 창이 열려있다면 갱신합니다.
			if (IsValid(InventoryWnd))
				InventoryWnd->UpdateInventoryItemSlots();

			UE_LOG(LogTemp, Warning, TEXT("IsSameItem"));
		}
		// 빈 아이템 슬롯을 찾았다면
		else if (inventoryItemInfos[i].IsEmpty())
		{
			inventoryItemInfos[i] = newItemSlotInfo;
			inventoryItemInfos[i].ItemCount = 0;

			// 아이템 채우기
			fnFillSlot(newItemSlotInfo, inventoryItemInfos, i);

			// 인벤토리 창이 열려있다면 갱신합니다.
			if (IsValid(InventoryWnd))
				InventoryWnd->UpdateInventoryItemSlots();

			UE_LOG(LogTemp, Warning, TEXT("IsEmpty"));
		}


		// 모든 아이템을 추가했다면
		if (newItemSlotInfo.ItemCount == 0)
		{
			UpdateSkillItemCount(newItemSlotInfo.ItemCode, addCount);
			return true;
		}
	}

	return false;
}

void UInventory::MergeItem(UInventoryItemSlot* ori, UInventoryItemSlot* target)
{
	auto playerInfo = GetManager(UPlayerManager)->GetPlayerInfo();

	FItemSlotInfo& oriItemSlotInfo = playerInfo->InventoryItemInfos[ori->GetItemSlotIndex()];
	FItemSlotInfo& targetItemSlotInfo = playerInfo->InventoryItemInfos[target->GetItemSlotIndex()];

	// 슬롯에 들어갈 수 있는 최대 아이템 개수
	int32 maxSlotCount = ori->GetItemInfo()->MaxSlotCount;

	// 둘 중 하나라도 최대 개수라면 스왑이 일어나도록 합니다.
	if (oriItemSlotInfo.ItemCount == maxSlotCount ||
		targetItemSlotInfo.ItemCount == maxSlotCount)
		SwapItem(ori, target);
	else
	{
		// 추가 가능한 아이템 개수를 계산합니다.
		int32 addable = maxSlotCount - targetItemSlotInfo.ItemCount;

		// 옮기려는 아이템의 개수가 슬롯의 아이템 개수보다 큰 경우
		if (addable > oriItemSlotInfo.ItemCount)
			// 옮길 개수를 슬롯 아아템 개수로 설정합니다.
			addable = oriItemSlotInfo.ItemCount;

		// 아이템을 옮깁니다.
		oriItemSlotInfo.ItemCount -= addable;
		targetItemSlotInfo.ItemCount += addable;

		// 옮긴 후 슬롯이 비어있다면
		if (oriItemSlotInfo.ItemCount == 0)
		{
			oriItemSlotInfo.Clear();
			ori->SetItemInfo(FName());
		}

		// 슬롯 갱신
		ori->UpdateInventoryItemSlot();
		target->UpdateInventoryItemSlot();
	}
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

	// 인벤토리 창이 열려있다면
	if (IsValid(playerInventoryWnd))
		// 인벤토리 창의 아이템 슬롯들을 갱신합니다.
		playerInventoryWnd->UpdateInventoryItemSlots();

	UpdateSkillItemCount(inventoryItemInfo[itemSlotIndex].ItemCode, -removeCount);

}

void UInventory::UpdateSkillItemCount(FName itemCode, int32 Count)
{

	for (int i = 0; i < GetManager(UPlayerManager)->GetPlayerInfo()->SkillInfo.Num(); ++i)
	{
		if (GetManager(UPlayerManager)->GetPlayerInfo()->SkillInfo[i].SkillCode == itemCode)
		{
			GetManager(UPlayerManager)->GetPlayerInfo()->SkillInfo[i].SkillLevel += Count;

			if (GetManager(UPlayerManager)->GetQuickManager()->ItemCountChangeEvent.IsBound())
				GetManager(UPlayerManager)->GetQuickManager()->ItemCountChangeEvent.Broadcast(itemCode, Count);
		}
	}
}
 