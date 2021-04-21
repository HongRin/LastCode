#include "BaseSlot.h"
#include "Blueprint/WidgetBlueprintLibrary.h"

#include "Components/Image.h"

#include "Blueprint/WidgetLayoutLibrary.h"
#include "Components/CanvasPanelSlot.h"

#include "Widgets/ClosableWnd/DraggableWnd/SkillStateWnd/SkillDetailWnd/SkillDetailWnd.h"
#include "Widgets/ClosableWnd/DraggableWnd/InventoryWnd/ItemDetailWnd/ItemDetailWnd.h"

#include "Components/CanvasPanel.h"
#include "Components/CanvasPanelSlot.h"

UBaseSlot::UBaseSlot(const FObjectInitializer& ObjectInitializer) :
	Super(ObjectInitializer)
{
	static ConstructorHelpers::FClassFinder<UUserWidget> BP_SLOT_DRAG_IMAGE(
		TEXT("WidgetBlueprint'/Game/Resources/Blueprints/Widgets/ClosableWnd/DraggableWnd/DragSlot/BP_SlotDragImage.BP_SlotDragImage_C'"));
	if (BP_SLOT_DRAG_IMAGE.Succeeded()) BP_SlotDragImage = BP_SLOT_DRAG_IMAGE.Class;

	static ConstructorHelpers::FObjectFinder<UTexture2D> T_NULL(
		TEXT("Texture2D'/Game/Resources/UIImage/Icon/T_NULL.T_NULL'"));
	if (T_NULL.Succeeded()) T_Null = T_NULL.Object;

	static ConstructorHelpers::FClassFinder<USkillDetailWnd> BP_SKILL_DETAIL_WND(
		TEXT("WidgetBlueprint'/Game/Resources/Blueprints/Widgets/ClosableWnd/DraggableWnd/SkillStateWnd/BP_SkillDetailWnd.BP_SkillDetailWnd_C'"));
	if (BP_SKILL_DETAIL_WND.Succeeded()) BP_SkillDetailWnd = BP_SKILL_DETAIL_WND.Class;
	else UE_LOG(LogTemp, Error, TEXT("USkillSlot.cpp::%d::LINE:: BP_SKILL_DETAIL_WND is not loaded!"), __LINE__);

	static ConstructorHelpers::FClassFinder<UItemDetailWnd> BP_ITEM_DETAIL_WND(
		TEXT("WidgetBlueprint'/Game/Resources/Blueprints/Widgets/ClosableWnd/DraggableWnd/Inventory/ItemDetailWnd/BP_ItemDetailWnd.BP_ItemDetailWnd_C'"));
	if (BP_ITEM_DETAIL_WND.Succeeded()) BP_ItemDetailWnd = BP_ITEM_DETAIL_WND.Class;
	else UE_LOG(LogTemp, Error, TEXT("USkillSlot.cpp::%d::LINE:: BP_ITEM_DETAIL_WND is not loaded!"), __LINE__);

}

void UBaseSlot::NativeOnMouseEnter(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent)
{
	Super::NativeOnMouseEnter(InGeometry, InMouseEvent);

	// 슬롯을 마우스 겹침 상태로 표시합니다.
	ShowSlotHorverState();

	if (SkillType == ESkillType::SKT_ACTIVE)
	{
		if (!IsValid(SkillDetailWnd) && !InCode.IsNone())
		{
			SkillDetailWnd = CreateWidget<USkillDetailWnd>(this, BP_SkillDetailWnd);
			CanvasPanel_Detail->AddChild(SkillDetailWnd);
			SkillDetailWnd->UpdateSkillDetailWnd(InCode);
			Cast<UCanvasPanelSlot>(SkillDetailWnd->Slot)->SetSize(FVector2D(463.0f, 600.0f));
			if (SlotType == ESlotType::SLT_SKILL)
			{
				Cast<UCanvasPanelSlot>(SkillDetailWnd->Slot)->SetAnchors(FAnchors(0.0f, 0.0f, 0.0f, 0.0f));
				Cast<UCanvasPanelSlot>(SkillDetailWnd->Slot)->SetAlignment(FVector2D(-0.11f, -0.07f));
			}
			else if (SlotType == ESlotType::SLT_QUICK)
			{
				Cast<UCanvasPanelSlot>(SkillDetailWnd->Slot)->SetAnchors(FAnchors(0.0f, 0.0f, 0.0f, 0.0f));
				Cast<UCanvasPanelSlot>(SkillDetailWnd->Slot)->SetAlignment(FVector2D(-0.04f, 0.93f));
			}
		}
	}
	else if (SkillType == ESkillType::SKT_ITEM)
	{
		if (!IsValid(ItemDetailWnd) && !InCode.IsNone())
		{
			ItemDetailWnd = CreateWidget<UItemDetailWnd>(this, BP_ItemDetailWnd);
			CanvasPanel_Detail->AddChild(ItemDetailWnd);
			ItemDetailWnd->UpdateItemDetailWnd(InCode);
			Cast<UCanvasPanelSlot>(ItemDetailWnd->Slot)->SetSize(FVector2D(463.0f, 350.0f));
			if (SlotType == ESlotType::SLT_QUICK)
			{
				Cast<UCanvasPanelSlot>(ItemDetailWnd->Slot)->SetAnchors(FAnchors(0.0f, 0.0f, 0.0f, 0.0f));
				Cast<UCanvasPanelSlot>(ItemDetailWnd->Slot)->SetAlignment(FVector2D(-0.04f, 0.93f));
			}
			else
			{
				Cast<UCanvasPanelSlot>(ItemDetailWnd->Slot)->SetAnchors(FAnchors(0.0f, 0.0f, 0.0f, 0.0f));
				Cast<UCanvasPanelSlot>(ItemDetailWnd->Slot)->SetAlignment(FVector2D(-0.11f, -0.07f));
			}
		}
	}
}

void UBaseSlot::NativeOnMouseLeave(const FPointerEvent& InMouseEvent)
{
	Super::NativeOnMouseLeave(InMouseEvent);

	if (SkillType == ESkillType::SKT_ACTIVE)
	{
		if (IsValid(SkillDetailWnd))
		{
			CanvasPanel_Detail->RemoveChild(SkillDetailWnd);
			SkillDetailWnd = nullptr;
		}
	}

	if (SkillType == ESkillType::SKT_ITEM)
	{
		if (IsValid(ItemDetailWnd))
		{
			CanvasPanel_Detail->RemoveChild(ItemDetailWnd);
			ItemDetailWnd = nullptr;
		}
	}

	// 슬롯을 기본 상태로 표시합니다.
	ShowSlotNormalState();
	

}

FReply UBaseSlot::NativeOnMouseButtonDown(
	const FGeometry& InGeometry, const FPointerEvent& InMouseEvent)
{
	auto retVal = Super::NativeOnMouseButtonDown(InGeometry, InMouseEvent);


	// 입력된 마우스 버튼을 확인합니다.
	if (InMouseEvent.GetEffectingButton() == EKeys::LeftMouseButton)
	{
		// 슬롯을 눌림 상태로 표시합니다.
		ShowSlotPressedState();

		// 왼쪽 클릭 이벤트를 발생시킵니다.
		if (OnMouseLeftButtonClicked.IsBound())
			OnMouseLeftButtonClicked.Broadcast(SlotType);

		bDroppable = false;

		// 드래그 앤 드롭 작업을 시작하며, 작업 결과를 반환합니다.
		return UWidgetBlueprintLibrary::DetectDragIfPressed(
			InMouseEvent, this, EKeys::LeftMouseButton).NativeReply;
		/// - PointerEvent : 마우스 입력 이벤트를 전달합니다.
		/// - WidgetDetectingDrag : 드래그를 감지할 객체
		/// - DragKey : 드래그를 감지할 때 사용될 키
	
	}
	else if (InMouseEvent.GetEffectingButton() == EKeys::RightMouseButton)
	{
		// 오른쪽 클릭 이벤트를 발생시킵니다.
		if (OnMouseRightButtonClicked.IsBound())
			OnMouseRightButtonClicked.Broadcast(SlotType);
	}
	return retVal;
}

FReply UBaseSlot::NativeOnMouseButtonUp(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent)
{
	ShowSlotNormalState();
	return Super::NativeOnMouseButtonUp(InGeometry, InMouseEvent);
}

FReply UBaseSlot::NativeOnMouseButtonDoubleClick(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent)
{
	auto retVal = Super::NativeOnMouseButtonDoubleClick(InGeometry, InMouseEvent);

	if (InMouseEvent.GetEffectingButton() == EKeys::LeftMouseButton)
	{
		// 슬롯을 기본 상태로 표시합니다.
		ShowSlotNormalState();

		// 더블 클릭 이벤트 발생
		if (OnMouseLeftButtonDBClicked.IsBound())
			OnMouseLeftButtonDBClicked.Broadcast(SlotType);
	}

	return retVal;
}

void UBaseSlot::NativeOnDragDetected(
	const FGeometry& InGeometry,
	const FPointerEvent& InMouseEvent,
	UDragDropOperation*& OutOperation)
{
	Super::NativeOnDragDetected(InGeometry, InMouseEvent, OutOperation);

	// 슬롯을 기본 상태로 표시합니다.
	ShowSlotNormalState();

	// 드래그 드랍 작업 객체를 생성합니다.
	USlotDragDropOperation* dragDropOperation = Cast<USlotDragDropOperation>(
		UWidgetBlueprintLibrary::CreateDragDropOperation(USlotDragDropOperation::StaticClass()));

	// 드래그 시작 위젯을 설정합니다.
	dragDropOperation->DraggingSlot = this;

	// 슬롯 드래그 시작 이벤트 발생
	if (OnSlotDragStarted.IsBound())
		OnSlotDragStarted.Broadcast(dragDropOperation);



	// 출력용 매개 변수에 드래그 앤 드롭 작업 객체를 설정합니다.
	OutOperation = dragDropOperation;
}

void UBaseSlot::NativeOnDragCancelled(
	const FDragDropEvent& InDragDropEvent,
	UDragDropOperation* InOperation)
{
	Super::NativeOnDragCancelled(InDragDropEvent, InOperation);

	if (Cast<USlotDragDropOperation>(InOperation)->DraggingSlot->bDroppable) return;

	// 슬롯 드래그 취소 이벤트 발생
	if (OnSlotDragCancelled.IsBound())
		OnSlotDragCancelled.Broadcast(Cast<USlotDragDropOperation>(InOperation));
}

bool UBaseSlot::NativeOnDrop(
	const FGeometry& InGeometry,
	const FDragDropEvent& InDragDropEvent,
	UDragDropOperation* InOperation)
{
	auto retVal = Super::NativeOnDrop(InGeometry, InDragDropEvent, InOperation);

	// 슬롯 드래그 끝 이벤트 발생
	if (OnSlotDragFinished.IsBound())
		OnSlotDragFinished.Broadcast(Cast<USlotDragDropOperation>(InOperation));

	Cast<USlotDragDropOperation>(InOperation)->DraggingSlot->bDroppable = true;

	return retVal;
}

void UBaseSlot::InitializeSlot(ESlotType slotType, FName inCode, ESkillType skillType)
{
	SlotType = slotType;
	InCode = inCode;
	SkillType = skillType;
}

void UBaseSlot::SlotImageEmpty()
{
	Image_Slot->SetBrushFromTexture(T_Null);
}




void UBaseSlot::ShowSlotNormalState()
{
	GetSlotBackgroundImage()->SetColorAndOpacity(FLinearColor(1.0f, 1.0f, 1.0f));
}

void UBaseSlot::ShowSlotHorverState()
{
	GetSlotBackgroundImage()->SetColorAndOpacity(FLinearColor(1.0f, 0.8f, 0.3f));
}

void UBaseSlot::ShowSlotPressedState()
{
	GetSlotBackgroundImage()->SetColorAndOpacity(FLinearColor(0.2f, 0.2f, 0.2f));
}

void UBaseSlot::SetSlotColorNormal()
{
	GetSlotImage()->SetBrushTintColor(FLinearColor(1.0f, 1.0f, 1.0f));
}

void UBaseSlot::SetSlotColorDragging()
{
	GetSlotImage()->SetBrushTintColor(FLinearColor(0.2f, 0.2f, 0.2f));
}

TTuple<UUserWidget*, UImage*> UBaseSlot::CreateSlotDragWidget()
{
	// 드래그 앤 드랍 시 보여질 위젯을 생성합니다.
	auto slotDragWidget = CreateWidget<UUserWidget>(this, BP_SlotDragImage);
	auto image_Drag = Cast<UImage>(slotDragWidget->GetWidgetFromName(TEXT("Image_Drag")));

	return MakeTuple(slotDragWidget, image_Drag);
}


