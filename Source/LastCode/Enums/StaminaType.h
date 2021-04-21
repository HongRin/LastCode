#pragma once

#include "CoreMinimal.h"
#include "StaminaType.generated.h"

UENUM(BlueprintType)
enum class EStaminaType : uint8
{
	ST_BULLET		UMETA(DisplayName = Bullet),
	ST_ENERGY      UMETA(DisplayName = Energy)
};
