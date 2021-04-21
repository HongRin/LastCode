#pragma once

#include "LastCode.h"
#include "Blueprint/UserWidget.h"
#include "QuickSlotBar.generated.h"

UCLASS()
class LASTCODE_API UQuickSlotBar : public UUserWidget
{
	GENERATED_BODY()

private :
	TSubclassOf<class UQuickSlot> BP_QuickSlot;

private :
	UPROPERTY(meta = (BindWidget))
	class UHorizontalBox* HorizontalBox_QuickSlotList;

public :
	UQuickSlotBar(const FObjectInitializer& ObjInitializer);

protected :
	virtual void NativeConstruct() override;

public :
	void InitializeQuickSlots();
	
};
