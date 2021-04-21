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

	//if (!IsValid(TipWnd))
	//{
	//	TipWnd = CreateWidget<UTipWnd>(GetWorld(), BP_Tip);
	//	TipWnd->AddToViewport();
	//	TipWnd->SetExplanation(FText::FromString(TEXT("W,A,S,D 키를 누르시면 이동합니다.")));
	//}
	//
	//PlayableCharacter = Cast<APlayableCharacter>(GetManager(UPlayerManager)->GetPlayableController()->GetPawn());
	//
	//ExplanationLevel = 1;
}

void ATutorialLevel::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	//UpdateExplanation();
}

void ATutorialLevel::UpdateExplanation()
{
	//switch (ExplanationLevel)
	//{
	//case 1 :
	//	if (PlayableCharacter->GetVelocity().Size() > 200.0f)
	//	{
	//		TipWnd->SetExplanation(FText::FromString(TEXT("Shift 키를 누르시면 달리실 수 있습니다.")));
	//		ExplanationLevel = 2;
	//	}
	//	break;
	//case 2:
	//	if (PlayableCharacter->GetVelocity().Size() > 500.0f)
	//	{
	//		TipWnd->SetExplanation(FText::FromString(TEXT("Space 키를 누르시면 점프합니다.")));
	//		ExplanationLevel = 3;
	//	}
	//	break;
	//case 3:
	//	if (PlayableCharacter->IsInAir())
	//	{
	//		TipWnd->SetExplanation(FText::FromString(TEXT("마우스 오른쪽, 왼쪽키로 공격을 하실 수 있습니다.")));
	//		ExplanationLevel = 4;
	//	}
	//	break;
	//}
}


