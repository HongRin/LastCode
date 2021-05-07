#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "PlayableCharacterAnimInstance.generated.h"

UCLASS()
class LASTCODE_API UPlayableCharacterAnimInstance : public UAnimInstance
{
	GENERATED_BODY()
	
protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Owner Properties")
		class APlayableCharacter* Owner;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Owner Properties")
		float VelocityLength;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Owner Properties")
		bool bIsInAir;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Owner Properties")
		bool bIsDie;

public:
	virtual void NativeUpdateAnimation(float DeltaSeconds) override;

protected :
	UFUNCTION()
	void AnimNotify_HitFin();
};
