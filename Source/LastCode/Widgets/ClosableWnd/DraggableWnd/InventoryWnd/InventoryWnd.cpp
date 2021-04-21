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

	// ������ ����
	UpdateSilver();
}

void UInventoryWnd::InitializeInventoryWnd()
{
#pragma region Create Inventory Slots

	// �÷��̾� ĳ���� ������ ����ϴ�.
	auto playerInfo = GetManager(UPlayerManager)->GetPlayerInfo();

	// �κ��丮 ���� ������ ����ϴ�.
	int32 inventorySlotCount = playerInfo->InventorySlotCount;

	const int32 maxColumnCount = 7;
	int32 currentColumnCount = 0;

	// �κ��丮 ���Ե��� �����մϴ�.
	for (int32 i = 0; i < inventorySlotCount; ++i)
	{
		// �κ��丮 ������ �����մϴ�.
		auto newItemSlot = CreateItemSlot();

		// ���� �ʱ�ȭ
		newItemSlot->InitializeItemSlot(
			ESlotType::SLT_INVENTORY,
			playerInfo->InventoryItemInfos[i].ItemCode, ESkillType::SKT_ITEM, i);

		// ������ ������ �����մϴ�.
		UWidgetControllerWidget::SortGridPanelElem(
			newItemSlot, maxColumnCount, currentColumnCount);
	}
#pragma endregion
}

UInventoryItemSlot* UInventoryWnd::CreateItemSlot()
{
	// �κ��丮 ������ �����մϴ�.
	auto newItemSlot = CreateWidget<UInventoryItemSlot>(
		this, BP_InventoryItemSlot);

	ItemSlots.Add(newItemSlot);

	// GridPanel_ItemSlots �� �ڽ� �������� �߰��մϴ�.
	GridPanel_ItemSlots->AddChild(newItemSlot);

	// ������ �κ��丮 ������ ��ȯ�մϴ�.
	return newItemSlot;
}

void UInventoryWnd::UpdateSilver()
{
	FText silverToText = FText::FromString(FString::FromInt(GetManager(UPlayerManager)->GetPlayerInfo()->Silver));
	Text_Silver->SetText(silverToText);
}
