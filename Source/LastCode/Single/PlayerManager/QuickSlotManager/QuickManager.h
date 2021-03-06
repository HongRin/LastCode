#pragma once

#include "LastCode.h"
#include "UObject/NoExportTypes.h"
#include "Enums/InputModeType.h"

#include "QuickManager.generated.h"

DECLARE_MULTICAST_DELEGATE_OneParam(OnQuickSlotEvevtSignature, FName);
DECLARE_MULTICAST_DELEGATE_TwoParams(OnQuickSlotChangedSignature, FName, int32);

UCLASS()
class LASTCODE_API UQuickManager : public UObject
{
	GENERATED_BODY()

public :
	OnQuickSlotEvevtSignature QuickSlotEventStarted;
	OnQuickSlotChangedSignature SkillLevelUpdateEvent;
	OnQuickSlotChangedSignature ItemCountChangeEvent;

private :
	TSubclassOf<class UQuickSlotBar> BP_QuickSlotBar;

	UPROPERTY()
	class UQuickSlotBar* QuickSlotBar;

public :
	UQuickManager();

public :
	void CreateQuickSlotBar(
		class UWidgetControllerWidget* widgetController,
		EInputModeType changeInputMode = EInputModeType::IM_Default, bool bShowCursor = true);

	void ReleaseQuickSlotBar();

public :
	UFUNCTION()
	void QuickSlotEventExecution(struct FKey key);

};
