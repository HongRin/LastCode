#pragma once

#include "LastCode.h"
#include "GameFramework/PlayerController.h"
#include "PreviewCharacterController.generated.h"

UCLASS()
class LASTCODE_API APreviewCharacterController : public APlayerController
{
	GENERATED_BODY()
	
private :
	// 게임 위젯에 대한 UClass 와 인스턴스를 나타냅니다.
	TSubclassOf<class USelectClassWnd> SelectClassWnd;

	class USelectClassWnd* PreviewCharacterWidgetInstance;

public:
	APreviewCharacterController();

protected:
	virtual void SetupInputComponent() override;
	virtual void OnPossess(APawn* aPawn) override;

private:
	void InputMouseX(float axis);
	void InputMouseY(float axis);

public:
	class USelectClassWnd* GetPreviewCharacterWidgetInstance();
};
