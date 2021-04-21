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
	// �κ��丮 â�� �����մϴ�.
	class USkillStateWnd* CreateSkillStateWnd(
		class UWidgetControllerWidget* widgetController,
		EInputModeType changeInputMode = EInputModeType::IM_Default, bool bShowCursor = true);

	// �κ��丮 â�� �ݽ��ϴ�.
	void CloseSkillStaeWnd();

	// �κ��丮 â�� ����մϴ�.
	void ToggleSkillStateWnd(class UWidgetControllerWidget* widgetController);
};
