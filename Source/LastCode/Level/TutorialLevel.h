#pragma once

#include "LastCode.h"
#include "Engine/LevelScriptActor.h"
#include "TutorialLevel.generated.h"

UCLASS()
class LASTCODE_API ATutorialLevel : public ALevelScriptActor
{
	GENERATED_BODY()

private :
	TSubclassOf<class UUserWidget> BP_Tip;
	class UTipWnd* TipWnd;

	class APlayableCharacter* PlayableCharacter;

	int32 ExplanationLevel;

public :
	ATutorialLevel();

protected :
	virtual void BeginPlay() override;

	virtual void Tick(float DeltaTime) override;

private :
	void UpdateExplanation();

};
