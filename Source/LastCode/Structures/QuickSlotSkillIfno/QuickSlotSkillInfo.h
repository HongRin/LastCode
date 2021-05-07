#pragma once

#include "CoreMinimal.h"
#include "Enums/SkillType.h"
#include "QuickSlotSkillInfo.generated.h"

USTRUCT()
struct LASTCODE_API FQuickSlotSkillInfo

{
	GENERATED_USTRUCT_BODY()

public:
	UPROPERTY()
	FName QuickSlotKey;

	UPROPERTY()
	ESkillType SkillType;

	UPROPERTY()
	FName SkillCode;

	UPROPERTY()
	bool bQuickSlotCoolDownTime;

	FQuickSlotSkillInfo();
	FQuickSlotSkillInfo(FName quickSlotKey);
	FQuickSlotSkillInfo(FName quickSlotKey, ESkillType SkillType, FName SkillCode);

	FORCEINLINE bool IsEmpty() const
	{
		return SkillCode.IsNone();
	}

	FORCEINLINE bool IsCoolDownTime() const
	{
		return bQuickSlotCoolDownTime == true;
	}

	// 해당 데이터를 비웁니다.
	FORCEINLINE void Clear()
	{
		SkillCode = TEXT("");
	}
};
