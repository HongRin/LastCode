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

	TSubclassOf<class UShopWnd> BP_ShopWnd;
	class UShopWnd* ShopWnd;

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

	// 상점창을 생성합니다.
	class UShopWnd* CreateShopWnd();

	// 상점 창을 닫습니다.
	void CloseShopWnd();

	// 상점 창을 토글합니다.
	void ToggleShopWnd();

public :
	UFUNCTION()
	void FieldListButtonClicked();

	UFUNCTION()
	void ShopButtonClicked();
};
