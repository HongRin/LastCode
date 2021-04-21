#pragma once

#include "LastCode.h"
#include "Engine/LevelScriptActor.h"
#include "LobbyLevel.generated.h"

UCLASS()
class LASTCODE_API ALobbyLevel : public ALevelScriptActor
{
	GENERATED_BODY()

private :
	TSubclassOf<class ULobbyWnd> BP_LobbyWnd;

	class ULobbyWnd* LobbyWnd;

public :
	ALobbyLevel();

protected:
	virtual void BeginPlay() override;
	
};
