#pragma once

#include "CoreMinimal.h"
#include "Widgets/ClosableWnd/DraggableWnd/DraggableWidget/BaseSlot/BaseSlot.h"
#include "QuickSlot.generated.h"

UCLASS()
class LASTCODE_API UQuickSlot : public UBaseSlot
{
	GENERATED_BODY()


private:
	TSubclassOf<class USkillDetailWnd> BP_SkillDetailWnd;

	class USkillDetailWnd* SkillDetailWnd;



private :
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

	FName QuickSlotkey;

	FText QuickSlotName;

	FQuickSlotInfo QuickSlotInfo;

	float StartTime;

	float CoolDownTime;

protected :
	virtual void NativeConstruct() override;

	virtual void NativeTick(const FGeometry& MyGeometry, float inDeltaTime) override;

private :
	void InitiailzeBind();

	void LogPlayerQuickSlotInfo();

	FString GetESkillTypeToString(ESkillType skillTypeValue);

	void UpdateCoolDownTime();

	// 슬롯을 비웁니다.
	void SetQuickSlotEmpty();

public:
	// 슬롯을 초기화합니다.
	virtual void InitializeSlot(ESlotType slotType, FName inCode, ESkillType skillType) override;

	void UpdateQuickSlot();

	void UpdateQuickSlotInfoSkill();

	void SwapQuickSlot(UQuickSlot* firstQuickSlot, UQuickSlot* SecondQuickSlot);


	struct FQuickSlotInfo GetQuickSlotInfo(FName quickSlotkey) const;

	struct FQuickSlotInfo GetCodeToQuickSlotInfo(FName code) const;

	void SetQuickSlotInfo(struct FQuickSlotInfo quickSlotInfo);

	void SetQuickLockandUnlock(bool isLock);

	FORCEINLINE void SetQuickSlotKey(FName quickSlotkey)
	{ QuickSlotkey = quickSlotkey; }

	FORCEINLINE FName GetQuickSlotKey() const
	{ return QuickSlotkey; }

	FORCEINLINE FQuickSlotInfo GetQuickSlotInfo() const
	{ return QuickSlotInfo; }
};
