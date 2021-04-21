#include "LastCodeGameModeBase.h"
#include "Actors/Characters/PlayerCharacter/PlayableCharacter.h"
#include "Actors/Controllers/PlayerController/PlayableController/PlayableController.h"

ALastCodeGameModeBase::ALastCodeGameModeBase()
{
	DefaultPawnClass = APlayableCharacter::StaticClass();
	PlayerControllerClass = APlayableController::StaticClass();
}