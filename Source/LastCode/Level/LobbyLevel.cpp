#include "LobbyLevel.h"

#include "Actors/Controllers/PlayerController/PlayableController/PlayableController.h"

#include "Single/GameInstance/LCGameInstance.h"
#include "Single/PlayerManager/PlayerManager.h"

#include "Widgets/PlayerWidget/LobbyWnd/LobbyWnd.h"
#include "Widgets/WidgetControllerWidget/WidgetControllerWidget.h"

#include "Components/CanvasPanel.h"
#include "Components/CanvasPanelSlot.h"

ALobbyLevel::ALobbyLevel()
{
	static ConstructorHelpers::FClassFinder<ULobbyWnd> BP_LOBBY_WND(
		TEXT("WidgetBlueprint'/Game/Resources/Blueprints/Widgets/PlayerWidget/BP_PlayerLoobyWnd.BP_PlayerLoobyWnd_C'"));
	if (BP_LOBBY_WND.Succeeded()) BP_LobbyWnd = BP_LOBBY_WND.Class;
}

void ALobbyLevel::BeginPlay()
{
	Super::BeginPlay();

	if (!IsValid(LobbyWnd))
	{
		UWidgetControllerWidget* widgetController =
			GetManager(UPlayerManager)->GetPlayableController()->GetWidgetControllerWidget();
		LobbyWnd = CreateWidget<ULobbyWnd>(widgetController, BP_LobbyWnd);
		widgetController->AddChildWidget(LobbyWnd, EInputModeType::IM_GameAndUI, true, 400.0f, 1080.0f);
		Cast<UCanvasPanelSlot>(LobbyWnd->Slot)->SetAnchors(FAnchors(1.0f, 1.0f, 1.0f, 1.0f));
		Cast<UCanvasPanelSlot>(LobbyWnd->Slot)->SetAlignment(FVector2D(1.0f, 1.2f));
	}


}
