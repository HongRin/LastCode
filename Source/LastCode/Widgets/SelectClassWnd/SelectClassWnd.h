#pragma once

#include "LastCode.h"
#include "Blueprint/UserWidget.h"
#include "SelectClassWnd.generated.h"

UCLASS()
class LASTCODE_API USelectClassWnd : public UUserWidget
{
	GENERATED_BODY()

private :
	class UDataTable* DT_SCWndRowInfo;
	class UDataTable* DT_SkillInfo;
	class UDataTable* DT_SkillReinforceInfo;


private :
	UPROPERTY(meta = (BindWidget))
	class UTextBlock* Text_Name;

	UPROPERTY(meta = (BindWidget))
	class UTextBlock* Text_Weapon;

	UPROPERTY(meta = (BindWidget))
	class UTextBlock* Text_Explain;

	UPROPERTY(meta = (BindWidget))
	class UProgressBar* ProgressBar_Atk;

	UPROPERTY(meta = (BindWidget))
	class UProgressBar* ProgressBar_Hp;

	UPROPERTY(meta = (BindWidget))
	class UProgressBar* ProgressBar_Mobility;

	UPROPERTY(meta = (BindWidget))
	class UButton* Button_BattleSide;
	
	UPROPERTY(meta = (BindWidget))
	class UButton* Button_Sniper;

	UPROPERTY(meta = (BindWidget))
	class UButton* Button_Idle;

	UPROPERTY(meta = (BindWidget))
	class UButton* Button_Walk;

	UPROPERTY(meta = (BindWidget))
	class UButton* Button_Run;

	UPROPERTY(meta = (BindWidget))
	class UButton* Button_Start;

	UPROPERTY()
	class APreviewCharacter* PreviewCharacter;

	UPROPERTY(meta = (BindWidgetAnim), meta = (AllowPrivateAccess = true))
	class UWidgetAnimation* Sniper;

	UPROPERTY(meta = (BindWidgetAnim), meta = (AllowPrivateAccess = true))
	class UWidgetAnimation* BattleSide;

public :
	USelectClassWnd(const FObjectInitializer& ObjInitializer);

protected:
	virtual void NativeConstruct() override;

public:
	void SetPreviewCharacter(class APreviewCharacter* previewCharacter);

private :
	void UpdateRow();
	void PlayerSkillSetting();

private :
	UFUNCTION()
	void BattleSideIconClicked();
	UFUNCTION()
	void SniperIconClicked();
	UFUNCTION()
	void IdleButtonClicked();
	UFUNCTION()
	void WalkButtonClicked();
	UFUNCTION()
	void RunButtonClicked();
	UFUNCTION()
	void StartButtonClicked();
};
