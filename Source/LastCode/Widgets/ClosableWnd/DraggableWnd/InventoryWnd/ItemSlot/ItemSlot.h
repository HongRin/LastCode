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

	// 아이템 이미지를 갱신합니다.
	void UpdateItemImage();

	// 슬롯에 표시되는 숫자를 설정합니다.
	/// - itemCount : 표시시킬 아이템 개수를 전달합니다.
	/// - bVisible01Count : 0 이나 1 일 경우에도 표시할 것인지를 전달합니다.
	void SetSlotItemCount(int32 itemCount, bool bVisible01Count = false);

public:
	void SetItemInfo(FName itemCode);

	FORCEINLINE FItemInfo* GetItemInfo()
	{
		return &ItemInfo;
	}
};
