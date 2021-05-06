#include "DungeonLevel.h"

#include "Engine/World.h"
#include "Engine/EngineTypes.h"
#include "UserWidget.h"

#include "Actors/Characters/PlayerCharacter/PlayableCharacter.h"
#include "Actors/Characters/EnemyCharacter/EnemyCharacter.h"

#include "Single/GameInstance/LCGameInstance.h"
#include "Single/PlayerManager/PlayerManager.h"


ADungeonLevel::ADungeonLevel()
{

}

void ADungeonLevel::BeginPlay()
{
	Super::BeginPlay();

}

EClearType ADungeonLevel::DungeonClear()
{
	if (EnemyCharacters.Num() == 0) return EClearType::CT_Clear;
	else if (GetManager(UPlayerManager)->GetPlayableCharacter()->IsDie()) return EClearType::CT_Fail;

	return EClearType::CT_None;
}
