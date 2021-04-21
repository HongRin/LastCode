#include "TitleLevel.h"
#include "Widgets/TitleWnd/TitleWnd.h"

ATitleLevel::ATitleLevel()
{
	static ConstructorHelpers::FClassFinder<UTitleWnd> BP_TITLE_WND(
		TEXT("WidgetBlueprint'/Game/Resources/Blueprints/Widgets/TitleWnd/BP_TitleWnd.BP_TitleWnd_C'"));
	if (BP_TITLE_WND.Succeeded()) BP_TitleWnd = BP_TITLE_WND.Class;
	else UE_LOG(LogTemp, Warning, TEXT("ATitleLevel.cpp::%d::LINE:: BP_TITLE_WND is not loaded !"), __LINE__);
}

void ATitleLevel::BeginPlay()
{
	Super::BeginPlay();

	CreateWidget<UTitleWnd>(GetWorld(), BP_TitleWnd)->AddToViewport();
}
