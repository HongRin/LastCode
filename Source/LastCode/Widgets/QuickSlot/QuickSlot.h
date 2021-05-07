#pragma once

#include "CoreMinimal.h"
#include "Widgets/ClosableWnd/DraggableWnd/DraggableWidget/BaseSlot/BaseSlot.h"
#include "Structures/QuickSlotInfo/QuickSlotInfo.h"
#include "Structures/QuickSlotSkillIfno/QuickSlotSkillInfo.h"
#include "QuickSlot.generated.h"

UCLASS()
class LASTCODE_API UQuickSlot : public UBaseSlot
{
	GENERATED_BODY()


private:
	TSubclassOf<class USkillDetailWnd> BP_SkillDetailWnd;

	class USkillDetailWnd* SkillDetailWnd;

private:
	UPROPERTY(meta = (BindWidget))
	class UTextBlock* Text_Value;

	UPROPERTY(meta = (BindWidget))
	class UTextBlock* Text_InputKeyName;

	UPROPERTY(meta = (BindWidget))
	class UProgressBar* ProgressBar_CoolDownTime;

	UPROPERTY(meta = (BindWidget))
	class UImage* Image_Star;

	UPROPERTY(meta = (BindWidgetAnim), meta = (AllowPrivateAccess = true))
	class UWidgetAnimation* QuickSlotActivation;

	UPROPERTY()
	FName QuickSlotKey;

	UPROPERTY()
	FText QuickSlotKeyName;

	struct FQuickSlotSkillInfo QuickSlotSkillInfo;

	float StartTime;

	float CoolDownTime;

protected :
	virtual void NativeConstruct() override;

	virtual void NativeTick(const FGeometry& MyGeometry, float inDeltaTime) override;

private :
	void InitiailzeBind();

	void UpdateCoolDownTime();

	// 슬롯을 비웁니다.
	void SetQuickSlotEmpty();

public:
	// 슬롯을 초기화합니다.
	virtual void InitializeSlot(ESlotType slotType, FName inCode, ESkillType skillType) override;

	void UpdateQuickSlot();

	void UpdateQuickSlotInfoSkill();

	void SwapQuickSlot(UQuickSlot* firstQuickSlot, UQuickSlot* SecondQuickSlot);

	struct FQuickSlotSkillInfo GetCodeToQuickSlotSkillInfo(FName code) const;

	void SetQuickSlotInfo(FQuickSlotInfo quickSlotInfo);

	void InitializeQuickSlotSkillInfo(FQuickSlotSkillInfo quickSlotSkillInfo);

	void SetQuickSlotSkillInfo(FQuickSlotSkillInfo quickSlotSkillInfo);

	void SetQuickLockandUnlock(bool isLock);

	FORCEINLINE FQuickSlotSkillInfo GetQuickSlotSkillInfo() const
	{ return QuickSlotSkillInfo; }
};
