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
	// �κ��丮 â�� �����մϴ�.
	class UFieldListWnd* CreateFieldListWnd();

	// �κ��丮 â�� �ݽ��ϴ�.
	void CloseFieldListWnd();

	// �κ��丮 â�� ����մϴ�.
	void ToggleFieldListWnd();

public :
	UFUNCTION()
	void FieldListButtonClicked();
};
