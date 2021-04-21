#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "PreviewCharacterAnimInstance.generated.h"

UCLASS()
class LASTCODE_API UPreviewCharacterAnimInstance : public UAnimInstance
{
	GENERATED_BODY()
	
protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Owner Properties")
		class APreviewCharacter* Owner;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Owner Properties")
		float VelocityLength;

public:
	virtual void NativeUpdateAnimation(float DeltaSeconds) override;
};
