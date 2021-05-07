#pragma once

#include "LastCode.h"
#include "Engine/LevelScriptActor.h"
#include "Enums/ClearType.h"
#include "Structures/ItemSlotInfo/ItemSlotInfo.h"
#include "DungeonLevel.generated.h"

UCLASS()
class LASTCODE_API ADungeonLevel : public ALevelScriptActor
{
	GENERATED_BODY()
	
private :
	TSubclassOf<class UDungeonResultWnd> BP_DungeonResultWnd;

	class UDungeonResultWnd* ResultWnd;
	
	TArray<class AEnemyCharacter*> EnemyCharacters;

	EClearType ClearType;

	int32 FirstMonsterCount;

	int32 RewardExp;

	int32 RewardSilver;

	int32 Kill;

	TArray<FItemSlotInfo> DropItems;

public:
	ADungeonLevel();

protected:
	virtual void BeginPlay() override;

public :
	 void DungeonClear();

public:
	FORCEINLINE void AddEnemyCharacters(class AEnemyCharacter* enemyCharacter)
	{
		EnemyCharacters.Add(enemyCharacter);
	}

	void RemoveEnemyCharacters(class AEnemyCharacter* enemyCharacter);

	void SetDropItems(FName itemCode, int32 maxSlotCount);

	FORCEINLINE void AddRewardSilver(int32 silver)
	{ RewardSilver += silver; }

	FORCEINLINE void AddRewardExp(int32 exp)
	{ RewardExp += exp; }

};
