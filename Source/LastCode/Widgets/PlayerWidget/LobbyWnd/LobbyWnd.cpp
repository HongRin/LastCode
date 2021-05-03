#include "LobbyWnd.h"

#include "Components/Button.h"
#include "Components/CanvasPanel.h"
#include "Components/CanvasPanelSlot.h"

#include "Actors/Controllers/PlayerController/PlayableController/PlayableController.h"

#include "Single/GameInstance/LCGameInstance.h"
#include "Single/PlayerManager/PlayerManager.h"

#include "Widgets/WidgetControllerWidget/WidgetControllerWidget.h"
#include "Widgets/PlayerWidget/LobbyWnd/FieldListWnd/FieldListWnd.h"
#include "Widgets/ClosableWnd/DraggableWnd/ShopWnd/ShopWnd.h"

ULobbyWnd::ULobbyWnd(const FObjectInitializer& ObjInitializer) :
	Super(ObjInitializer)
{
	static ConstructorHelpers::FClassFinder<UFieldListWnd> BP_FIELD_LIST_WND(
		TEXT("WidgetBlueprint'/Game/Resources/Blueprints/Widgets/PlayerWidget/FieldList/BP_FieldListWnd.BP_FieldListWnd_C'"));
	if (BP_FIELD_LIST_WND.Succeeded()) BP_FieldListWnd = BP_FIELD_LIST_WND.Class;
	else UE_LOG(LogTemp, Error, TEXT("ULobbyWnd.cpp::%d::LINE:: BP_FIELD_LIST_WND is not loaed!"), __LINE__);

	static ConstructorHelpers::FClassFinder<UShopWnd> BP_SHOP_WND(
		TEXT("WidgetBlueprint'/Game/Resources/Blueprints/Widgets/ClosableWnd/DraggableWnd/Shop/BP_ShopWnd.BP_ShopWnd_C'"));
	if (BP_SHOP_WND.Succeeded()) BP_ShopWnd = BP_SHOP_WND.Class;
	else UE_LOG(LogTemp, Error, TEXT("ULobbyWnd.cpp::%d::LINE:: BP_SHOP_WND is not loaed!"), __LINE__);
}

void ULobbyWnd::NativeConstruct()
{
	Super::NativeConstruct();

	Button_FieldList->OnClicked.AddDynamic(this, &ULobbyWnd::FieldListButtonClicked);

	Button_Shop->OnClicked.AddDynamic(this, &ULobbyWnd::ShopButtonClicked);


	WidgetController = GetManager(UPlayerManager)->GetPlayableController()->GetWidgetControllerWidget();

}

UFieldListWnd* ULobbyWnd::CreateFieldListWnd()
{
	if (IsValid(FieldListWnd)) return FieldListWnd;
	WidgetController->CloseWnd(true);
	FieldListWnd = CreateWidget<UFieldListWnd>(WidgetController, BP_FieldListWnd);
	WidgetController->AddChildWidget(FieldListWnd, EInputModeType::IM_UIOnly, true, 1100.0f, 700.0f);
	Cast<UCanvasPanelSlot>(FieldListWnd->Slot)->SetAnchors(FAnchors(1.0f, 1.0f, 1.0f, 1.0f));
	Cast<UCanvasPanelSlot>(FieldListWnd->Slot)->SetAlignment(FVector2D(1.37f, 1.3f));

	return FieldListWnd;
}

void ULobbyWnd::CloseFieldListWnd()
{
	if (IsValid(FieldListWnd))
	{
		WidgetController->CloseChildWidget(FieldListWnd);
		FieldListWnd = nullptr;

		ABasePlayerController* playableController = GetManager(UPlayerManager)->GetPlayableController();

		playableController->ChangeInputModeToDefault();

		playableController->bShowMouseCursor = playableController->GetDefaultCursorVisibility();
	}
}

void ULobbyWnd::ToggleFieldListWnd()
{
	if (IsValid(FieldListWnd)) CloseFieldListWnd();
	else CreateFieldListWnd();
}

UShopWnd* ULobbyWnd::CreateShopWnd()
{
	if (IsValid(ShopWnd)) return ShopWnd;
	ShopWnd = Cast<UShopWnd>(WidgetController->CreateWnd(BP_ShopWnd));

	return ShopWnd;
}

void ULobbyWnd::CloseShopWnd()
{
	if (IsValid(ShopWnd))
	{
		ShopWnd->CloseThisWnd();
		ShopWnd = nullptr;
	}
}

void ULobbyWnd::ToggleShopWnd()
{
	if (IsValid(ShopWnd)) CloseShopWnd();
	else CreateShopWnd();
}

void ULobbyWnd::FieldListButtonClicked()
{
	ToggleFieldListWnd();
}

void ULobbyWnd::ShopButtonClicked()
{
	ToggleShopWnd();
}
