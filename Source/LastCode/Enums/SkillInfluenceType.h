#pragma once

#include "CoreMinimal.h"
#include "SkillInfluenceType.generated.h"

UENUM(BlueprintType)
enum class ESkillInfluenceType : uint8
{
	SLF_NONE		UMETA(DisplayName = None),
	SLF_DAMAGE		UMETA(DisplayName = Damage),
	SLF_HP			UMETA(DisplayName = Hp),
	SLF_STAMINA		UMETA(DisplayName = Stamina),
	SLF_ATK			UMETA(DisplayName = Atk)
};
