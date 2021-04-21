#pragma once

#include "LastCode.h"
#include "Engine/LevelScriptActor.h"
#include "TitleLevel.generated.h"

UCLASS()
class LASTCODE_API ATitleLevel : public ALevelScriptActor
{
	GENERATED_BODY()

private :
	TSubclassOf<class UTitleWnd> BP_TitleWnd;

public :
	ATitleLevel();

protected :
	virtual void BeginPlay() override;
	
};
