#include "LevelUpComponent.h"

ULevelUpComponent::ULevelUpComponent()
{
	PrimaryComponentTick.bCanEverTick = true;

}


void ULevelUpComponent::BeginPlay()
{
	Super::BeginPlay();

	
}


void ULevelUpComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

}

