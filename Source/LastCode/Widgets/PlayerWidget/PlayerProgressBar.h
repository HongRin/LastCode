#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "PlayerProgressBar.generated.h"

UCLASS()
class LASTCODE_API UPlayerProgressBar : public UUserWidget
{
	GENERATED_BODY()
	
private:
	UPROPERTY(meta = (BindWidget))
		class UProgressBar* ProgressBar_Hp;

	UPROPERTY(meta = (BindWidget))
		class UProgressBar* ProgressBar_Stamina;

	UPROPERTY(meta = (BindWidget))
		class UProgressBar* ProgressBar_Exp;

	UPROPERTY(meta = (BindWidget))
		class UTextBlock* Text_Hp;

	UPROPERTY(meta = (BindWidget))
		class UTextBlock* Text_Stamina;

	UPROPERTY(meta = (BindWidget))
		class UTextBlock* Text_Exp;

	class APlayableCharacter* PlayableCharacter;

protected:
	virtual void NativeConstruct() override;
};
