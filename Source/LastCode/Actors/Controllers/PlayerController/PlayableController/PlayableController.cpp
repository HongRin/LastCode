#include "PlayableController.h"

#include "Components/WndToggler/WndTogglerComponent.h"

#include "Single/GameInstance/LCGameInstance.h"
#include "Single/PlayerManager/PlayerManager.h"

#include "Widgets/WidgetControllerWidget/WidgetControllerWidget.h"

void APlayableController::SetupInputComponent()
{
	Super::SetupInputComponent();

	InputComponent->BindAction(TEXT("OpenSkillStateWnd"), EInputEvent::IE_Pressed,
		GetWndToggler(), &UWndTogglerComponent::ToggleWnd<USkillState>);

	InputComponent->BindAction(TEXT("OpenInventoryWnd"), EInputEvent::IE_Pressed,
		GetWndToggler(), &UWndTogglerComponent::ToggleWnd<UInventory>);

	InputComponent->BindAxis(TEXT("MouseX"), this, &APlayableController::InputMouseX);
	InputComponent->BindAxis(TEXT("MouseY"), this, &APlayableController::InputMouseY);

}

void APlayableController::OnPossess(APawn* aPawn)
{
	Super::OnPossess(aPawn);

	RegisterToggleEvent();

	GetManager(UPlayerManager)->GetPlayerStateManager()->CreatePlayerStateManager(GetWidgetControllerWidget());
	GetManager(UPlayerManager)->GetQuickManager()->CreateQuickSlotBar(GetWidgetControllerWidget());

}
void APlayableController::OnUnPossess()
{
	Super::OnUnPossess();

	GetManager(UPlayerManager)->GetQuickManager()->ReleaseQuickSlotBar();
}

void APlayableController::RegisterToggleEvent()
{
#pragma region USkillState
	FToggleEvent skillstateWndToggleEvent;
	skillstateWndToggleEvent.BindLambda(
		[this]() {
			GetManager(UPlayerManager)->GetSkillState()->
				ToggleSkillStateWnd(GetWidgetControllerWidget());
		});
	GetWndToggler()->RegisterToggleEvent<USkillState>(skillstateWndToggleEvent);
#pragma endregion

#pragma region UPlayerInventory
	FToggleEvent InventoryWndToggleEvent;
	InventoryWndToggleEvent.BindLambda(
		[this]() {
			GetManager(UPlayerManager)->GetInventory()->
				ToggleInventoryWnd(GetWidgetControllerWidget());
		});
	GetWndToggler()->RegisterToggleEvent<UInventory>(InventoryWndToggleEvent);
#pragma endregion

}

void APlayableController::InputMouseX(float axis)
{
	AddYawInput(axis);
}

void APlayableController::InputMouseY(float axis)
{
	AddPitchInput(axis);
}