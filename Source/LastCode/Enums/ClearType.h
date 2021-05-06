#pragma once

#include "CoreMinimal.h"
#include "ClearType.generated.h"

UENUM(BlueprintType)
enum class EClearType : uint8
{
	CT_None		   UMETA(DisPlayName = None),
	CT_Clear	   UMETA(DisplayName = Clear),
	CT_Fail		   UMETA(DisplayName = Fail)
};