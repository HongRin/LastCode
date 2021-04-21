#include "TitleWnd.h"

#include "Components/Button.h"
#include "Single/GameInstance/LCGameInstance.h"


void UTitleWnd::NativeConstruct()
{
	Super::NativeConstruct();

	Button_Play->OnClicked.AddDynamic(this, &UTitleWnd::PlayButtonClicked);
	Button_Exit->OnClicked.AddDynamic(this, &UTitleWnd::ExitButtonClicked);
}

void UTitleWnd::PlayButtonClicked()
{
	Cast<ULCGameInstance>(GetGameInstance())->SetNextLevelName(FName(TEXT("SelectCharacterMap")));
	UGameplayStatics::OpenLevel(this, FName(TEXT("LoadingLevel")));
}

void UTitleWnd::ExitButtonClicked()
{
	UE_LOG(LogTemp, Warning, TEXT("Exit"));

	UKismetSystemLibrary::QuitGame(
		GetWorld(),
		UGameplayStatics::GetPlayerController(GetWorld(), 0),
		EQuitPreference::Quit,
		false);
}
