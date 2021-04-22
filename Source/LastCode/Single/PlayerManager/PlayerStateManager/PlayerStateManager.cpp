#include "PlayerStateManager.h"

#include "Widgets/PlayerWidget/PlayerProgressBar.h"
#include "Widgets/WidgetControllerWidget/WidgetControllerWidget.h"

#include "Components/SkillController/SkillControllerComponent.h"
#include "Components/CanvasPanel.h"
#include "Components/CanvasPanelSlot.h"

#include "Single/GameInstance/LCGameInstance.h"
#include "Single/PlayerManager/PlayerManager.h"

UPlayerStateManager::UPlayerStateManager()
{
	static ConstructorHelpers::FClassFinder<UPlayerProgressBar> BP_PLAYER_PROGRESS_BAR(
		TEXT("WidgetBlueprint'/Game/Resources/Blueprints/Widgets/PlayerWidget/BP_PlayerProgressBar.BP_PlayerProgressBar_C'"));
	if (BP_PLAYER_PROGRESS_BAR.Succeeded()) BP_PlayerProgressBar = BP_PLAYER_PROGRESS_BAR.Class;
	else UE_LOG(LogTemp, Error, TEXT("UQuickManager.cpp::%d::LINE:: BP_PLAYER_PROGRESS_BAR is not loaed! "), __LINE__);
}

void UPlayerStateManager::CreatePlayerStateManager(UWidgetControllerWidget* widgetController, EInputModeType changeInputMode, bool bShowCursor)
{
	if (IsValid(PlayerProgressBar))
	{
		PlayerProgressBar->RemoveFromParent();
		UE_LOG(LogTemp, Warning, TEXT("PlayerProgressBar is valid"));
	}
	else
	{
		PlayerProgressBar = CreateWidget<UPlayerProgressBar>(widgetController, BP_PlayerProgressBar);
		UE_LOG(LogTemp, Warning, TEXT("PlayerProgressBar is not valid"));
	}
	
	widgetController->AddChildWidget(PlayerProgressBar, EInputModeType::IM_GameOnly, false, 1000.0f, 200.0f);
	Cast<UCanvasPanelSlot>(PlayerProgressBar->Slot)->SetAnchors(FAnchors(0.5f, 0.5f, 0.5f, 0.5f));
	Cast<UCanvasPanelSlot>(PlayerProgressBar->Slot)->SetAlignment(FVector2D(0.5f, -1.29f));

	if (OnUpdateHp.IsBound()) OnUpdateHp.Broadcast();
	if (OnUpdateStamina.IsBound()) OnUpdateStamina.Broadcast();
}
