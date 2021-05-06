#include "PlayerDetectorComponent.h"

#include "Actors/Controllers/PlayerController/PlayableController/PlayableController.h"
#include "Actors/Characters/PlayerCharacter/PlayableCharacter.h"

#include "Single/PlayerManager/PlayerManager.h"
#include "Single/GameInstance/LCGameInstance.h"

UPlayerDetectorComponent::UPlayerDetectorComponent()
{
	SphereRadius = 400.0f;
}

void UPlayerDetectorComponent::BeginPlay()
{
	Super::BeginPlay();

	OnComponentBeginOverlap.AddDynamic(this, &UPlayerDetectorComponent::OnPlayerDetected);
	OnComponentEndOverlap.AddDynamic(this, &UPlayerDetectorComponent::OnPlayerLost);
}

void UPlayerDetectorComponent::OnPlayerDetected(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor == Cast<APlayableCharacter>(GetManager(UPlayerManager)->GetPlayableController()->GetPawn()))
	{
		if (OtherComp == Cast<APlayableCharacter>(OtherActor)->GetCapsuleComponent())
			bDetectPlayer = true;
	}
}

void UPlayerDetectorComponent::OnPlayerLost(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if (OtherActor == Cast<APlayableCharacter>(GetManager(UPlayerManager)->GetPlayableController()->GetPawn()))
	{
		if (OtherComp == Cast<APlayableCharacter>(OtherActor)->GetCapsuleComponent())
			bDetectPlayer = false;
	}
}
