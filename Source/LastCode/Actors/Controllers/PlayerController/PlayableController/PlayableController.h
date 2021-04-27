#pragma once

#include "CoreMinimal.h"
#include "Actors/Controllers/PlayerController/BasePlayerController.h"
#include "PlayableController.generated.h"

UCLASS()
class LASTCODE_API APlayableController : public ABasePlayerController
{
	GENERATED_BODY()
	
protected:
	virtual void SetupInputComponent() override;
	virtual void OnPossess(APawn* aPawn) override;
	virtual void OnUnPossess() override;

private:
	void RegisterToggleEvent();

private:
	void InputMouseX(float axis);
	void InputMouseY(float axis);

};
