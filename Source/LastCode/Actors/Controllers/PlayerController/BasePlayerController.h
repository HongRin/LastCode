#pragma once

#include "LastCode.h"
#include "GameFramework/PlayerController.h"
#include "Enums/InputModeType.h"
#include "BasePlayerController.generated.h"

UCLASS()
class  LASTCODE_API ABasePlayerController : public APlayerController
{
	GENERATED_BODY()

private:
	TSubclassOf<class UWidgetControllerWidget> BP_WidgetController;

private:
	UPROPERTY()
		class UWndTogglerComponent* WndToggler;

protected:
	class UWidgetControllerWidget* WidgetControllerWidget;
	EInputModeType DefaultInputMode;
	bool bDefaultCursorVisibility;

public:
	ABasePlayerController();

protected:
	virtual void OnPossess(APawn* aPawn) override;


public:
	FORCEINLINE class UWidgetControllerWidget* GetWidgetControllerWidget() const
	{
		return WidgetControllerWidget;
	}

	FORCEINLINE class UWndTogglerComponent* GetWndToggler() const
	{
		return WndToggler;
	}

	FORCEINLINE EInputModeType GetDefaultInputMode() const
	{
		return DefaultInputMode;
	}

	FORCEINLINE bool GetDefaultCursorVisibility() const
	{
		return bDefaultCursorVisibility;
	}

	FORCEINLINE void SetInputModeFromNewInputModeType(EInputModeType newInputMode)
	{
		switch (newInputMode)
		{
		case EInputModeType::IM_GameOnly:	SetInputMode(FInputModeGameOnly());		break;
		case EInputModeType::IM_UIOnly:		SetInputMode(FInputModeUIOnly());		break;
		case EInputModeType::IM_GameAndUI:	SetInputMode(FInputModeGameAndUI());	break;
		}
	}

	FORCEINLINE void ChangeInputModeToDefault()
	{
		switch (DefaultInputMode)
		{
		case EInputModeType::IM_GameOnly:	SetInputMode(FInputModeGameOnly());		break;
		case EInputModeType::IM_UIOnly:		SetInputMode(FInputModeUIOnly());		break;
		case EInputModeType::IM_GameAndUI:	SetInputMode(FInputModeGameAndUI());	break;
		}
	}

	// 카메라 뷰 타깃을 변경합니다.
	/// - targetActor : 변경할 뷰 타깃 카메라 컴포넌트를 갖는 액터를 전달합니다.
	/// - blendTime : 블랜딩 시간을 전달합니다.
	void ChangeViewTarget(class AActor* targetActor, float blendTime = 0.5f);

	void ResetViewTarget(float blendTime = 0.5f);
};