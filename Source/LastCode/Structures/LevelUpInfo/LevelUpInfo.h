#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "LevelUpInfo.generated.h"

USTRUCT()
struct LASTCODE_API FLevelUpInfo : public FTableRowBase
{

	GENERATED_USTRUCT_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FName MaxExp;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float HpIncrease;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float StaminaIncrease;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float AtkIncrease;
};
