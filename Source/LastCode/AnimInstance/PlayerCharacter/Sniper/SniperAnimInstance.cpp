#include "SniperAnimInstance.h"

#include "Actors/Characters/PlayerCharacter/PlayableCharacter.h"
#include "Actors/Controllers/PlayerController/PlayableController/PlayableController.h"
#include "Components/SkillController/SkillControllerComponent.h"

#include "Single/GameInstance/LCGameInstance.h"
#include "Single/PlayerManager/PlayerManager.h"


void USniperAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);
	if (!IsValid(Owner)) return;
}

void USniperAnimInstance::AnimNotify_LRegularComboAttackFin()
{
	if (Owner->GetSkillControllerComponent()->OnLRegularAttackFinished.IsBound())
		Owner->GetSkillControllerComponent()->OnLRegularAttackFinished.Broadcast();
}

void USniperAnimInstance::AnimNotify_LFirstComboAttack()
{
	if (Owner->GetSkillControllerComponent()->LFirstComboAttackable())
		Montage_JumpToSection(TEXT("LComboAttack2"));
}

void USniperAnimInstance::AnimNotify_LSecondComboAttack()
{
	if (Owner->GetSkillControllerComponent()->LSecondComboAttackable())
		Montage_JumpToSection(TEXT("LComboAttack3"));
}

void USniperAnimInstance::AnimNotify_LThirdComboAttack()
{
	if (Owner->GetSkillControllerComponent()->LThirdComboAttackable())
		Montage_JumpToSection(TEXT("LComboAttack4"));
}

void USniperAnimInstance::AnimNotify_RRegularComboAttackFin()
{
	if (Owner->GetSkillControllerComponent()->OnRRegularAttackFinished.IsBound())
		Owner->GetSkillControllerComponent()->OnRRegularAttackFinished.Broadcast();
}

void USniperAnimInstance::AnimNotify_RFirstComboAttack()
{
	if (Owner->GetSkillControllerComponent()->RFirstComboAttackable())
		Montage_JumpToSection(TEXT("RComboAttack2"));
}

void USniperAnimInstance::AnimNotify_RSecondComboAttack()
{
	if (Owner->GetSkillControllerComponent()->RSecondComboAttackable())
		Montage_JumpToSection(TEXT("RComboAttack3"));
}

void USniperAnimInstance::AnimNotify_RThirdComboAttack()
{
	if (Owner->GetSkillControllerComponent()->RThirdComboAttackable())
		Montage_JumpToSection(TEXT("RComboAttack4"));
}


void USniperAnimInstance::AnimNotify_CameraShaking()
{
	Owner->GetSkillControllerComponent()->CameraShaking();
}

void USniperAnimInstance::AnimNotify_DashFin()
{
	if (Owner->GetSkillControllerComponent()->OnDashFinished.IsBound())
		Owner->GetSkillControllerComponent()->OnDashFinished.Broadcast();
}

void USniperAnimInstance::AnimNotify_UpdateRotation()
{ Owner->LookatControlDirection(); }

void USniperAnimInstance::AnimNotify_UpdateAttackRange()
{ Owner->GetSkillControllerComponent()->UpdateAttackRange(); }

void USniperAnimInstance::AnimNotify_SkillFin()
{
	if (Owner->GetSkillControllerComponent()->OnActiveSkillFinished.IsBound())
		Owner->GetSkillControllerComponent()->OnActiveSkillFinished.Broadcast();
}

void USniperAnimInstance::AnimNotify_PlayExplosionShotParticle()
{
	Owner->GetSkillControllerComponent()->PlaySkillParitcle(Owner->GetActorLocation() +
		(Owner->GetActorForwardVector() * 700.0f) + 
		(Owner->GetActorUpVector() * -100.0f));
}

void USniperAnimInstance::AnimNotify_PlayFreezingShotParticle()
{
	Owner->GetSkillControllerComponent()->PlaySkillParitcle(Owner->GetActorLocation() + 
		(Owner->GetActorForwardVector() * 700.0f) +
		(Owner->GetActorUpVector() * -80.0f));
}
