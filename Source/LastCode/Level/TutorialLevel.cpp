#include "TutorialLevel.h"

#include "Actors/Characters/PlayerCharacter/PlayableCharacter.h"
#include "Actors/Controllers/PlayerController/PlayableController/PlayableController.h"

#include "Single/GameInstance/LCGameInstance.h"
#include "Single/PlayerManager/PlayerManager.h"

#include "Widgets/TipWnd/TipWnd.h"

ATutorialLevel::ATutorialLevel()
{
	PrimaryActorTick.bCanEverTick = true;

	static ConstructorHelpers::FClassFinder<UTipWnd> BP_TIP_WND(
		TEXT("WidgetBlueprint'/Game/Resources/Blueprints/Widgets/TipWnd/BP_Tip.BP_Tip_C'"));
	if (BP_TIP_WND.Succeeded()) BP_Tip = BP_TIP_WND.Class;
	else UE_LOG(LogTemp, Warning, TEXT("ATutorialLevel.cpp::%d::LINE:: BP_TIP_WND is not loaded !"), __LINE__);
}

void ATutorialLevel::BeginPlay()
{
	Super::BeginPlay();

}

void ATutorialLevel::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ATutorialLevel::UpdateExplanation()
{

}


