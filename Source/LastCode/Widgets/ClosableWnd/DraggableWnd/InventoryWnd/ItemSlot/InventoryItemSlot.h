#pragma once

#include "Widgets/ClosableWnd/DraggableWnd/InventoryWnd/ItemSlot/ItemSlot.h"
#include "InventoryItemSlot.generated.h"

UCLASS()
class LASTCODE_API UInventoryItemSlot : public UItemSlot
{
	GENERATED_BODY()
	
private:
	// �κ��丮 ���� �ε����� ��Ÿ���ϴ�.
	int32 ItemSlotIndex;

protected:
	virtual void NativeConstruct() override;

public:
	void InitializeItemSlot(ESlotType slotType, FName itemCode, ESkillType skillType, int32 itemSlotIndex);

	// ������ ������ �����մϴ�.
	void UpdateInventoryItemSlot();

private:
	// ������ ���� �ؽ�Ʈ�� �����մϴ�.
	void UpdateItemCountText();

public:
	FORCEINLINE int32 GetItemSlotIndex() const
	{
		return ItemSlotIndex;
	}


};
