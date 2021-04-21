#pragma once

#include "CoreMinimal.h"
#include "AnimInstance/PlayerCharacter/PlayableCharacterAnimInstance.h"
#include "SniperAnimInstance.generated.h"

UCLASS()
class LASTCODE_API USniperAnimInstance : public UPlayableCharacterAnimInstance
{
	GENERATED_BODY()

public:
	virtual void NativeUpdateAnimation(float DeltaSeconds) override;

private :
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
	void AnimNotify_DashFin();

	UFUNCTION()
	void AnimNotify_UpdateRotation();

	UFUNCTION()
	void AnimNotify_UpdateAttackRange();

	UFUNCTION()
	void AnimNotify_SkillFin();

	UFUNCTION()
	void AnimNotify_PlayExplosionShotParticle();

	UFUNCTION()
	void AnimNotify_PlayFreezingShotParticle();
};
