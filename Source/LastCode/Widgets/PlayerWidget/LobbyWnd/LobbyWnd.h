#pragma once

#include "LastCode.h"
#include "Blueprint/UserWidget.h"
#include "Enums/InputModeType.h"

#include "LobbyWnd.generated.h"

UCLASS()
class LASTCODE_API ULobbyWnd : public UUserWidget
{
	GENERATED_BODY()

private :
	TSubclassOf<class UFieldListWnd> BP_FieldListWnd;
	class UFieldListWnd* FieldListWnd;

	class UWidgetControllerWidget* WidgetController;

private :
	UPROPERTY(meta = (BindWidget))
	class UButton* Button_Mission;

	UPROPERTY(meta = (BindWidget))
	class UButton* Button_Shop;

	UPROPERTY(meta = (BindWidget))
	class UButton* Button_FieldList;

public :
	ULobbyWnd(const FObjectInitializer& ObjInitializer);

protected :
	virtual void NativeConstruct() override;

private :
	// 인벤토리 창을 생성합니다.
	class UFieldListWnd* CreateFieldListWnd();

	// 인벤토리 창을 닫습니다.
	void CloseFieldListWnd();

	// 인벤토리 창을 토글합니다.
	void ToggleFieldListWnd();

public :
	UFUNCTION()
	void FieldListButtonClicked();
};
