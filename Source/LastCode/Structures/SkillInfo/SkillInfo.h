#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "Enums/SkillType.h"
#include "Enums/SkillInfluenceType.h"
#include "SkillInfo.generated.h"

USTRUCT()
struct LASTCODE_API FSkillInfo : public FTableRowBase
{

	GENERATED_USTRUCT_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FName SkillCode;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FText SkillName;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	ESkillType SkillType;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	ESkillInfluenceType SkillInfluenceType;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FName CharacterCode;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FName ReinforceSkillCode;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	UAnimMontage* SkillAnimPath;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FSoftObjectPath SkillParticlePath;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float SkillStartLenght;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float SkillEndLenght;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float SkillRadius;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FText SkillExplain;

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
	FSoftObjectPath ImageSprite;
};
