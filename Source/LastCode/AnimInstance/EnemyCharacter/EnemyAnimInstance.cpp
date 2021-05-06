#include "EnemyAnimInstance.h"

#include "Actors/Characters/EnemyCharacter/EnemyCharacter.h"
#include "Actors/Controllers/EnemyController/EnemyController.h"

#include "Components/EnemyAttack/EnemyAttackComponent.h"

void UEnemyAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);

	if (!IsValid(Owner))
	{
		Owner = Cast<AEnemyCharacter>(TryGetPawnOwner());
		return;
	}

	VelocityLength = Owner->GetVelocity().Size();

	IsDie = Owner->IsDie();
}

void UEnemyAnimInstance::AnimNotify_EnemyAttackFin()
{
	if (Owner->GetEnemyAttack()->OnEnemyAttackFinished.IsBound())
		Owner->GetEnemyAttack()->OnEnemyAttackFinished.Broadcast();

	Owner->GetEnemyInfo()->Atk = Owner->GetEnemyAtk();
}

void UEnemyAnimInstance::AnimNotify_UpdateRotation()
{
	Cast<AEnemyController>(Owner->GetController())->IsLookatPlayer();
}

void UEnemyAnimInstance::AnimNotify_AttackRange()
{
	Owner->GetEnemyAttack()->ActiveEnemyAttackRange();
}

void UEnemyAnimInstance::AnimNotify_EnemyReBound()
{
	Owner->EnemyRebound(Owner->GetActorForwardVector(), -2000.0f);
}

void UEnemyAnimInstance::AnimNotify_EnemyHitStart()
{
	Owner->SetHitting(true);
}

void UEnemyAnimInstance::AnimNotify_EnemyHitFin()
{
	Owner->SetHitting(false);
}

void UEnemyAnimInstance::AnimNotify_EnemyDieFin()
{
	Owner->EnemyDie();
}
