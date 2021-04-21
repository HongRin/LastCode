#include "LoadingLevel.h"

#include "UserWidget.h"
#include "Engine/World.h"

ALoadingLevel::ALoadingLevel()
{
	static ConstructorHelpers::FClassFinder<UUserWidget> BP_LOADING_WND(
		TEXT("WidgetBlueprint'/Game/Resources/Blueprints/Widgets/LoadingWnd/BP_LoadingWnd.BP_LoadingWnd_C'"));
	if (BP_LOADING_WND.Succeeded()) BP_LoadingWnd = BP_LOADING_WND.Class;
	else UE_LOG(LogTemp, Error, TEXT("ALoadingLevel.cpp::%d::LINE:: BP_LOADING_WND is not loaded!"), __LINE__);
}

void ALoadingLevel::BeginPlay()
{
	Super::BeginPlay();

	CreateWidget<UUserWidget>(GetWorld(), BP_LoadingWnd)->AddToViewport();
}
