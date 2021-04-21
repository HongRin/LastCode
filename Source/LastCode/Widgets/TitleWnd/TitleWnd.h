#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "TitleWnd.generated.h"

UCLASS()
class LASTCODE_API UTitleWnd : public UUserWidget
{
	GENERATED_BODY()

private :
	UPROPERTY(meta = (BindWidget))
	class UButton* Button_Play;

	UPROPERTY(meta = (BindWidget))
	class UButton* Button_Exit;

protected :
	virtual void NativeConstruct() override;

private :
	UFUNCTION()
	void PlayButtonClicked();

	UFUNCTION()
	void ExitButtonClicked();
};
