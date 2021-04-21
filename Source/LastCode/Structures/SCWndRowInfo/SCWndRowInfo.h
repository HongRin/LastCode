#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "SCWndRowInfo.generated.h"

USTRUCT()
struct LASTCODE_API FSCWndRowInfo : public FTableRowBase
{
	GENERATED_USTRUCT_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FText CharacterClassName;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FText WeaponName;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FText CharacterClassExplain;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float value1;
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float value2;
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float value3;
};
