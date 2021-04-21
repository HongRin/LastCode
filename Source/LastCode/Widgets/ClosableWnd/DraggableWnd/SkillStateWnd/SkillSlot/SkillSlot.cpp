#include "SkillSlot.h"
#include "Blueprint/WidgetBlueprintLibrary.h"

#include "Actors/Controllers/PlayerController/PlayableController/PlayableController.h"

#include "Components/Image.h"
#include "Components/TextBlock.h"

#include "Single/GameInstance/LCGameInstance.h"
#include "Single/PlayerManager/PlayerManager.h"

#include "Widgets/ClosableWnd/DraggableWnd/SkillStateWnd/SkillStateRow/SkillStateRow.h"

#include "Blueprint/WidgetLayoutLibrary.h"


USkillSlot::USkillSlot(const FObjectInitializer& ObjInitializer) :
	Super(ObjInitializer)
{

}

void USkillSlot::NativeConstruct()
{
	Super::NativeConstruct();

}

void USkillSlot::UpdateSkillSlot(FSkillInfo activeSkillInfo)
{
	InitializeSlot(ESlotType::SLT_SKILL, activeSkillInfo.SkillCode, ESkillType::SKT_ACTIVE);

	SkillInfo = activeSkillInfo;

	ULCGameInstance* gameInst = Cast<ULCGameInstance>(GetGameInstance());

	// 아이템 이미지를 로드합니다.
	UTexture2D* itemImage =
		Cast<UTexture2D>(GetManager(FStreamableManager)->LoadSynchronous(activeSkillInfo.ImageSprite));

	// 이미지를 설정합니다.
	GetSlotImage()->SetBrushFromTexture(itemImage);

}

void USkillSlot::InitializeSlot(ESlotType slotType, FName inCode, ESkillType skillType)
{
	Super::InitializeSlot(slotType, inCode, skillType);

	OnSlotDragStarted.AddLambda(
		[this](class USlotDragDropOperation* op) {
			{
				if (SkillInfo.SkillLevel == 0) return;

				auto widgetData = CreateSlotDragWidget();
				auto dragWidget = widgetData.Get<0>();
				auto dragImage = widgetData.Get<1>();

				op->DefaultDragVisual = dragWidget;
				dragImage->SetBrushFromTexture(Cast<UTexture2D>(GetSlotImage()->Brush.GetResourceObject()));
			}
	});

	OnSlotDragFinished.AddLambda(
		[this](USlotDragDropOperation* Op)
		{
			Op->DraggingSlot->SetSlotColorNormal();
		});
}



