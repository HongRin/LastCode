#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "FieldInfo.generated.h"

USTRUCT()
struct LASTCODE_API FFieldInfo : public FTableRowBase 
{

	GENERATED_USTRUCT_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Basic")
	FName FieldName;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Basic")
	FSoftObjectPath FieldImagePath;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Basic")
	int32 FieldUnLockLevel;
};
