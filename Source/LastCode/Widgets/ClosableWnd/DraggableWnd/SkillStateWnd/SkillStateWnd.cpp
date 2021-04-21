#include "SkillStateWnd.h"

#include "Actors/Characters/PlayerCharacter/PlayableCharacter.h"
#include "Actors/Controllers/PlayerController/PlayableController/PlayableController.h"

#include "Components/ScrollBox.h"

#include "Single/GameInstance/LCGameInstance.h"
#include "Single/PlayerManager/PlayerManager.h"

#include "Components/CanvasPanel.h"
#include "Components/CanvasPanelSlot.h"
#include "Components/TextBlock.h"

#include "Widgets/ClosableWnd/DraggableWnd/SkillStateWnd/SkillStateRow/SkillStateRow.h"

USkillStateWnd::USkillStateWnd()
{
	static ConstructorHelpers::FClassFinder<USkillStateRow> BP_SKILL_STATE_ROW(
		TEXT("WidgetBlueprint'/Game/Resources/Blueprints/Widgets/ClosableWnd/DraggableWnd/SkillStateWnd/BP_SkillStateRow.BP_SkillStateRow_C'"));
	if (BP_SKILL_STATE_ROW.Succeeded()) BP_SkillStateRow = BP_SKILL_STATE_ROW.Class;
	else UE_LOG(LogTemp, Error, TEXT("USkillStateWnd.cpp::%d::LINE:: BP_SKILL_STATE_ROW is not loaded!"), __LINE__);
}

void USkillStateWnd::NativeConstruct()
{
	Super::NativeConstruct();

	WndSize = FVector2D(500.0f, 600.0f);

	for (int i = 0; i < GetManager(UPlayerManager)->GetPlayerInfo()->SkillInfo.Num(); ++i)
	{
		if (GetManager(UPlayerManager)->GetPlayerInfo()->SkillInfo[i].SkillType == ESkillType::SKT_ACTIVE)
			ActiveSkillInfo.Add(GetManager(UPlayerManager)->GetPlayerInfo()->SkillInfo[i]);
	}

	UpdateSkillStateWnd();

	GetManager(UPlayerManager)->GetSkillState()->UpdateSkillPointEvent.AddLambda([this]() {
		UpdateSkillPointText();
		});

}

void USkillStateWnd::UpdateSkillStateWnd()
{
	UpdateSkillPointText();

	for (int i = 0; i < ActiveSkillInfo.Num(); ++i)
	{
		USkillStateRow* skillStateRow = CreateWidget<USkillStateRow>(this, BP_SkillStateRow);

		skillStateRow->UpdateSkillStateRow(ActiveSkillInfo[i]);

		ScrollBox_List->AddChild(skillStateRow);
	}
}

void USkillStateWnd::UpdateSkillPointText()
{
	Text_SkillPoint->SetText(FText::FromString(FString::FromInt(GetManager(UPlayerManager)->GetPlayerInfo()->SkillPoint)));
}

