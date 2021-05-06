#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "EnemyAttackComponent.generated.h"

#ifndef MONSTER_ATTACK_TYPE
#define MONSTER_ATTACK_TYPE

#define MONSTER_ATTACK_NONE -1
#define MONSTER_ATTACK_BASIC 0

#endif 

DECLARE_MULTICAST_DELEGATE(FOnEnemyAttackEventSignature)


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class LASTCODE_API UEnemyAttackComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	FOnEnemyAttackEventSignature OnEnemyAttackStarted;

	FOnEnemyAttackEventSignature OnEnemyAttackFinished;

private:
	UPROPERTY()
	class AEnemyCharacter* EnemyCharacter;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Character", meta = (AllowPrivateAccess = "true"))
	class UAnimMontage* EnemyAttack;

	UPROPERTY()
	int32 AttackState;

public:	
	UEnemyAttackComponent();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

public:
	void PlayEnemyAttackAnimation();

	void ActiveEnemyAttackRange();

	FORCEINLINE bool IsEnemyAttacking() const
	{
		return AttackState != MONSTER_ATTACK_NONE;
	};
};
