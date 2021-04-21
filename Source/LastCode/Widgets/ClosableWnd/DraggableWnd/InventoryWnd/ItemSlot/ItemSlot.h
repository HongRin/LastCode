#pragma once

#include "Widgets/ClosableWnd/DraggableWnd/DraggableWidget/BaseSlot/BaseSlot.h"
#include "Structures/ItemInfo/ItemInfo.h"
#include "ItemSlot.generated.h"

UCLASS()
class LASTCODE_API UItemSlot : public UBaseSlot
{
	GENERATED_BODY()
	
private:
	class UDataTable* DT_ItemInfo;

private:
	FItemInfo ItemInfo;

	UPROPERTY(meta = (BindWidget))
	class UTextBlock* Text_ItemCount;

public:
	UItemSlot(const FObjectInitializer& objectInitializer);

public:
	virtual void InitializeSlot(ESlotType slotType, FName inCode, ESkillType skillType) override;

	// ������ �̹����� �����մϴ�.
	void UpdateItemImage();

	// ���Կ� ǥ�õǴ� ���ڸ� �����մϴ�.
	/// - itemCount : ǥ�ý�ų ������ ������ �����մϴ�.
	/// - bVisible01Count : 0 �̳� 1 �� ��쿡�� ǥ���� �������� �����մϴ�.
	void SetSlotItemCount(int32 itemCount, bool bVisible01Count = false);

public:
	void SetItemInfo(FName itemCode);

	FORCEINLINE FItemInfo* GetItemInfo()
	{
		return &ItemInfo;
	}
};
