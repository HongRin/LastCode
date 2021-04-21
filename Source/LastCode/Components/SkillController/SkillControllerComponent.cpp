#include "SkillControllerComponent.h"

#include "Actors/Characters/PlayerCharacter/PlayableCharacter.h"
#include "Actors/Controllers/PlayerController/PlayableController/PlayableController.h"
#include "Actors/PoolableParticleActor/SkillParticle/PoolableSkillParticleActor.h"

#include "Components/ShakeCamera/ShakeCamera.h"

#include "Single/GameInstance/LCGameInstance.h"
#include "Single/PlayerManager/PlayerManager.h"

#include "Structures/SkillInfo/SkillInfo.h"

#include "Util/ObjectPool.h"

#include "GameFramework/PlayerInput.h"

USkillControllerComponent::USkillControllerComponent()
{
	PrimaryComponentTick.bCanEverTick = true;

	LoadAsset();
}


void USkillControllerComponent::BeginPlay()
{
	Super::BeginPlay();

	PlayableCharacter = Cast<APlayableCharacter>(GetOwner());

	ParticleObjectPool = NewObject<UObjectPool>();

	OnLRegularAttackFinished.AddLambda([this]()->void {
		bIsLRegularAttack = bIsLFirstComboAttack = bIsLSecondComboAttack = bIsLThirdComboAttack = false;
		EmptySkillInfo();
		});
	OnRRegularAttackFinished.AddLambda([this]()->void {
		bIsRRegularAttack = bIsRFirstComboAttack = bIsRSecondComboAttack = bIsRThirdComboAttack = false;
		EmptySkillInfo();
		});
	OnDashFinished.AddLambda([this]()->void {
		PlayableCharacter->AllowMove();
		bIsDash = false;
		EmptySkillInfo();
		});

	OnActiveSkillFinished.AddLambda([this]()->void {
		PlayableCharacter->AllowMove();
		bIsSkillable = false;
		EmptySkillInfo();
		});

	SkillInfo = GetManager(UPlayerManager)->GetPlayerInfo()->SkillInfo;
}

void USkillControllerComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

void USkillControllerComponent::LoadAsset()
{
	static ConstructorHelpers::FObjectFinder<UDataTable> DT_SKILL_INFO(
		TEXT("DataTable'/Game/Resources/DataTable/DT_SkillInfo.DT_SkillInfo'"));
	if (DT_SKILL_INFO.Succeeded()) DT_SkillInfo = DT_SKILL_INFO.Object;
	else UE_LOG(LogTemp, Warning, TEXT("UPlayerAttackComponent.cpp::%d::LINE:: DT_SKILL_INFO is not loaded!"), __LINE__);

	static ConstructorHelpers::FClassFinder<APoolableSkillParticleActor> SKILL_PARTICLE_ACTOR(
		TEXT("Blueprint'/Game/Resources/Blueprints/Actor/PoolableActor/SkillParticle/P_SkillParitcle.P_SkillParitcle_C'"));
	if (SKILL_PARTICLE_ACTOR.Succeeded()) SkillParticle = SKILL_PARTICLE_ACTOR.Class;

	ShakeCamera = UShakeCamera::StaticClass();
}

void USkillControllerComponent::PlayActiveSkill(FName skillCode)
{
	if (!PlayableCharacter->IsMoveable()) return;

	UpdateSkillInfo(skillCode);

	if (GetManager(UPlayerManager)->GetPlayerInfo()->Stamina < BehaviorSkillInfo->SkillStamina)
	{
		EmptySkillInfo();
		return;
	}

	if (GetManager(UPlayerManager)->GetQuickManager()->QuickSlotEventStarted.IsBound())
		GetManager(UPlayerManager)->GetQuickManager()->QuickSlotEventStarted.Broadcast(skillCode);

	PlayableCharacter->ProhibitMove();

	bIsSkillable = true;

	PlayableCharacter->PlayAnimMontage(BehaviorSkillInfo->SkillAnimPath);

	GetManager(UPlayerManager)->GetPlayerInfo()->Stamina -= BehaviorSkillInfo->SkillStamina;
	if (GetManager(UPlayerManager)->GetPlayerStateManager()->OnUpdateStamina.IsBound())
		GetManager(UPlayerManager)->GetPlayerStateManager()->OnUpdateStamina.Broadcast();

	UE_LOG(LogTemp, Warning, TEXT("PlayActiveSkill"));
}

void USkillControllerComponent::PlayUseItem(FName skillCode)
{
	UpdateSkillInfo(skillCode);

	switch (BehaviorSkillInfo->SkillInfluenceType)
	{
	case ESkillInfluenceType::SLF_HP : 
		GetManager(UPlayerManager)->GetPlayerInfo()->Hp += BehaviorSkillInfo->SkillValue;
		if (GetManager(UPlayerManager)->GetPlayerStateManager()->OnUpdateHp.IsBound())
			GetManager(UPlayerManager)->GetPlayerStateManager()->OnUpdateHp.Broadcast();
		break;
	case ESkillInfluenceType::SLF_STAMINA:
		GetManager(UPlayerManager)->GetPlayerInfo()->Stamina += BehaviorSkillInfo->SkillValue;
		if (GetManager(UPlayerManager)->GetPlayerStateManager()->OnUpdateStamina.IsBound())
			GetManager(UPlayerManager)->GetPlayerStateManager()->OnUpdateStamina.Broadcast();
		break;
	}

	if (GetManager(UPlayerManager)->GetQuickManager()->QuickSlotEventStarted.IsBound())
		GetManager(UPlayerManager)->GetQuickManager()->QuickSlotEventStarted.Broadcast(skillCode);
	EmptySkillInfo();
}

void USkillControllerComponent::LRegularAttack()
{
	if (PlayableCharacter->IsInAir() || bIsDash || IsSkillable()) return;

	if (OnRRegularAttackFinished.IsBound())
		OnRRegularAttackFinished.Broadcast();

	UpdateSkillInfo(FName(TEXT("0001")));

	if (bIsLSecondComboAttack)
		bIsLThirdComboAttack = true;
	else if (bIsLFirstComboAttack)
		bIsLSecondComboAttack = true;
	else if (bIsLRegularAttack)
		bIsLFirstComboAttack = true;
	else
	{
		bIsLRegularAttack = true;
		PlayableCharacter->PlayAnimMontage(BehaviorSkillInfo->SkillAnimPath);
	}
}

void USkillControllerComponent::RRegularAttack()
{
	if (PlayableCharacter->IsInAir() || bIsDash || IsSkillable()) return;

	if (OnLRegularAttackFinished.IsBound())
		OnLRegularAttackFinished.Broadcast();

	UpdateSkillInfo(FName(TEXT("0001")));

	if (bIsRSecondComboAttack)
		bIsRThirdComboAttack = true;
	else if (bIsRFirstComboAttack)
		bIsRSecondComboAttack = true;
	else if (bIsRRegularAttack)
		bIsRFirstComboAttack = true;
	else
	{
		bIsRRegularAttack = true;
		PlayableCharacter->PlayAnimMontage(BehaviorSkillInfo->SkillAnimPath, 1.0f, TEXT("RComboAttack1"));
	}
}

void USkillControllerComponent::Dash()
{
	if (!PlayableCharacter->IsMoveable() || IsSkillable()) return;

	bIsDash = true;

	UpdateSkillInfo(FName(TEXT("0002")));

	PlayableCharacter->ProhibitMove();

	if (GetManager(UPlayerManager)->GetPlayableController()->GetInputKeyTimeDown(FKey("W")) >= 0.01f)
	{
		PlayableCharacter->PlayAnimMontage(BehaviorSkillInfo->SkillAnimPath, 1.0f, TEXT("ForwardDash"));
		PlayableCharacter->LookatControlDirection();
		PlayableCharacter->SetImpluse(PlayableCharacter->GetActorForwardVector(), 12000.0f);
	}
	else if (GetManager(UPlayerManager)->GetPlayableController()->GetInputKeyTimeDown(FKey("S")) >= 0.01f)
	{
		PlayableCharacter->PlayAnimMontage(BehaviorSkillInfo->SkillAnimPath, 1.0f, TEXT("BackwardDash"));
		PlayableCharacter->LookatControlDirection();
		PlayableCharacter->SetImpluse(PlayableCharacter->GetActorForwardVector(), -12000.0f);
	}
	else if (GetManager(UPlayerManager)->GetPlayableController()->GetInputKeyTimeDown(FKey("D")) >= 0.01f)
	{
		PlayableCharacter->PlayAnimMontage(BehaviorSkillInfo->SkillAnimPath, 1.0f, TEXT("RightDash"));
		PlayableCharacter->LookatControlDirection();
		PlayableCharacter->SetImpluse(PlayableCharacter->GetActorRightVector(), 12000.0f);
	}
	else if (GetManager(UPlayerManager)->GetPlayableController()->GetInputKeyTimeDown(FKey("A")) >= 0.01f)
	{
		PlayableCharacter->PlayAnimMontage(BehaviorSkillInfo->SkillAnimPath, 1.0f, TEXT("LeftDash"));
		PlayableCharacter->LookatControlDirection();
		PlayableCharacter->SetImpluse(PlayableCharacter->GetActorRightVector(), -12000.0f);
	}
}

void USkillControllerComponent::PlayQuickSlotkill(FName skillCode, ESkillType skillType)
{
	if (skillType == ESkillType::SKT_ACTIVE) PlayActiveSkill(skillCode);
	else if (skillType == ESkillType::SKT_ITEM) PlayUseItem(skillCode);
}

void USkillControllerComponent::UpdateSkillInfo(FName skillCode)
{
	for (int i = 0; i < SkillInfo.Num(); ++i)
	{
		if (SkillInfo[i].SkillCode == skillCode)
			BehaviorSkillInfo = &SkillInfo[i];
	}
}

void USkillControllerComponent::EmptySkillInfo()
{
	BehaviorSkillInfo = nullptr;
}

void USkillControllerComponent::CameraShaking(float scale)
{
	GetManager(UPlayerManager)->GetPlayableController()->PlayerCameraManager->PlayCameraShake(ShakeCamera, scale);
}

void USkillControllerComponent::UpdateAttackRange()
{
	TArray<AActor*> actorsToIgnore;
	actorsToIgnore.Add(PlayableCharacter);


	TArray<FHitResult> hitResults;

	UKismetSystemLibrary::SphereTraceMultiByProfile(
		GetWorld(),
		PlayableCharacter->GetActorLocation() + (PlayableCharacter->GetActorForwardVector() * BehaviorSkillInfo->SkillStartLenght),
		PlayableCharacter->GetActorLocation() + (PlayableCharacter->GetActorForwardVector() * BehaviorSkillInfo->SkillEndLenght),
		BehaviorSkillInfo->SkillRadius,
		TEXT("AttackRange"),
		true,
		actorsToIgnore,
		EDrawDebugTrace::Type::ForDuration,
		hitResults,
		true);

	for (auto hit : hitResults)
	{
		hit.GetActor()->TakeDamage(
			PlayableCharacter->GetPlayerManager()->GetPlayerInfo()->Atk,
			FDamageEvent(),
			PlayableCharacter->GetController(),
			PlayableCharacter);
	}
}

APoolableSkillParticleActor* USkillControllerComponent::PlaySkillParitcle(FVector loc, FRotator rot)
{
	ULCGameInstance* gameInst = Cast<ULCGameInstance>(GetWorld()->GetGameInstance());

	auto skillParticle = Cast<UParticleSystem>(
		GetManager(FStreamableManager)->LoadSynchronous(BehaviorSkillInfo->SkillParticlePath));


	auto skillParticlePool = Cast<APoolableSkillParticleActor>(
		ParticleObjectPool->GetRecycledObjectById(DEFAULT_SKILL));

	if (!IsValid(skillParticlePool))
	{
		ParticleObjectPool->RegisterRecyclableObject(
			skillParticlePool = GetWorld()->SpawnActor<APoolableSkillParticleActor>(SkillParticle));
	}

	skillParticlePool->PlayParticle(skillParticle, loc, rot);

	return skillParticlePool;
}
