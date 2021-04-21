#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "SkillSlotInfo.generated.h"

USTRUCT()
struct LASTCODE_API FSkillSlotInfo : public FTableRowBase 
{
	GENERATED_USTRUCT_BODY()
public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FName SkillCode;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FName CharacterCode;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FName ReinforceSkillCode;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FText SkillName;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FText SkillExplain;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FSoftObjectPath ImageSprite;
};
