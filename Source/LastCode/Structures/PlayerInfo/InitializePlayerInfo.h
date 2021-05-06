#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "AnimInstance/PlayerCharacter/PlayableCharacterAnimInstance.h"
#include "AnimInstance/PlayerCharacter/Preview/PreviewCharacterAnimInstance.h"
#include "Enums/StaminaType.h"
#include "InitializePlayerInfo.generated.h"

USTRUCT()
struct LASTCODE_API FInitializePlayerInfo : public FTableRowBase
{
	GENERATED_USTRUCT_BODY()

public :
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FName CharacterCode;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	EStaminaType StaminaType;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FSoftObjectPath SkeletalMeshBodyPath;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FSoftObjectPath StaticMeshRWeaponPath;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FSoftObjectPath StaticMeshLWeaponPath;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FSoftObjectPath SkeletalMeshMaskPath;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TSubclassOf<UPreviewCharacterAnimInstance> PreviewAnimInstancePath;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TSubclassOf<UPlayableCharacterAnimInstance> AnimInstancePath;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	UAnimMontage* HitAnimPath;
};
