#pragma once

#include "LastCode.h"
#include "Blueprint/UserWidget.h"
#include "FieldListWnd.generated.h"

UCLASS()
class LASTCODE_API UFieldListWnd : public UUserWidget
{
	GENERATED_BODY()
	
private :
	TSubclassOf<class UFieldRow> BP_FieldRow;

	class UDataTable* DT_FieldInfo;

private:
	UPROPERTY(meta = (BindWidget))
	class UScrollBox* ScrollBox_List;

	UPROPERTY(meta = (BindWidget))
	class UCanvasPanel* CanvasPanel_Help;
	
	UPROPERTY(meta = (BindWidget))
	class UButton* Button_Previous;

	UPROPERTY(meta = (BindWidget))
	class UButton* Button_Next;

	UPROPERTY(meta = (BindWidget))
	class UButton* Button_Help;

	float CurrentOffset;
	float NextOffset;

public :
	UFieldListWnd(const FObjectInitializer& ObjInitializer);

protected :
	virtual void NativeConstruct() override;

	virtual void NativeTick(const FGeometry& MyGeometry, float inDeltaTime) override;
	
private :
	void SetScroll(float time);
	void InitializeFieldListWnd();

private :
	UFUNCTION()
	void PreviousButtonClicked();

	UFUNCTION()
	void NextButtonClicked();

	UFUNCTION()
	void HelpButtonHovered();

	UFUNCTION()
	void HelpButtonOnUnhovered();
};
