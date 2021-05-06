#include "EnemyAttackComponent.h"

#include "Actors/Characters/EnemyCharacter/EnemyCharacter.h"
#include "Structures/EnemyInfo/EnemyInfo.h"

UEnemyAttackComponent::UEnemyAttackComponent()
{
	PrimaryComponentTick.bCanEverTick = true;

	AttackState = MONSTER_ATTACK_NONE;
}


void UEnemyAttackComponent::BeginPlay()
{
	Super::BeginPlay();

	EnemyCharacter = Cast<AEnemyCharacter>(GetOwner());

	OnEnemyAttackFinished.AddLambda([this]()->void {
		AttackState = MONSTER_ATTACK_NONE;
		});
}


void UEnemyAttackComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

}

void UEnemyAttackComponent::PlayEnemyAttackAnimation()
{
	if (AttackState != MONSTER_ATTACK_NONE || EnemyCharacter->IsHitting()) return;
	if (!IsValid(EnemyAttack)) return;

	if (OnEnemyAttackStarted.IsBound())
		OnEnemyAttackStarted.Broadcast();

		AttackState = MONSTER_ATTACK_BASIC;
		EnemyCharacter->PlayAnimMontage(EnemyAttack, 1.0f, TEXT("Attack"));
}

void UEnemyAttackComponent::ActiveEnemyAttackRange()
{
	FEnemyInfo* enemyInfo = EnemyCharacter->GetEnemyInfo();

	float attackRange = enemyInfo->AtkRange;

	FVector start = EnemyCharacter->GetActorLocation();

	TArray<AActor*> actorsToIgnore;
	actorsToIgnore.Add(EnemyCharacter);

	TArray<FHitResult> outHits;

	UKismetSystemLibrary::SphereTraceMultiByProfile(
		GetWorld(),
		start,
		EnemyCharacter->GetActorLocation() + (EnemyCharacter->GetActorForwardVector() * attackRange),
		attackRange,
		TEXT("AttackRange"),
		true,
		actorsToIgnore,
		EDrawDebugTrace::Type::ForDuration,
		outHits,
		true,
		FLinearColor::Red,
		FLinearColor::Red,
		2.0f
	);

	for (auto hit : outHits)
	{
		if (!hit.GetActor()->ActorHasTag(TEXT("Monster")))
		{
			hit.GetActor()->TakeDamage(
				EnemyCharacter->GetEnemyAtk(),
				FDamageEvent(),
				EnemyCharacter->GetController(),
				EnemyCharacter);
		}
	}
}

