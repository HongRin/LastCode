#pragma once

#include "LastCode.h"
#include "UObject/NoExportTypes.h"
#include "Enums/InputModeType.h"

#include "PlayerStateManager.generated.h"

DECLARE_MULTICAST_DELEGATE(OnProgressbarUpdateSignature);


UCLASS()
class LASTCODE_API UPlayerStateManager : public UObject
{
	GENERATED_BODY()

public :
	OnProgressbarUpdateSignature OnUpdateHp;
	OnProgressbarUpdateSignature OnUpdateStamina;
	OnProgressbarUpdateSignature OnUpdateExp;


private:
	TSubclassOf<class UPlayerProgressBar> BP_PlayerProgressBar;
	class UPlayerProgressBar* PlayerProgressBar;

public:
	UPlayerStateManager();

public:
	void CreatePlayerStateManager(
		class UWidgetControllerWidget* widgetController,
		EInputModeType changeInputMode = EInputModeType::IM_Default, bool bShowCursor = true);

	void ClosePlayerStateManager(class UWidgetControllerWidget* widgetController);
};
