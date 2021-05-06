#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "EnemyAnimInstance.generated.h"

UCLASS()
class LASTCODE_API UEnemyAnimInstance : public UAnimInstance
{
	GENERATED_BODY()

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Character")
	class AEnemyCharacter* Owner;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Character")
	float VelocityLength;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Character")
	bool IsDie;

public:
	virtual void NativeUpdateAnimation(float DeltaSeconds) override;

protected:
	UFUNCTION()
	void AnimNotify_EnemyAttackFin();

	UFUNCTION()
	void AnimNotify_UpdateRotation();

	UFUNCTION()
	void AnimNotify_AttackRange();

	UFUNCTION()
	void AnimNotify_EnemyReBound();

	UFUNCTION()
	void AnimNotify_EnemyHitStart();

	UFUNCTION()
	void AnimNotify_EnemyHitFin();

	UFUNCTION()
	void AnimNotify_EnemyDieFin();
};
