#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "EnemyInfo.generated.h"

USTRUCT(BlueprintType)
struct LASTCODE_API FEnemyInfo : public FTableRowBase
{
	GENERATED_USTRUCT_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FName EnemyCode;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FSoftObjectPath SkeletalMeshPath;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FSoftObjectPath AnimInstanceClassPath;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FSoftObjectPath WeaponStaticMeshPath;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (UIMin = "0.0", UIMax = "1000.0", ClampMin = "0.0", ClampMax = "1000.0"))
	float MaxSpeed;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (UIMin = "0.0", UIMax = "100000.0", ClampMin = "0.0", ClampMax = "100000.0"))
	float MaxHp;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (UIMin = "0.0", UIMax = "100000.0", ClampMin = "0.0", ClampMax = "100000.0"))
	float Atk;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (UIMin = "0.0", UIMax = "5000.0", ClampMin = "0.0", ClampMax = "5000.0"))
	float AtkRange;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (UIMin = "0.0", UIMax = "100000.0", ClampMin = "0.0", ClampMax = "100000.0"))
	int32 MinDropSilver;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (UIMin = "0.0", UIMax = "100000.0", ClampMin = "0.0", ClampMax = "100000.0"))
	int32 MaxDropSilver;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TArray<FName> DropItemCode;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (UIMin = "0.0", UIMax = "100000.0", ClampMin = "0.0", ClampMax = "100000.0"))
	int32 Exp;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	UAnimMontage* HitAnimPath;
};
