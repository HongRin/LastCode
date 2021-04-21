#include "PreviewCharacterAnimInstance.h"
#include "Actors/Characters/PlayerCharacter/Preview/PreviewCharacter.h"

void UPreviewCharacterAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);

	if (!IsValid(Owner))
	{
		Owner = Cast<APreviewCharacter>(TryGetPawnOwner());
		return;
	}

	VelocityLength = Owner->GetCharacterMovement()->MaxWalkSpeed;
}
