#include "PlayableCharacterAnimInstance.h"
#include "Actors/Characters/PlayerCharacter/PlayableCharacter.h"
#include "Actors/Controllers/PlayerController/PlayableController/PlayableController.h"

#include "Components/SkillController/SkillControllerComponent.h"

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
void UPlayableCharacterAnimInstance::AnimNotify_HitFin()
{
	if (Owner->GetSkillControllerComponent()->OnLRegularAttackFinished.IsBound())
		Owner->GetSkillControllerComponent()->OnLRegularAttackFinished.Broadcast();

	if (Owner->GetSkillControllerComponent()->OnRRegularAttackFinished.IsBound())
		Owner->GetSkillControllerComponent()->OnRRegularAttackFinished.Broadcast();

	if (Owner->GetSkillControllerComponent()->OnDashFinished.IsBound())
		Owner->GetSkillControllerComponent()->OnDashFinished.Broadcast();

	if (Owner->GetSkillControllerComponent()->OnActiveSkillFinished.IsBound())
		Owner->GetSkillControllerComponent()->OnActiveSkillFinished.Broadcast();
}
