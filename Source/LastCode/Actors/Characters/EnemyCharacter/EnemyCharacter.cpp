#include "EnemyCharacter.h"

#include "Actors/Controllers/EnemyController/EnemyController.h"

#include "AnimInstance/EnemyCharacter/EnemyAnimInstance.h"

#include "Components/PlayerDetector/PlayerDetectorComponent.h"
#include "Components/EnemyAttack/EnemyAttackComponent.h"

#include "Level/DungeonLevel.h"

#include "Structures/ItemInfo/ItemInfo.h"

#include "Single/GameInstance/LCGameInstance.h"
#include "Single/PlayerManager/PlayerManager.h"

#include "BrainComponent.h"

AEnemyCharacter::AEnemyCharacter()
{
	static ConstructorHelpers::FObjectFinder<UDataTable> DT_ENEMY_INFO(
		TEXT("DataTable'/Game/Resources/DataTable/DT_EnemyInfo.DT_EnemyInfo'"));
	if (DT_ENEMY_INFO.Succeeded()) DT_EnemyInfo = DT_ENEMY_INFO.Object;

	static ConstructorHelpers::FObjectFinder<UDataTable> DT_ITEM_INFO(
		TEXT("DataTable'/Game/Resources/DataTable/DT_ItemInfo.DT_ItemInfo'"));
	if (DT_ITEM_INFO.Succeeded()) DT_ItemInfo = DT_ITEM_INFO.Object;

	AIControllerClass = AEnemyController::StaticClass();

	SetGenericTeamId(TEAM_MONSTER);

	InitializeComponent();
}

void AEnemyCharacter::BeginPlay()
{
	Super::BeginPlay();

	GameInst = Cast<ULCGameInstance>(GetGameInstance());

	// Set up the Monster Info
	InitializeMonsterDataConstructTime();

	Tags.Add(TEXT("Monster"));

	bHitting = false;

	DungeonLevel = Cast<ADungeonLevel>(GetWorld()->GetLevelScriptActor());
	DungeonLevel->AddEnemyCharacters(this);
}

void AEnemyCharacter::OnTakeDamage(AActor* DamagedActor, float Damage, const UDamageType* DamageType, AController* InstigatedBy, AActor* DamageCauser)
{
	Super::OnTakeDamage(DamagedActor, Damage, DamageType, InstigatedBy, DamageCauser);

	PlayAnimMontage(HitAnim);
}

void AEnemyCharacter::OnCharacterDie()
{
	Super::OnCharacterDie();

	GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::Type::NoCollision);

	FString reason;
	Cast<AEnemyController>(GetController())->GetBrainComponent()->StopLogic(reason);
}

void AEnemyCharacter::InitializeComponent()
{
	PlayerDetector = CreateDefaultSubobject<UPlayerDetectorComponent>(TEXT("PLAYER_DETECTOR"));
	PlayerDetector->SetupAttachment(GetRootComponent());

	WeaponMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("SM_WEAPON"));
	WeaponMesh->SetupAttachment(GetMesh(), TEXT("Weapon_Socket"));

	EnemyAttack = CreateDefaultSubobject<UEnemyAttackComponent>(TEXT("ENEMY_ATTACK"));

	GetCapsuleComponent()->SetCollisionProfileName(TEXT("MonsterCollision"));
	GetMesh()->SetCollisionProfileName(TEXT("NoCollision"));
}

void AEnemyCharacter::InitializeSkeletalMeshComponent()
{
	// Monster SkeletalMesh synchronous load
	auto enemyMesh = Cast<USkeletalMesh>(
		GetManager(FStreamableManager)->LoadSynchronous(EnemyInfo.SkeletalMeshPath));

	// Anim Blueprint Asset Load
	UBlueprint* enemyAnimInstClass = Cast<UBlueprint>(
		GetManager(FStreamableManager)->LoadSynchronous(EnemyInfo.AnimInstanceClassPath));

	auto hitanim = Cast<UAnimMontage>(GetManager(FStreamableManager)->LoadSynchronous(EnemyInfo.HitAnimPath));

	if (IsValid(enemyMesh))
	{
		// Apply the loaded SkeletalMesh
		GetMesh()->SetSkeletalMesh(enemyMesh);

		// Set up the Location & Rotation
		GetMesh()->SetRelativeLocationAndRotation(
			FVector(0.0f, 0.0f, -(GetCapsuleComponent()->GetScaledCapsuleHalfHeight())),
			FRotator(0.0f, -90.0f, 0.0f));
	}
	else
		UE_LOG(LogTemp, Error, TEXT("AMonsterCharacter.cpp :: %d LINE :: monstermesh is not loaded!"), __LINE__);

	UStaticMesh* weaponStaticMesh = Cast<UStaticMesh>(GetManager(FStreamableManager)->LoadSynchronous(EnemyInfo.WeaponStaticMeshPath));
	if (IsValid(weaponStaticMesh)) WeaponMesh->SetStaticMesh(weaponStaticMesh);
	else UE_LOG(LogTemp, Error, TEXT("APreviewCharacter.cpp::%d::LINE:: weaponStaticMesh is not loaded !"));

	if (IsValid(enemyAnimInstClass))
	{
		// Cast as the AnimInstanceClass
		TSubclassOf<UEnemyAnimInstance> bpAnimInstClass =
			static_cast<TSubclassOf<UEnemyAnimInstance>>(enemyAnimInstClass->GeneratedClass);

		// Apply AnimInstanceClass
		GetMesh()->SetAnimClass(bpAnimInstClass);
	}

	if (IsValid(hitanim)) HitAnim = hitanim;
}

void AEnemyCharacter::InitializeMonsterDataConstructTime()
{
	// Saves the Infomation that matches MonsterCode 
	FString contextString;
	FEnemyInfo* enemyInfo = DT_EnemyInfo->FindRow<FEnemyInfo>(
		EnemyCode, contextString
		);

	// Check for information found
	if (enemyInfo == nullptr)
	{
		UE_LOG(LogTemp, Error, TEXT("AMonsterCharacter.cpp :: %d LINE :: monsterInfo is not loaded!"), __LINE__);
		return;
	}

	// Saves the MonsterInfo
	EnemyInfo = (*enemyInfo);

	// Set up the Hp
	Hp = MaxHp = enemyInfo->MaxHp;

	EnemyAtk = enemyInfo->Atk;

	// Set up the MaxWalkSpeed
	GetCharacterMovement()->MaxWalkSpeed = EnemyInfo.MaxSpeed;

	// SkeletalMesh Initialization
	InitializeSkeletalMeshComponent();

}

void AEnemyCharacter::EnemyRebound(FVector direction, float power)
{
	GetCharacterMovement()->AddImpulse(direction * power, true);
}

void AEnemyCharacter::EnemyDie()
{
	DungeonLevel->RemoveEnemyCharacters(this);
	DungeonLevel->AddRewardExp(EnemyInfo.Exp);
	DungeonLevel->AddRewardSilver(DropSilver());
	DropItem();
	DungeonLevel->DungeonClear();
	Destroy();
}

int32 AEnemyCharacter::DropSilver()
{
	int32 silver = FMath::FRandRange(EnemyInfo.MinDropSilver, EnemyInfo.MaxDropSilver);
	return silver;
}

void AEnemyCharacter::DropItem()
{
	for (int i = 0; i < EnemyInfo.DropItemCode.Num(); ++i)
	{
		FString contextStirng;
		FItemInfo* itemInfo = DT_ItemInfo->FindRow<FItemInfo>(EnemyInfo.DropItemCode[i], contextStirng);
		
		if (itemInfo->DropPercent > FMath::FRandRange(0.0f, 100.0f))
			DungeonLevel->SetDropItems(itemInfo->ItemCode, itemInfo->MaxSlotCount);
	}

	
}

bool AEnemyCharacter::IsMovable() const
{
	return !GetEnemyAttack()->IsEnemyAttacking() && !bIsDie && !bHitting;
}
