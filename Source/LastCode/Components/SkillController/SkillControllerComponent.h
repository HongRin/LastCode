#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Enums/SkillType.h"
#include "SkillControllerComponent.generated.h"

#ifndef SKILL_PARTICLE_ID
#define SKILL_PARTICLE_ID

#define DEFAULT_SKILL			1

#endif

DECLARE_MULTICAST_DELEGATE(OnAttackEventSignature);
DECLARE_MULTICAST_DELEGATE(OnDashEventSignature);
DECLARE_MULTICAST_DELEGATE(OnSkillEventSignature);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class LASTCODE_API USkillControllerComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	OnAttackEventSignature OnRRegularAttackFinished;
	OnAttackEventSignature OnLRegularAttackFinished;

	OnDashEventSignature OnDashFinished;

	OnSkillEventSignature  OnActiveSkillFinished;

private:

private:
	UPROPERTY()
	class APlayableCharacter* PlayableCharacter;

	class UDataTable* DT_SkillInfo;

	UPROPERTY()
	TSubclassOf<class UCameraShake> ShakeCamera;

	UPROPERTY()
	TSubclassOf<class APoolableSkillParticleActor> SkillParticle;

	UPROPERTY()
	class UObjectPool* ParticleObjectPool;

	TArray<struct FSkillInfo> SkillInfo;
	FSkillInfo* BehaviorSkillInfo;

#pragma region boolComboAttaking...
	bool bIsLRegularAttack;
	bool bIsLFirstComboAttack;
	bool bIsLSecondComboAttack;
	bool bIsLThirdComboAttack;

	bool bIsRRegularAttack;
	bool bIsRFirstComboAttack;
	bool bIsRSecondComboAttack;
	bool bIsRThirdComboAttack;

	bool bIsDash;

	bool bIsSkillable;
#pragma endregion

public:
	USkillControllerComponent();

protected:
	virtual void BeginPlay() override;

public:
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

private:
	// 에셋을 로드합니다.
	void LoadAsset();

private :
	void PlayActiveSkill(FName skillCode);
	void PlayUseItem(FName skillCode);

public:
	void LRegularAttack();
	void RRegularAttack();

	void Dash();

	void PlayQuickSlotkill(FName skillCode, ESkillType skillType);

	void UpdateSkillInfo(FName skillCode);
	void EmptySkillInfo();

	void CameraShaking(float scale = 1.0f);

	void UpdateAttackRange();

	class APoolableSkillParticleActor* PlaySkillParitcle(FVector loc, FRotator rot = FRotator::ZeroRotator);

public:
#pragma region GetComboAttaking...
	FORCEINLINE bool LRegularAttacking() const
	{
		return bIsLRegularAttack;
	}
	FORCEINLINE bool LFirstComboAttackable() const
	{
		return bIsLFirstComboAttack;
	}
	FORCEINLINE bool LSecondComboAttackable() const
	{
		return bIsLSecondComboAttack;
	}
	FORCEINLINE bool LThirdComboAttackable() const
	{
		return bIsLThirdComboAttack;
	}

	FORCEINLINE bool RRegularAttacking() const
	{
		return bIsRRegularAttack;
	}
	FORCEINLINE bool RFirstComboAttackable() const
	{
		return bIsRFirstComboAttack;
	}
	FORCEINLINE bool RSecondComboAttackable() const
	{
		return bIsRSecondComboAttack;
	}
	FORCEINLINE bool RThirdComboAttackable() const
	{
		return bIsRThirdComboAttack;
	}
#pragma endregion

	FORCEINLINE  bool IsAttacking() const
	{
		return bIsLRegularAttack || bIsRRegularAttack;
	}

	FORCEINLINE bool IsSkillable() const
	{
		return bIsSkillable;
	}
};
