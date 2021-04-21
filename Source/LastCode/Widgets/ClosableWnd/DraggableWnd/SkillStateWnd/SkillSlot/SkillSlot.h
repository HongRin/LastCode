#pragma once

#include "Widgets/ClosableWnd/DraggableWnd/DraggableWidget/BaseSlot/BaseSlot.h"
#include "SkillSlot.generated.h"

UCLASS()
class LASTCODE_API USkillSlot : public UBaseSlot
{
	GENERATED_BODY()

private :
	class USkillStateRow* SkillStateRow;

	struct FSkillInfo SkillInfo;

public:
	USkillSlot(const FObjectInitializer& ObjInitializer);

protected :
	void NativeConstruct() override;

public :
	void UpdateSkillSlot(struct FSkillInfo activeSkillInfo);

public :
	// 슬롯을 초기화합니다.
	virtual void InitializeSlot(ESlotType slotType, FName inCode, ESkillType skillType) override;
public:
	FORCEINLINE void SetSkillStateRow(class USkillStateRow* skillStateRow)
	{ SkillStateRow = skillStateRow; }
};
