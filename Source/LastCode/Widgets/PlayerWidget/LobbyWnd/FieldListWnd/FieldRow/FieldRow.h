#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Structures/FieldInfo/FieldInfo.h"
#include "FieldRow.generated.h"

UCLASS()
class LASTCODE_API UFieldRow : public UUserWidget
{
	GENERATED_BODY()
	

private :
	UPROPERTY(meta = (BindWidget))
	class UButton* Button_Previous;

	UPROPERTY(meta = (BindWidget))
	class UButton* Button_Next;

	UPROPERTY(meta = (BindWidget))
	class UButton* Button_EnterDungeon;

	UPROPERTY(meta = (BindWidget))
	class UImage* Image_Field;

	UPROPERTY(meta = (BindWidget))
	class UImage* Image_Diffuclty;

	UPROPERTY(meta = (BindWidget))
	class UTextBlock* Text_Name;

	UPROPERTY(meta = (BindWidget))
	class UTextBlock* Text_Difficulty;

	UPROPERTY(meta = (BindWidget))
	class UTextBlock* Text_Qualification;

	UPROPERTY(meta = (BindWidget))
	class UCanvasPanel* CanvasPanel_Lock;


	UPROPERTY(meta = (BindWidgetAnim), meta = (AllowPrivateAccess = true))
	class UWidgetAnimation* DifficultyDown;

	UPROPERTY(meta = (BindWidgetAnim), meta = (AllowPrivateAccess = true))
	class UWidgetAnimation* DifficultyUp;

private :
	int32 Difficulty;
	
public :
	UFieldRow(const FObjectInitializer& ObjInitializer);

protected :
	virtual void NativeConstruct() override;

public :
	void UpdateFieldRow(FFieldInfo* fieldInfo);

private :
	void SetDifficulty();
	void SetLock(int32 unLockLevel);

private :
	UFUNCTION()
	void PreviousButtonClicked();

	UFUNCTION()
	void NextButtonClicked();
};
