#include "SkillStateRow.h"
#include "Components/TextBlock.h"
#include "Components/Button.h"
#include "Components/BackgroundBlur.h"

#include "Single/GameInstance/LCGameInstance.h"
#include "Single/PlayerManager/PlayerManager.h"

#include "Widgets/ClosableWnd/DraggableWnd/SkillStateWnd/SkillSlot/SkillSlot.h"
#include "Components/CanvasPanel.h"
#include "Components/CanvasPanelSlot.h"

USkillStateRow::USkillStateRow(const FObjectInitializer& ObjInitializer) :
	Super(ObjInitializer)
{
	static ConstructorHelpers::FObjectFinder<UDataTable> DT_REINFORCE_SKILL_INFO(
		TEXT("DataTable'/Game/Resources/DataTable/DT_SkillReinforceInfo.DT_SkillReinforceInfo'"));
	if (DT_REINFORCE_SKILL_INFO.Succeeded()) DT_SkillReinforceInfo = DT_REINFORCE_SKILL_INFO.Object;
	else UE_LOG(LogTemp, Error, TEXT("USelectClassWnd.cpp::%d::LINE:: DT_REINFORCE_SKILL_INFO is not loaded !"), __LINE__);
}

void USkillStateRow::NativeConstruct()
{
	Super::NativeConstruct();

	Button_Plus->OnClicked.AddDynamic(this, &USkillStateRow::OnPlusButtonClicked);
}

void USkillStateRow::InitialzieSkillReinforeInfo(FSkillInfo activeSkillInfo)
{
	FString contextString;
	TArray<FSkillReinforceInfo*> skillreinforceInfo;
	DT_SkillReinforceInfo->GetAllRows(contextString, skillreinforceInfo);

	for (int i = 0; i < skillreinforceInfo.Num(); ++i)
	{
		if (skillreinforceInfo[i]->CharacterCode == activeSkillInfo.CharacterCode &&
			skillreinforceInfo[i]->CurrentSkillCode == activeSkillInfo.ReinforceSkillCode)
		{
			NextSkillInfo = skillreinforceInfo[i];
		}
	}

	CurrrentSkillInfo = activeSkillInfo;
}

void USkillStateRow::ReinforceSkill()
{
	for (int i = 0; i < GetManager(UPlayerManager)->GetPlayerInfo()->SkillInfo.Num(); ++i)
	{
		if (NextSkillInfo->SkillCode == GetManager(UPlayerManager)->GetPlayerInfo()->SkillInfo[i].SkillCode)
		{
			GetManager(UPlayerManager)->GetPlayerInfo()->SkillInfo[i].SkillLevel = NextSkillInfo->SkillLevel;
			GetManager(UPlayerManager)->GetPlayerInfo()->SkillInfo[i].ActivationCharacterLevel = NextSkillInfo->ActivationCharacterLevel;
			GetManager(UPlayerManager)->GetPlayerInfo()->SkillInfo[i].SkillValue = NextSkillInfo->SkillValue;
			GetManager(UPlayerManager)->GetPlayerInfo()->SkillInfo[i].SkillStamina = NextSkillInfo->SkillStamina;
			GetManager(UPlayerManager)->GetPlayerInfo()->SkillInfo[i].SKillCoolDownTime = NextSkillInfo->SKillCoolDownTime;
			GetManager(UPlayerManager)->GetPlayerInfo()->SkillInfo[i].bMaximumLevel = NextSkillInfo->bMaximumLevel;
			GetManager(UPlayerManager)->GetPlayerInfo()->SkillInfo[i].ReinforceSkillCode = NextSkillInfo->NextSkillCode;
			UpdateSkillStateRow(GetManager(UPlayerManager)->GetPlayerInfo()->SkillInfo[i]);
			if (GetManager(UPlayerManager)->GetQuickManager()->SkillLevelUpdateEvent.IsBound())
				GetManager(UPlayerManager)->GetQuickManager()->SkillLevelUpdateEvent.Broadcast(
					GetManager(UPlayerManager)->GetPlayerInfo()->SkillInfo[i].SkillCode,
					GetManager(UPlayerManager)->GetPlayerInfo()->SkillInfo[i].SkillLevel);
		}
	}
}



void USkillStateRow::UpdateSkillStateRow(FSkillInfo activeSkillInfo)
{
	InitialzieSkillReinforeInfo(activeSkillInfo);

	Text_Name->SetText(CurrrentSkillInfo.SkillName);

	BP_SkillSlot->UpdateSkillSlot(activeSkillInfo);

	BP_SkillSlot->SetSkillStateRow(this);

	Text_SkillLevel->SetText(FText::FromString(FString::FromInt(CurrrentSkillInfo.SkillLevel)));

	SetActivation(CurrrentSkillInfo);
}

void USkillStateRow::SetActivation(FSkillInfo activeSkillInfo)
{
	if (activeSkillInfo.ActivationCharacterLevel > GetManager(UPlayerManager)->GetPlayerInfo()->Level)
	{
		int32 QualificationLevel = activeSkillInfo.ActivationCharacterLevel;
		Text_Qualification->SetText(FText::FromString(FString::Printf(TEXT("Requires level %d of the player"), QualificationLevel)));
		ActivationSkill->SetVisibility(ESlateVisibility::Visible);
	}
	else if (activeSkillInfo.bMaximumLevel)
	{
		Text_Qualification->SetText(FText::FromString(FString(TEXT("SkillLevel Max"))));
		ActivationSkill->SetVisibility(ESlateVisibility::Visible);
	}
	else if (GetManager(UPlayerManager)->GetPlayerInfo()->SkillPoint <= 0)
	{
		Button_Plus->SetColorAndOpacity(FLinearColor(0.05f, 0.05f, 0.05f, 1.0f));
		Button_Plus->SetVisibility(ESlateVisibility::HitTestInvisible);
	}
	else
	{
		Button_Plus->SetColorAndOpacity(FLinearColor(1.0f, 1.0f, 1.0f, 1.0f));
		Button_Plus->SetVisibility(ESlateVisibility::Visible);
		ActivationSkill->SetVisibility(ESlateVisibility::Hidden);
	}
}

void USkillStateRow::OnPlusButtonClicked()
{
	ReinforceSkill();

	--(GetManager(UPlayerManager)->GetPlayerInfo()->SkillPoint);

	if(GetManager(UPlayerManager)->GetSkillState()->UpdateSkillPointEvent.IsBound())
		GetManager(UPlayerManager)->GetSkillState()->UpdateSkillPointEvent.Broadcast();



	SetActivation(CurrrentSkillInfo);
}
