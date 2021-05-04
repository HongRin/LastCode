#include "InventoryItemSlot.h"

#include "Single/GameInstance/LCGameInstance.h"
#include "Single/PlayerManager/PlayerManager.h"

#include "Components/Image.h"

void UInventoryItemSlot::NativeConstruct()
{
	Super::NativeConstruct();

	// ���� �巡���� ���۵Ǿ��� ���
	OnSlotDragStarted.AddLambda(
		[this](USlotDragDropOperation* dragDropOp)
		{
			// ������ ����ִٸ� ���� ���
			if (GetItemInfo()->IsEmpty()) return;

			auto dragWidgetData = CreateSlotDragWidget();
			auto dragWidgetInstance = dragWidgetData.Get<0>();
			auto dragWidgetImage = dragWidgetData.Get<1>();

			// �巡�� �� ǥ�õǴ� ������ �����մϴ�.
			dragDropOp->DefaultDragVisual = dragWidgetInstance;

			// �巡�� �� ǥ�õǴ� �̹����� �����մϴ�.
			dragWidgetImage->SetBrushFromTexture(
				Cast<UTexture2D>(GetSlotImage()->Brush.GetResourceObject()));

			// ������ ������ �̹��� ������ �巡�� �������� �����մϴ�.
			SetSlotColorDragging();
		});

	// ���� �巡���� ��ҵǾ��� ���
	OnSlotDragCancelled.AddLambda(
		[this](USlotDragDropOperation* dragDropOp)
		{
			// ������ ����ִٸ� ���� ���
			if (GetItemInfo()->IsEmpty()) return;

			// ������ �̹��� ������ �⺻ �������� �����մϴ�.
			SetSlotColorNormal();
		});

	// ���� �巡���� ���������� ������ ���
	OnSlotDragFinished.AddLambda(
		[this](USlotDragDropOperation* dragDropOp)
		{
			if (dragDropOp->DraggingSlot->GetSlotType() == ESlotType::SLT_INVENTORY)
			{
				auto originatedDragSlot = Cast<UInventoryItemSlot>(dragDropOp->DraggingSlot);

				// ������ ����ִٸ� ���� ���
				if (originatedDragSlot->GetItemInfo()->IsEmpty()) return;

				// ������ �̹��� ������ �⺻ �������� �����մϴ�.
				dragDropOp->DraggingSlot->SetSlotColorNormal();

				// �κ��丮 ���� ����
				GetManager(UPlayerManager)->GetInventory()->SwapItem(originatedDragSlot, this);
			}
		});
}

void UInventoryItemSlot::InitializeItemSlot(ESlotType slotType, FName itemCode, ESkillType skillType, int32 itemSlotIndex)
{
	Super::InitializeSlot(slotType, itemCode, skillType);

	ItemSlotIndex = itemSlotIndex;

	UpdateItemCountText();
}

void UInventoryItemSlot::UpdateInventoryItemSlot()
{
	UpdateItemImage();
	UpdateItemCountText();
	InitializeSlot(SlotType, GetManager(UPlayerManager)->GetInventory()->GetItemSlotInfo(ItemSlotIndex)->ItemCode, SkillType);
}

void UInventoryItemSlot::UpdateItemCountText()
{
	auto itemSlotInfo = GetManager(UPlayerManager)->GetInventory()->GetItemSlotInfo(ItemSlotIndex);

	SetSlotItemCount(itemSlotInfo->ItemCount);
}
