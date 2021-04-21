#pragma once

#include "LastCode.h"
#include "UObject/NoExportTypes.h"

#include "Structures/ItemSlotInfo/ItemSlotInfo.h"

#include "Enums/InputModeType.h"

#include "Inventory.generated.h"

DECLARE_MULTICAST_DELEGATE(FOnInventorySlotChangedSignature)

UCLASS()
class LASTCODE_API UInventory : public UObject
{
	GENERATED_BODY()

public :
	FOnInventorySlotChangedSignature OnInventorySlotChanged;


private:
	TSubclassOf<class UInventoryWnd> BP_InventoryWnd;

private:
	UPROPERTY()
		class UInventoryWnd* InventoryWnd;

public:
	UInventory();

public:
	// �κ��丮 â�� �����մϴ�.
	class UInventoryWnd* CreateInventoryWnd(
		class UWidgetControllerWidget* widgetController,
		EInputModeType changeInputMode = EInputModeType::IM_Default, bool bShowCursor = true);

	// �κ��丮 â�� �ݽ��ϴ�.
	void CloseInventoryWnd();

	// �κ��丮 â�� ����մϴ�.
	void ToggleInventoryWnd(class UWidgetControllerWidget* widgetController);

	// ������ ���� ������ ����ϴ�.
	FItemSlotInfo* GetItemSlotInfo(int32 slotIndex) const;

	// �κ��丮 �������� ��ü�մϴ�.
	void SwapItem(class UInventoryItemSlot* first, class UInventoryItemSlot* second);


	// �������� �κ��丮���� �����մϴ�.
	/// - itemSlotIndex : ������ ���� �ε����� �����մϴ�.
	/// - removeCount : ������ ������ �����մϴ�.
	void RemoveItem(int32 itemSlotIndex, int32 removeCount = 1);

};
