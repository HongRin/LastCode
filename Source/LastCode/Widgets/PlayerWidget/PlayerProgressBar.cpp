#include "PlayerProgressBar.h"
#include "Actors/Characters/PlayerCharacter/PlayableCharacter.h"

#include "Components/ProgressBar.h"
#include "Components/TextBlock.h"
#include "Single/GameInstance/LCGameInstance.h"
#include "Single/PlayerManager/PlayerManager.h"

void UPlayerProgressBar::NativeConstruct()
{
	Super::NativeConstruct();

	PlayableCharacter = GetManager(UPlayerManager)->GetPlayableCharacter();

	GetManager(UPlayerManager)->GetPlayerStateManager()->OnUpdateHp.AddLambda([this](void) {
		if (PlayableCharacter->GetHp() <= 0) PlayableCharacter->SetHp(0.0f);
		else if (PlayableCharacter->GetHp() >= PlayableCharacter->GetMaxHp()) 
			PlayableCharacter->SetHp(PlayableCharacter->GetMaxHp());
		ProgressBar_Hp->SetPercent(PlayableCharacter->GetHp() / PlayableCharacter->GetMaxHp());
		Text_Hp->SetText(FText::FromString(
			FString::Printf(TEXT("%.0f%%"), (PlayableCharacter->GetHp() / PlayableCharacter->GetMaxHp()) * 100.0f)));
	});

	GetManager(UPlayerManager)->GetPlayerStateManager()->OnUpdateStamina.AddLambda([this](void) {
		if (PlayableCharacter->GetStamina() <= 0) PlayableCharacter->SetStamina(0.0f);
		else if (PlayableCharacter->GetStamina() >= PlayableCharacter->GetMaxStamina())
			PlayableCharacter->SetStamina(PlayableCharacter->GetMaxStamina());
		ProgressBar_Stamina->SetPercent(PlayableCharacter->GetStamina() / PlayableCharacter->GetMaxStamina());
		Text_Stamina->SetText(FText::FromString(
			FString::Printf(TEXT("%.0f / %.0f"), PlayableCharacter->GetStamina(), PlayableCharacter->GetMaxStamina())));
		});
}
