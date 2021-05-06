#pragma once

#include "LastCode.h"
#include "GameFramework/Character.h"
#include "BaseCharacter.generated.h"

DECLARE_MULTICAST_DELEGATE(FOnCharacterDieEventSignature)

UCLASS()
class LASTCODE_API ABaseCharacter : public ACharacter
{
	GENERATED_BODY()

public :
	FOnCharacterDieEventSignature OnCharacterDieEvent;

protected:
	UPROPERTY()
		bool bIsDie;

protected:
	virtual void BeginPlay() override;

public:
	virtual float GetMaxHp() PURE_VIRTUAL(ABaseCharacter::GetMaxHp, return 0.0f; );

	virtual float GetHp() PURE_VIRTUAL(ABaseCharacter::GetHp, return 0.0f; );

	virtual void SetHp(float value) PURE_VIRTUAL(ABaseCharacter::SetHp, );

protected:
	UFUNCTION()
		virtual void OnTakeDamage(
			AActor* DamagedActor,
			float Damage,
			const class UDamageType* DamageType,
			class AController* InstigatedBy,
			AActor* DamageCauser);

	virtual void OnCharacterDie();


public:
	FORCEINLINE bool IsDie() const
	{
		return bIsDie;
	}
};
