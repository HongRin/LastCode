#pragma once

#include "CoreMinimal.h"
#include "SkillType.generated.h"

UENUM(BlueprintType)
enum class ESkillType : uint8
{
	SKT_ITEM		UMETA(DisplayName = Item),	
	SKT_ACTIVE		UMETA(DisplayName = ActiveSkill),			
	SKT_PASSIVE		UMETA(DisplayName = PassiveSkill),
	SKT_None		UMETA(DisplayName = None)
};
