#pragma once

#include "LastCode.h"
#include "Engine/LevelScriptActor.h"
#include "LoadingLevel.generated.h"

UCLASS()
class LASTCODE_API ALoadingLevel : public ALevelScriptActor
{
	GENERATED_BODY()
	
private :
	TSubclassOf<class UUserWidget> BP_LoadingWnd;

public :
	ALoadingLevel();

protected:
	virtual void BeginPlay() override;
};
