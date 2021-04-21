#pragma once

#include "LastCode.h"
#include "Blueprint/UserWidget.h"
#include "SkillStateRow.generated.h"

UCLASS()
class LASTCODE_API USkillStateRow : public UUserWidget
{
	GENERATED_BODY()
	
private :
	class UDataTable* DT_SkillReinforceInfo;

private :
	UPROPERTY(meta = (BindWidget))
	class USkillSlot* BP_SkillSlot;

	UPROPERTY(meta = (BindWidget))
	class UTextBlock* Text_Name;

	UPROPERTY(meta = (BindWidget))
	class UTextBlock* Text_SkillLevel;

	UPROPERTY(meta = (BindWidget))
	class UButton* Button_Plus;

	UPROPERTY(meta = (BindWidget))
	class UBackgroundBlur* ActivationSkill;

	UPROPERTY(meta = (BindWidget))
	class UTextBlock* Text_Qualification;

	struct FSkillInfo CurrrentSkillInfo;
	struct FSkillReinforceInfo* NextSkillInfo;

private :
	class USkillStateWnd* SkillStateWnd;

public :
	USkillStateRow(const FObjectInitializer& ObjInitializer);

protected:
	void NativeConstruct() override;

private :
	void InitialzieSkillReinforeInfo(struct FSkillInfo activeSkillInfo);

	void ReinforceSkill();

public :
	void UpdateSkillStateRow(struct FSkillInfo activeSkillInfo);

	void SetActivation(FSkillInfo activeSkillInfo);

private :
	UFUNCTION()
	void OnPlusButtonClicked();
};
