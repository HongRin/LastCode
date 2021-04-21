#include "PlayerManager.h"
#include "Actors/Controllers/PlayerController/PlayableController/PlayableController.h"
#include "Actors/Characters/PlayerCharacter/PlayableCharacter.h"

void UPlayerManager::RegisterPlayer(ABasePlayerController* newPlayerController, APlayableCharacter* newPlayerCharacter)
{
	PlayableController = newPlayerController;
	PlayableCharacter = newPlayerCharacter;
}

void UPlayerManager::InitManagerClass()
{
	SkillState = NewObject<USkillState>(this, USkillState::StaticClass(),
		NAME_None, EObjectFlags::RF_MarkAsRootSet);

	QuickManager = NewObject<UQuickManager>(this, UQuickManager::StaticClass(),
		NAME_None, EObjectFlags::RF_MarkAsRootSet);

	Inventory = NewObject<UInventory>(this, UInventory::StaticClass(),
		NAME_None, EObjectFlags::RF_MarkAsRootSet);

	PlayerStateManager = NewObject<UPlayerStateManager>(this, UPlayerStateManager::StaticClass(),
		NAME_None, EObjectFlags::RF_MarkAsRootSet);
}

void UPlayerManager::ShutdownManagerClass()
{
	if (SkillState->IsValidLowLevel()) return;
	SkillState->ConditionalBeginDestroy();

	if (QuickManager->IsValidLowLevel()) return;
	QuickManager->ConditionalBeginDestroy();

	if (Inventory->IsValidLowLevel()) return;
	Inventory->ConditionalBeginDestroy();

	if (PlayerStateManager->IsValidLowLevel()) return;
	PlayerStateManager->ConditionalBeginDestroy();
}
