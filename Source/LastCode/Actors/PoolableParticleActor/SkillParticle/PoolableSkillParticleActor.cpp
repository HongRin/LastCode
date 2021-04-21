#include "PoolableSkillParticleActor.h"

#include "Particles/ParticleSystemComponent.h"
#include "Components/SkillController/SkillControllerComponent.h"

#include "Single/GameInstance/LCGameInstance.h"
#include "Single/PlayerManager/PlayerManager.h"


APoolableSkillParticleActor::APoolableSkillParticleActor()
{
	PrimaryActorTick.bCanEverTick = true;

	SkillParticleSystem = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("PARTICLE_SYSTEM_COMP"));
	SetRootComponent(SkillParticleSystem);

	SetID(DEFAULT_SKILL);
}

void APoolableSkillParticleActor::BeginPlay()
{
	Super::BeginPlay();

	SkillParticleSystem->OnSystemFinished.AddDynamic(
		this, &APoolableSkillParticleActor::OnParticleSystemFinished);

}

void APoolableSkillParticleActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void APoolableSkillParticleActor::OnRecycleStart()
{

}

void APoolableSkillParticleActor::OnParticleSystemFinished(UParticleSystemComponent* PSystem)
{
	SkillParticleSystem->Activate(false);

	SetCanRecyclable(true);
}

void APoolableSkillParticleActor::PlayParticle(UParticleSystem* skillParticle, FVector loc, FRotator rot)
{
	SkillParticleSystem->SetTemplate(skillParticle);

	SkillParticleSystem->Activate(true);
	SkillParticleSystem->SetWorldLocationAndRotation(loc, rot);
}
