
#pragma once

#include "CoreMinimal.h"
#include "Enums/SkillType.h"
#include "QuickSlotInfo.generated.h"

USTRUCT()
struct LASTCODE_API FQuickSlotInfo
{

	GENERATED_USTRUCT_BODY()

public :
	UPROPERTY()
	FName QuickSlotKey;

	UPROPERTY()
	FText QuickSlotName;

	UPROPERTY()
	ESkillType SkillType;

	UPROPERTY()
	FName SkillCode;

	UPROPERTY()
	bool bQuickSlotCoolDownTime;

	FQuickSlotInfo();
	FQuickSlotInfo(FName quickSlotKey, FText quickSlotName);
	FQuickSlotInfo(FName quickSlotKey, FText quickSlotName, ESkillType SkillType, FName SkillCode);

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
	{ SkillCode = TEXT("");}


};
