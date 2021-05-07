
#pragma once

#include "CoreMinimal.h"
#include "QuickSlotInfo.generated.h"

USTRUCT()
struct LASTCODE_API FQuickSlotInfo
{

	GENERATED_USTRUCT_BODY()

public :
	UPROPERTY()
	FName QuickSlotKey;

	UPROPERTY()
	FText QuickSlotKeyName;

	FQuickSlotInfo();
	FQuickSlotInfo(FName quickSlotKey, FText quickSlotKeyName);

};
