#include "InventoryItemSlot.h"

#include "Single/GameInstance/LCGameInstance.h"
#include "Single/PlayerManager/PlayerManager.h"

#include "Components/Image.h"

void UInventoryItemSlot::NativeConstruct()
{
	Super::NativeConstruct();

	// 슬롯 드래깅이 시작되었을 경우
	OnSlotDragStarted.AddLambda(
		[this](USlotDragDropOperation* dragDropOp)
		{
			// 슬롯이 비어있다면 실행 취소
			if (GetItemInfo()->IsEmpty()) return;

			auto dragWidgetData = CreateSlotDragWidget();
			auto dragWidgetInstance = dragWidgetData.Get<0>();
			auto dragWidgetImage = dragWidgetData.Get<1>();

			// 드래그 시 표시되는 위젯을 설정합니다.
			dragDropOp->DefaultDragVisual = dragWidgetInstance;

			// 드래그 시 표시되는 이미지를 설정합니다.
			dragWidgetImage->SetBrushFromTexture(
				Cast<UTexture2D>(GetSlotImage()->Brush.GetResourceObject()));

			// 슬롯의 아이템 이미지 색상을 드래깅 색상으로 설정합니다.
			SetSlotColorDragging();
		});

	// 슬롯 드래깅이 취소되었을 경우
	OnSlotDragCancelled.AddLambda(
		[this](USlotDragDropOperation* dragDropOp)
		{
			// 슬롯이 비어있다면 실행 취소
			if (GetItemInfo()->IsEmpty()) return;

			// 아이템 이미지 색상을 기본 색상으로 설정합니다.
			SetSlotColorNormal();
		});

	// 슬롯 드래깅이 성공적으로 끝났을 경우
	OnSlotDragFinished.AddLambda(
		[this](USlotDragDropOperation* dragDropOp)
		{
			if (dragDropOp->DraggingSlot->GetSlotType() == ESlotType::SLT_INVENTORY)
			{
				auto originatedDragSlot = Cast<UInventoryItemSlot>(dragDropOp->DraggingSlot);

				// 슬롯이 비어있다면 실행 취소
				if (originatedDragSlot->GetItemInfo()->IsEmpty()) return;

				// 아이템 이미지 색상을 기본 색상으로 설정합니다.
				dragDropOp->DraggingSlot->SetSlotColorNormal();

				// 인벤토리 슬롯 스왑
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
