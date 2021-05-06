#include "PlayableCharacterAnimInstance.h"
#include "Actors/Characters/PlayerCharacter/PlayableCharacter.h"
#include "Actors/Controllers/PlayerController/PlayableController/PlayableController.h"

#include "Single/GameInstance/LCGameInstance.h"
#include "Single/PlayerManager/PlayerManager.h"


void UPlayableCharacterAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);

	if (!IsValid(Owner))
	{
		Owner = Cast<APlayableCharacter>(TryGetPawnOwner());
		return;
	}

	VelocityLength = Owner->GetVelocity().Size();

	bIsInAir = Owner->IsInAir();

	bIsDie = Owner->IsDie();
}
