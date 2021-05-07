#include "DungeonResultWnd.h"

#include "Single/GameInstance/LCGameInstance.h"
#include "Single/PlayerManager/PlayerManager.h"

#include "Widgets/ClosableWnd/DraggableWnd/InventoryWnd/ItemSlot/ItemSlot.h"
#include "Widgets/ClosableWnd/DraggableWnd/InventoryWnd/InventoryWnd.h"
#include "Widgets/WidgetControllerWidget/WidgetControllerWidget.h"

#include "Components/Overlay.h"
#include "Components/CanvasPanel.h"
#include "Components/CanvasPanelSlot.h"
#include "Components/GridPanel.h"
#include "Components/TextBlock.h"
#include "Components/Button.h"

UDungeonResultWnd::UDungeonResultWnd(const FObjectInitializer& ObjIntializer) :
	Super(ObjIntializer)
{
	static ConstructorHelpers::FClassFinder<UItemSlot> BP_ITEM_SLOT(
		TEXT("WidgetBlueprint'/Game/Resources/Blueprints/Widgets/ClosableWnd/DraggableWnd/Inventory/ItemSlot/BP_ItemSlot.BP_ItemSlot_C'"));
	if (BP_ITEM_SLOT.Succeeded()) BP_ItemSlot = BP_ITEM_SLOT.Class;
}

void UDungeonResultWnd::NativeConstruct()
{
	Super::NativeConstruct();

	Overlay_GameOver->SetVisibility(ESlateVisibility::Hidden);
	Overlay_GameClear->SetVisibility(ESlateVisibility::Hidden);
	CanvasPanel_Reward->SetVisibility(ESlateVisibility::Hidden);

	Button_Exit->OnClicked.AddDynamic(this, &UDungeonResultWnd::OnExitClicked);
}

void UDungeonResultWnd::DungeonResultAnimation(EClearType clearType)
{
	if (clearType == EClearType::CT_None) return;

	switch (clearType)
	{
	case EClearType::CT_Clear :
		PlayAnimation(GameClearAnimation);
		break;
	case EClearType::CT_Fail:
		PlayAnimation(GameOverAnimation);
		break;
	}
}

void UDungeonResultWnd::InitializeReward(int32 kill, int32 monsterCount, int32 exp, int32 silver, TArray<FItemSlotInfo> dropItems)
{
	Text_Kill->SetText(FText::FromString(FString::FromInt(kill)));

	float score = (kill / monsterCount) * 100.0f;

	Text_Score->SetText(FText::FromString(FString::Printf(TEXT("%.0f%%"), score)));

	Text_Exp->SetText(FText::FromString(FString::FromInt(exp)));

	Text_Silver->SetText(FText::FromString(FString::FromInt(silver)));

	UpdateDropItems(dropItems);

	PlayerReward(exp, silver, dropItems);
}

void UDungeonResultWnd::UpdateDropItems(TArray<FItemSlotInfo> dropItems)
{
	const int32 maxColumnCount = 6;
	int32 currentColumnCount = 0;

	for (int32 i = 0; i < dropItems.Num(); ++i)
	{
		auto newItemSlot = CreateWidget<UItemSlot>(
			this, BP_ItemSlot);;

		GridPanel_ItemList->AddChild(newItemSlot);

		// 슬롯 초기화
		newItemSlot->InitializeSlot(
			ESlotType::SLT_ITME,
			dropItems[i].ItemCode, ESkillType::SKT_ITEM);

		newItemSlot->SetSlotItemCount(dropItems[i].ItemCount);

		// 생성한 슬롯을 정렬합니다.
		UWidgetControllerWidget::SortGridPanelElem(
			newItemSlot, maxColumnCount, currentColumnCount);
	}
}

void UDungeonResultWnd::PlayerReward(int32 exp, int32 silver, TArray<FItemSlotInfo> dropItems)
{
	GetManager(UPlayerManager)->GetPlayerInfo()->Exp += exp;
	GetManager(UPlayerManager)->GetPlayerInfo()->Silver += silver;

	// 인벤토리에 아이템을 추가합니다.
	auto playerInventory = GetManager(UPlayerManager)->GetInventory();

	for (int32 i = 0; i < dropItems.Num(); ++i)
	{
		playerInventory->AddItem(dropItems[i]);
	}

	// 인벤토리 창의 은화 갱신
	auto InventoryWnd = playerInventory->GetInventoryWnd();
	if (IsValid(InventoryWnd)) InventoryWnd->UpdateSilver();

}

void UDungeonResultWnd::OnExitClicked()
{
	Cast<ULCGameInstance>(GetGameInstance())->SetNextLevelName(FName(TEXT("LobbyMap")));
	UGameplayStatics::OpenLevel(this, FName(TEXT("LoadingLevel")));
}
