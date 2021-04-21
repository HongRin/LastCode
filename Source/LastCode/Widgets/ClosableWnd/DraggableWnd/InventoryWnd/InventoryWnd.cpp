#include "InventoryWnd.h"

#include "Single/GameInstance/LCGameInstance.h"
#include "Single/PlayerManager/PlayerManager.h"

#include "Widgets/ClosableWnd/DraggableWnd/InventoryWnd/ItemSlot/InventoryItemSlot.h"
#include "Widgets/WidgetControllerWidget/WidgetControllerWidget.h"

#include "Components/GridPanel.h"
#include "Components/GridSlot.h"
#include "Components/TextBlock.h"

UInventoryWnd::UInventoryWnd(const FObjectInitializer& ObjectInitializer)
{
	static ConstructorHelpers::FClassFinder<UInventoryItemSlot> BP_INVENTORY_ITEM_SLOT(
		TEXT("WidgetBlueprint'/Game/Resources/Blueprints/Widgets/ClosableWnd/DraggableWnd/Inventory/ItemSlot/BP_InventoryItemSlot.BP_InventoryItemSlot_C'"));
	if (BP_INVENTORY_ITEM_SLOT.Succeeded()) BP_InventoryItemSlot = BP_INVENTORY_ITEM_SLOT.Class;
}

void UInventoryWnd::NativeConstruct()
{
	Super::NativeConstruct();

	WndSize = FVector2D(500.0f, 600.0f);

	InitializeInventoryWnd();

	// 소지금 갱신
	UpdateSilver();
}

void UInventoryWnd::InitializeInventoryWnd()
{
#pragma region Create Inventory Slots

	// 플레이어 캐릭터 정보를 얻습니다.
	auto playerInfo = GetManager(UPlayerManager)->GetPlayerInfo();

	// 인벤토리 슬롯 개수를 얻습니다.
	int32 inventorySlotCount = playerInfo->InventorySlotCount;

	const int32 maxColumnCount = 7;
	int32 currentColumnCount = 0;

	// 인벤토리 슬롯들을 생성합니다.
	for (int32 i = 0; i < inventorySlotCount; ++i)
	{
		// 인벤토리 슬롯을 생성합니다.
		auto newItemSlot = CreateItemSlot();

		// 슬롯 초기화
		newItemSlot->InitializeItemSlot(
			ESlotType::SLT_INVENTORY,
			playerInfo->InventoryItemInfos[i].ItemCode, ESkillType::SKT_ITEM, i);

		// 생성한 슬롯을 정렬합니다.
		UWidgetControllerWidget::SortGridPanelElem(
			newItemSlot, maxColumnCount, currentColumnCount);
	}
#pragma endregion
}

UInventoryItemSlot* UInventoryWnd::CreateItemSlot()
{
	// 인벤토리 슬롯을 생성합니다.
	auto newItemSlot = CreateWidget<UInventoryItemSlot>(
		this, BP_InventoryItemSlot);

	ItemSlots.Add(newItemSlot);

	// GridPanel_ItemSlots 의 자식 위젯으로 추가합니다.
	GridPanel_ItemSlots->AddChild(newItemSlot);

	// 생성한 인벤토리 슬롯을 반환합니다.
	return newItemSlot;
}

void UInventoryWnd::UpdateSilver()
{
	FText silverToText = FText::FromString(FString::FromInt(GetManager(UPlayerManager)->GetPlayerInfo()->Silver));
	Text_Silver->SetText(silverToText);
}
