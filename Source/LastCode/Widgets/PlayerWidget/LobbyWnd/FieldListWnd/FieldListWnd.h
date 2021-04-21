#pragma once

#include "LastCode.h"
#include "Blueprint/UserWidget.h"
#include "FieldListWnd.generated.h"

UCLASS()
class LASTCODE_API UFieldListWnd : public UUserWidget
{
	GENERATED_BODY()
	
private:
	UPROPERTY(meta = (BindWidget))
	class UScrollBox* ScrollBox_List;
	
	UPROPERTY(meta = (BindWidget))
	class UButton* Button_Previous;

	UPROPERTY(meta = (BindWidget))
	class UButton* Button_Next;

	float bNextButton;
	float bScrollable;
	float CurrentOffset;
	float NextOffset;

public :
	UFieldListWnd(const FObjectInitializer& ObjInitializer);

protected :
	virtual void NativeConstruct() override;

	virtual void NativeTick(const FGeometry& MyGeometry, float inDeltaTime) override;
	
private :
	void SetScroll(float time);

private :
	UFUNCTION()
	void PreviousButtonClicked();

	UFUNCTION()
	void NextButtonClicked();

}; 
