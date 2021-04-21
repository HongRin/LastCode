#include "BattleSideAnimInstance.h"

#include "Actors/Characters/PlayerCharacter/PlayableCharacter.h"
#include "Actors/Controllers/PlayerController/PlayableController/PlayableController.h"
#include "Components/SkillController/SkillControllerComponent.h"

#include "Single/GameInstance/LCGameInstance.h"
#include "Single/PlayerManager/PlayerManager.h"


void UBattleSideAnimInstance::NativeUpdateAnimation(float DeltaTime)
{
	Super::NativeUpdateAnimation(DeltaTime);
	if (!IsValid(Owner)) return;
}

void UBattleSideAnimInstance::AnimNotify_LRegularComboAttackFin()
{
	if (Owner->GetSkillControllerComponent()->OnLRegularAttackFinished.IsBound())
		Owner->GetSkillControllerComponent()->OnLRegularAttackFinished.Broadcast();
}

void UBattleSideAnimInstance::AnimNotify_LFirstComboAttack()
{
	if (Owner->GetSkillControllerComponent()->LFirstComboAttackable())
		Montage_JumpToSection(TEXT("LComboAttack2"));
}

void UBattleSideAnimInstance::AnimNotify_LSecondComboAttack()
{
	if (Owner->GetSkillControllerComponent()->LSecondComboAttackable())
		Montage_JumpToSection(TEXT("LComboAttack3"));
}

void UBattleSideAnimInstance::AnimNotify_LThirdComboAttack()
{
	if (Owner->GetSkillControllerComponent()->LThirdComboAttackable())
		Montage_JumpToSection(TEXT("LComboAttack4"));
}

void UBattleSideAnimInstance::AnimNotify_RRegularComboAttackFin()
{
	if (Owner->GetSkillControllerComponent()->OnRRegularAttackFinished.IsBound())
		Owner->GetSkillControllerComponent()->OnRRegularAttackFinished.Broadcast();
}

void UBattleSideAnimInstance::AnimNotify_RFirstComboAttack()
{
	if (Owner->GetSkillControllerComponent()->RFirstComboAttackable())
		Montage_JumpToSection(TEXT("RComboAttack2"));
}

void UBattleSideAnimInstance::AnimNotify_RSecondComboAttack()
{
	if (Owner->GetSkillControllerComponent()->RSecondComboAttackable())
		Montage_JumpToSection(TEXT("RComboAttack3"));
}

void UBattleSideAnimInstance::AnimNotify_RThirdComboAttack()
{
	if (Owner->GetSkillControllerComponent()->RThirdComboAttackable())
		Montage_JumpToSection(TEXT("RComboAttack4"));
}


void UBattleSideAnimInstance::AnimNotify_CameraShaking()
{
	Owner->GetSkillControllerComponent()->CameraShaking();
}

void UBattleSideAnimInstance::AnimNotify_AttackMove()
{
	Owner->GetCharacterMovement()->AddImpulse(Owner->GetActorForwardVector() * 1000.0f, true);
}

void UBattleSideAnimInstance::AnimNotify_DashFin()
{
	if (Owner->GetSkillControllerComponent()->OnDashFinished.IsBound())
		Owner->GetSkillControllerComponent()->OnDashFinished.Broadcast();
}

void UBattleSideAnimInstance::AnimNotify_UpdateRotation()
{ Owner->LookatControlDirection(); }

void UBattleSideAnimInstance::AnimNotify_UpdateAttackRange()
{ Owner->GetSkillControllerComponent()->UpdateAttackRange(); }

void UBattleSideAnimInstance::AnimNotify_SkillMoveStart()
{
	Owner->AllowMove();
	Owner->GetCharacterMovement()->MaxWalkSpeed = 600.0f;
}

void UBattleSideAnimInstance::AnimNotify_SkillMoveFin()
{
	Owner->ProhibitMove();
}

void UBattleSideAnimInstance::AnimNotify_SkillFin()
{
	if (Owner->GetSkillControllerComponent()->OnActiveSkillFinished.IsBound())
		Owner->GetSkillControllerComponent()->OnActiveSkillFinished.Broadcast();
}
