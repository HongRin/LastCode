#pragma once

#include "CoreMinimal.h"
#include "AnimInstance/PlayerCharacter/PlayableCharacterAnimInstance.h"
#include "BattleSideAnimInstance.generated.h"

UCLASS()
class LASTCODE_API UBattleSideAnimInstance : public UPlayableCharacterAnimInstance
{
	GENERATED_BODY()
	
protected :
	virtual void NativeUpdateAnimation(float DeltaTime) override;

private:
	UFUNCTION()
	void AnimNotify_LRegularComboAttackFin();

	UFUNCTION()
	void AnimNotify_LFirstComboAttack();
						
	UFUNCTION()			
	void AnimNotify_LSecondComboAttack();
						
	UFUNCTION()			
	void AnimNotify_LThirdComboAttack();

	UFUNCTION()
	void AnimNotify_RRegularComboAttackFin();

	UFUNCTION()
	void AnimNotify_RFirstComboAttack();

	UFUNCTION()
	void AnimNotify_RSecondComboAttack();

	UFUNCTION()
	void AnimNotify_RThirdComboAttack();

	UFUNCTION()
	void AnimNotify_CameraShaking();

	UFUNCTION()
	void AnimNotify_AttackMove();

	UFUNCTION()
	void AnimNotify_DashFin();

	UFUNCTION()
	void AnimNotify_UpdateRotation();

	UFUNCTION()
	void AnimNotify_UpdateAttackRange();

	UFUNCTION()
	void AnimNotify_SkillMoveStart();

	UFUNCTION()
	void AnimNotify_SkillMoveFin();

	UFUNCTION()
	void AnimNotify_SkillFin();
};
