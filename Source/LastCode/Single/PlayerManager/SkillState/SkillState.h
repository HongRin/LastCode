#pragma once

#include "LastCode.h"
#include "UObject/NoExportTypes.h"

#include "Enums/InputModeType.h"

#include "SkillState.generated.h"

DECLARE_MULTICAST_DELEGATE(OnSkillUpdateSignature);

UCLASS()
class LASTCODE_API USkillState : public UObject
{

	GENERATED_BODY()

public :
	OnSkillUpdateSignature UpdateSkillPointEvent;

private :
	TSubclassOf<class USkillStateWnd> BP_SkillStateWnd;

private :
	UPROPERTY()
	class USkillStateWnd* SkillStateWnd;

public :
	USkillState();

public:
	// 인벤토리 창을 생성합니다.
	class USkillStateWnd* CreateSkillStateWnd(
		class UWidgetControllerWidget* widgetController,
		EInputModeType changeInputMode = EInputModeType::IM_Default, bool bShowCursor = true);

	// 인벤토리 창을 닫습니다.
	void CloseSkillStaeWnd();

	// 인벤토리 창을 토글합니다.
	void ToggleSkillStateWnd(class UWidgetControllerWidget* widgetController);
};
