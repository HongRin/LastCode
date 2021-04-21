#include "SelectCharacterGameMode.h"
#include "Actors/Characters/PlayerCharacter/Preview/PreviewCharacter.h"
#include "Actors/Controllers/PlayerController/Preview/PreviewCharacterController.h"

ASelectCharacterGameMode::ASelectCharacterGameMode()
{
	DefaultPawnClass = APreviewCharacter::StaticClass();
	PlayerControllerClass = APreviewCharacterController::StaticClass();
};