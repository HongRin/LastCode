#include "EnemyController.h"

#include "Actors/Characters/EnemyCharacter/EnemyCharacter.h"
#include "Components/PlayerDetector/PlayerDetectorComponent.h"
#include "Components/EnemyAttack/EnemyAttackComponent.h"

#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BlackboardData.h"
#include "BehaviorTree/BlackboardComponent.h"

#include "Perception/AIPerceptionComponent.h"
#include "Perception/AISenseConfig_Sight.h"

AEnemyController::AEnemyController()
{
	static ConstructorHelpers::FObjectFinder<UBehaviorTree> BT_ENEMY(
		TEXT("BehaviorTree'/Game/Resources/AI/BT_Enemy.BT_Enemy'"));
	if (BT_ENEMY.Succeeded()) EnemyBehaviorTree = BT_ENEMY.Object;

	InitializeEnemyController();
}

void AEnemyController::BeginPlay()
{
	Super::BeginPlay();
}

void AEnemyController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);

	EnemyCharacter = Cast<AEnemyCharacter>(InPawn);

	if (IsValid(EnemyBehaviorTree))
	{
		RunBehaviorTree(EnemyBehaviorTree);

		GetPerceptionComponent()->OnTargetPerceptionUpdated.AddDynamic(this,
			&AEnemyController::OnSightDetected);
	}
	else
	{
		UE_LOG(LogTemp, Error,
			TEXT("MonsterController.cpp :: %d LINE :: MonseterBehaviorTree is not loaded !"), __LINE__);
	}

	EnemyCharacter->GetEnemyAttack()->OnEnemyAttackStarted.AddUObject(
		this, &AEnemyController::IsLookatPlayer);

	EnemyCharacter->GetEnemyAttack()->OnEnemyAttackStarted.AddLambda([this]()->void
		{ MoveToActor(EnemyCharacter); });
}

void AEnemyController::Tick(float dt)
{
	Super::Tick(dt);


	if (GetEnemyCharacter()->IsMovable())
	{
		if (!IsPlayerNearby())
			TrackingPlayer();
	}
}

void AEnemyController::InitializeEnemyController()
{
	SetPerceptionComponent(*CreateDefaultSubobject<UAIPerceptionComponent>(TEXT("AI_PERCEPTION")));

	SetGenericTeamId(TEAM_MONSTER);

	{
		AISightConfig = CreateDefaultSubobject<UAISenseConfig_Sight>(TEXT("SIGHT_CONFIG"));

		AISightConfig->SightRadius = 700.0f;
		AISightConfig->LoseSightRadius = AISightConfig->SightRadius + 100.0f;
		AISightConfig->PeripheralVisionAngleDegrees = 180.0f;

		// 감지 객체가 사라지더라도 유지하는 시간
		AISightConfig->SetMaxAge(2.0f);

		AISightConfig->DetectionByAffiliation.bDetectEnemies = true;
		AISightConfig->DetectionByAffiliation.bDetectFriendlies = false;
		AISightConfig->DetectionByAffiliation.bDetectNeutrals = false;

		GetPerceptionComponent()->ConfigureSense(*AISightConfig);
	}
}

bool AEnemyController::IsPlayerNearby()
{
	bool nearby = false;

	if (IsValid(EnemyCharacter))
	{
		nearby = EnemyCharacter->GetPlayerDetector()->IsPlayerDetected();
	}

	GetBlackboardComponent()->SetValueAsBool(TEXT("PlayerIsNearby"), nearby);

	return nearby;
}

void AEnemyController::TrackingPlayer()
{
	if (!IsValid(TrackingTargetActor)) return;

	GetBlackboardComponent()->SetValueAsBool(TEXT("IsTracking"), true);

	MoveToActor(TrackingTargetActor);
}

void AEnemyController::IsLookatPlayer()
{
	if (!IsValid(TrackingTargetActor)) return;

	FVector trackingLocation = TrackingTargetActor->GetActorLocation();
	FVector currentLocation = GetEnemyCharacter()->GetActorLocation();

	FVector direction = trackingLocation - currentLocation;

	direction.Z = 0.0f;

	direction = direction.GetSafeNormal();

	GetEnemyCharacter()->SetActorRotation(direction.Rotation());
}

void AEnemyController::OnSightDetected(AActor* Actor, FAIStimulus Stimulus)
{
	if (Stimulus.WasSuccessfullySensed())
	{
		if (!IsValid(TrackingTargetActor))
			TrackingTargetActor = Actor;
	}
	else
		TrackingTargetActor = nullptr;
}
