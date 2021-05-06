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

	// �̹� �κ��丮 â�� ����� �ִٸ� ����� �κ��丮 â�� ��ȯ�մϴ�.
	if (IsValid(InventoryWnd)) return InventoryWnd;

	// �κ��丮 â�� �����մϴ�.
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
		// �������� �߰��� �� �ִ� ���� ������ �����Ѵٸ�
		int32 addableItemCount = inventoryItemInfos[slotIndex].MaxSlotCount - inventoryItemInfos[slotIndex].ItemCount;
		if (addableItemCount > 0)
		{
			// �߰��� �� �ִ� ���� ������ �Ųٸ�, �������� �ִ��� ä��ϴ�.
			for (int32 i = 0;
				((i < addableItemCount) && newItemSlotInfo.ItemCount > 0);
				++i)
			{
				// �������� �߰��մϴ�.
				++inventoryItemInfos[slotIndex].ItemCount;

				// �߰��� �������� �����մϴ�.
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
		// ���� �߰��Ϸ��� �����۰� ������ �������� ���� ������ ã�Ҵٸ�
		if (inventoryItemInfos[i].IsSameItem(newItemSlotInfo))
		{
			// ������ ä���
			fnFillSlot(newItemSlotInfo, inventoryItemInfos, i);

			// �κ��丮 â�� �����ִٸ� �����մϴ�.
			if (IsValid(InventoryWnd))
				InventoryWnd->UpdateInventoryItemSlots();

			UE_LOG(LogTemp, Warning, TEXT("IsSameItem"));
		}
		// �� ������ ������ ã�Ҵٸ�
		else if (inventoryItemInfos[i].IsEmpty())
		{
			inventoryItemInfos[i] = newItemSlotInfo;
			inventoryItemInfos[i].ItemCount = 0;

			// ������ ä���
			fnFillSlot(newItemSlotInfo, inventoryItemInfos, i);

			// �κ��丮 â�� �����ִٸ� �����մϴ�.
			if (IsValid(InventoryWnd))
				InventoryWnd->UpdateInventoryItemSlots();

			UE_LOG(LogTemp, Warning, TEXT("IsEmpty"));
		}


		// ��� �������� �߰��ߴٸ�
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

	// ���Կ� �� �� �ִ� �ִ� ������ ����
	int32 maxSlotCount = ori->GetItemInfo()->MaxSlotCount;

	// �� �� �ϳ��� �ִ� ������� ������ �Ͼ���� �մϴ�.
	if (oriItemSlotInfo.ItemCount == maxSlotCount ||
		targetItemSlotInfo.ItemCount == maxSlotCount)
		SwapItem(ori, target);
	else
	{
		// �߰� ������ ������ ������ ����մϴ�.
		int32 addable = maxSlotCount - targetItemSlotInfo.ItemCount;

		// �ű���� �������� ������ ������ ������ �������� ū ���
		if (addable > oriItemSlotInfo.ItemCount)
			// �ű� ������ ���� �ƾ��� ������ �����մϴ�.
			addable = oriItemSlotInfo.ItemCount;

		// �������� �ű�ϴ�.
		oriItemSlotInfo.ItemCount -= addable;
		targetItemSlotInfo.ItemCount += addable;

		// �ű� �� ������ ����ִٸ�
		if (oriItemSlotInfo.ItemCount == 0)
		{
			oriItemSlotInfo.Clear();
			ori->SetItemInfo(FName());
		}

		// ���� ����
		ori->UpdateInventoryItemSlot();
		target->UpdateInventoryItemSlot();
	}
}

void UInventory::RemoveItem(int32 itemSlotIndex, int32 removeCount)
{
	auto playerInfo = GetManager(UPlayerManager)->GetPlayerInfo();
	auto playerInventoryWnd = InventoryWnd;

	TArray<FItemSlotInfo>& inventoryItemInfo = playerInfo->InventoryItemInfos;

	// ������ ������ �������� removeCount ��ŭ ���ϴ�.
	inventoryItemInfo[itemSlotIndex].ItemCount -= removeCount;

	// ������ ������ 0 ���϶�� ������ ���ϴ�.
	if (inventoryItemInfo[itemSlotIndex].ItemCount <= 0)
		inventoryItemInfo[itemSlotIndex].Clear();

	// �κ��丮 â�� �����ִٸ�
	if (IsValid(playerInventoryWnd))
		// �κ��丮 â�� ������ ���Ե��� �����մϴ�.
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
 