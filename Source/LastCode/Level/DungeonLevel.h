#pragma once

#include "CoreMinimal.h"
#include "Engine/LevelScriptActor.h"
#include "Enums/ClearType.h"
#include "DungeonLevel.generated.h"

UCLASS()
class LASTCODE_API ADungeonLevel : public ALevelScriptActor
{
	GENERATED_BODY()
	
private :
	TArray<class AEnemyCharacter*> EnemyCharacters;


public:
	ADungeonLevel();

protected:
	virtual void BeginPlay() override;

public :
	 EClearType DungeonClear();

public:
	FORCEINLINE void AddEnemyCharacters(class AEnemyCharacter* enemyCharacter)
	{
		EnemyCharacters.Add(enemyCharacter);
	}

	FORCEINLINE void RemoveEnemyCharacters(class AEnemyCharacter* enemyCharacter)
	{
		EnemyCharacters.Remove(enemyCharacter);
	};

};
