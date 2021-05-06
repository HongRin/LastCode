#pragma once

#include "LastCode.h"
#include "AIController.h"
#include "Perception/AIPerceptionTypes.h"
#include "EnemyController.generated.h"

UCLASS()
class LASTCODE_API AEnemyController : public AAIController
{
	GENERATED_BODY()
	
private:
	UPROPERTY()
	class AEnemyCharacter* EnemyCharacter;

	UPROPERTY(VisibleAnywhere, meta = (AllowPrivateAccess = "true"))
	class UAISenseConfig_Sight* AISightConfig;

	UPROPERTY(VisibleAnywhere, meta = (AllowPrivateAccess = "true"))
	class UBehaviorTree* EnemyBehaviorTree;

	UPROPERTY()
	class AActor* TrackingTargetActor;

public:
	AEnemyController();

public:
	virtual void BeginPlay() override;
	virtual void OnPossess(APawn* InPawn) override;
	virtual void Tick(float dt) override;

private:
	void InitializeEnemyController();

	bool IsPlayerNearby();

	void TrackingPlayer();

public:
	void IsLookatPlayer();

private:
	UFUNCTION()
		void OnSightDetected(AActor* Actor, FAIStimulus Stimulus);

public:
	FORCEINLINE AEnemyCharacter* GetEnemyCharacter() const
	{ return EnemyCharacter; }


};
