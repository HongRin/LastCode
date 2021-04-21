#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "SkillDetailWnd.generated.h"

UCLASS()
class LASTCODE_API USkillDetailWnd : public UUserWidget
{
	GENERATED_BODY()

private :
	UPROPERTY(meta = (BindWidget))
	class UImage* Image_SkillSprite;

	UPROPERTY(meta = (BindWidget))
	class UTextBlock* Text_SkillLevel;

	UPROPERTY(meta = (BindWidget))
	class UTextBlock* Text_Name;

	UPROPERTY(meta = (BindWidget))
	class UTextBlock* Text_Damage;

	UPROPERTY(meta = (BindWidget))
	class UTextBlock* Text_CoolDownTime;

	UPROPERTY(meta = (BindWidget))
	class UTextBlock* Text_Stamina;

	UPROPERTY(meta = (BindWidget))
	class UTextBlock* Text_Explain;

protected :
	virtual void NativeConstruct() override;

public :
	void UpdateSkillDetailWnd(FName skillCode);
	
};
