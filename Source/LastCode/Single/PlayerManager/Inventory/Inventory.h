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
	// 인벤토리 창을 생성합니다.
	class UInventoryWnd* CreateInventoryWnd(
		class UWidgetControllerWidget* widgetController,
		EInputModeType changeInputMode = EInputModeType::IM_Default, bool bShowCursor = true);

	// 인벤토리 창을 닫습니다.
	void CloseInventoryWnd();

	// 인벤토리 창을 토글합니다.
	void ToggleInventoryWnd(class UWidgetControllerWidget* widgetController);

	// 아이템 슬롯 정보를 얻습니다.
	FItemSlotInfo* GetItemSlotInfo(int32 slotIndex) const;

	// 인벤토리 아이템을 교체합니다.
	void SwapItem(class UInventoryItemSlot* first, class UInventoryItemSlot* second);


	// 아이템을 인벤토리에서 제거합니다.
	/// - itemSlotIndex : 제거할 슬롯 인덱스를 전달합니다.
	/// - removeCount : 제거할 개수를 전달합니다.
	void RemoveItem(int32 itemSlotIndex, int32 removeCount = 1);

};
