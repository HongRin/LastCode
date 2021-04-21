#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "SkillReinforceInfo.generated.h"

USTRUCT()
struct LASTCODE_API FSkillReinforceInfo : public FTableRowBase
{
	GENERATED_USTRUCT_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FName CharacterCode;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FName SkillCode;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FName CurrentSkillCode;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FName NextSkillCode;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	int32 SkillLevel;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	int32 ActivationCharacterLevel;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (UIMin = "0.0", UIMax = "10000000.0", ClampMin = "0.0", ClampMax = "10000000.0"))
	float SkillValue;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (UIMin = "0.0", UIMax = "1000000.0", ClampMin = "0.0", ClampMax = "1000000.0"))
	float SkillStamina;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (UIMin = "0.0", UIMax = "500.0", ClampMin = "0.0", ClampMax = "500.0"))
	float SKillCoolDownTime;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	bool bMaximumLevel;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float value1;
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float value2;
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float value3;
};
