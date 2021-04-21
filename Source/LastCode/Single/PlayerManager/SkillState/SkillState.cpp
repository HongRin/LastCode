#include "SkillState.h"

#include "Widgets/WidgetControllerWidget/WidgetControllerWidget.h"

#include "Single/GameInstance/LCGameInstance.h"
#include "Single/PlayerManager/PlayerManager.h"

#include "Widgets/ClosableWnd/DraggableWnd/SkillStateWnd/SkillStateWnd.h"

USkillState::USkillState()
{
    static ConstructorHelpers::FClassFinder<USkillStateWnd> BP_SKILL_STATE_WND(
        TEXT("WidgetBlueprint'/Game/Resources/Blueprints/Widgets/ClosableWnd/DraggableWnd/SkillStateWnd/BP_SkillStateWnd.BP_SkillStateWnd_C'"));
    if (BP_SKILL_STATE_WND.Succeeded()) BP_SkillStateWnd = BP_SKILL_STATE_WND.Class;
    else UE_LOG(LogTemp, Error, TEXT("USkillState.cpp::%d::LINE:: BP_SKILL_STATE_WND is not loaded !"), __LINE__);
}

USkillStateWnd* USkillState::CreateSkillStateWnd(UWidgetControllerWidget* widgetController, EInputModeType changeInputMode, bool bShowCursor)
{
    // �̹� ��ųâ�� ����� �ִٸ� ��ųâ�� ��ȯ�մϴ�.
    if (IsValid(SkillStateWnd)) return SkillStateWnd;

    SkillStateWnd = Cast<USkillStateWnd>(widgetController->CreateWnd(BP_SkillStateWnd, true, changeInputMode, bShowCursor));
    SkillStateWnd->OnWndClosedEvent.AddLambda([this](class UClosableWnd* closableWnd) {SkillStateWnd = nullptr;});

    return SkillStateWnd;
}

void USkillState::CloseSkillStaeWnd()
{
    if (IsValid(SkillStateWnd))
    {
        SkillStateWnd->CloseThisWnd();
        SkillStateWnd = nullptr;
    }
}

void USkillState::ToggleSkillStateWnd(UWidgetControllerWidget* widgetController)
{
    if (IsValid(SkillStateWnd)) CloseSkillStaeWnd();
    else CreateSkillStateWnd(widgetController, EInputModeType::IM_GameAndUI, true);

}
