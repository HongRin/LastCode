#pragma once

#include "CoreMinimal.h"
#include "SlotType.generated.h"

UENUM(BlueprintType)
enum class ESlotType : uint8 
{
	SLT_ITME		UMETA(DisplayName = ItemSlot),
	SLT_SKILL		UMETA(DisplayName = SkillSlot),
	SLT_QUICK		UMETA(DisplayName = QuickSlot),
	SLT_INVENTORY	UMETA(DisplayName = InventorySlot)
};
