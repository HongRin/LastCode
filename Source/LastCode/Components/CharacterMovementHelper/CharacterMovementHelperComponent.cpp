#include "CharacterMovementHelperComponent.h"

UCharacterMovementHelperComponent::UCharacterMovementHelperComponent()
{
	PrimaryComponentTick.bCanEverTick = true;

}


void UCharacterMovementHelperComponent::BeginPlay()
{
	Super::BeginPlay();
	
}


void UCharacterMovementHelperComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

}

