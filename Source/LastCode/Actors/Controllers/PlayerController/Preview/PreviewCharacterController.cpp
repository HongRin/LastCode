#include "PreviewCharacterController.h"
#include "Actors/Characters/PlayerCharacter/Preview/PreviewCharacter.h"
#include "Widgets/SelectClassWnd/SelectClassWnd.h"

APreviewCharacterController::APreviewCharacterController()
{
	static ConstructorHelpers::FClassFinder<USelectClassWnd> SELECT_CLASS_WND(
		TEXT("WidgetBlueprint'/Game/Resources/Blueprints/Widgets/SelectClassWnd/BP_SelectClassWnd.BP_SelectClassWnd_C'"));
	if (SELECT_CLASS_WND.Succeeded()) SelectClassWnd = SELECT_CLASS_WND.Class;
	else UE_LOG(LogTemp, Warning, TEXT("APreviewCharacterController.cpp::%d::LINE::SELECT_CLASS_WND is not loaded !"), __LINE__);
}

void APreviewCharacterController::SetupInputComponent()
{
	Super::SetupInputComponent();

	InputComponent->BindAxis(TEXT("MouseX"), this, &APreviewCharacterController::InputMouseX);
	InputComponent->BindAxis(TEXT("MouseY"), this, &APreviewCharacterController::InputMouseY);
}

void APreviewCharacterController::OnPossess(APawn* aPawn)
{
	Super::OnPossess(aPawn);

	SetInputMode(FInputModeGameAndUI()); 
	bShowMouseCursor = true;

	GetPreviewCharacterWidgetInstance();
}

void APreviewCharacterController::InputMouseX(float axis)
{ AddYawInput(axis); }

void APreviewCharacterController::InputMouseY(float axis)
{ AddPitchInput(axis); }

USelectClassWnd* APreviewCharacterController::GetPreviewCharacterWidgetInstance()
{
	if (!IsValid(PreviewCharacterWidgetInstance))
	{
		PreviewCharacterWidgetInstance = CreateWidget<USelectClassWnd>(this, SelectClassWnd);
		PreviewCharacterWidgetInstance->SetPreviewCharacter(Cast<APreviewCharacter>(GetPawn()));
		PreviewCharacterWidgetInstance->AddToViewport();
	}

	return PreviewCharacterWidgetInstance;
}
