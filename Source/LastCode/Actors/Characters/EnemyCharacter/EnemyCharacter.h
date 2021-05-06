#pragma once

#include "Actors/Characters/BaseCharacter.h"
#include "GenericTeamAgentInterface.h"
#include "Structures/EnemyInfo/EnemyInfo.h"
#include "EnemyCharacter.generated.h"

UCLASS()
class LASTCODE_API AEnemyCharacter : public ABaseCharacter,
	public IGenericTeamAgentInterface
{
	GENERATED_BODY()


private:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Basic", meta = (AllowPrivateAccess = "true"))
	class UPlayerDetectorComponent* PlayerDetector;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Basic", meta = (AllowPrivateAccess = "true"))
	class UEnemyAttackComponent* EnemyAttack;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "StaticMesh", meta = (AllowPrivateAccess = "true"))
	class UStaticMeshComponent* WeaponMesh;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Basic", meta = (AllowPrivateAccess = "true"))
	FName EnemyCode;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Anim", meta = (AllowPrivateAccess = "true"))
	UAnimMontage* HitAnim;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Basic", meta = (AllowPrivateAccess = "true"))
	float MaxHp;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Basic", meta = (AllowPrivateAccess = "true"))
	float Hp;

	UPROPERTY()
	class ULCGameInstance* GameInst;

	UPROPERTY()
	class UDataTable* DT_EnemyInfo;

	class ADungeonLevel* DungeonLevel;

	FEnemyInfo EnemyInfo;

	FGenericTeamId TeamId;

	float EnemyAtk;

	bool bHitting;

public:
	AEnemyCharacter();


#pragma region Overrides...
protected:
	virtual void BeginPlay() override;


	virtual void OnTakeDamage(
		AActor* DamagedActor,
		float Damage,
		const class UDamageType* DamageType,
		class AController* InstigatedBy,
		AActor* DamageCauser) override;

	virtual void OnCharacterDie() override;
#pragma endregion
private:
	// Components Initialization
	void InitializeComponent();

	// SkeletalMeshInfomation Initialization
	void InitializeSkeletalMeshComponent();

public:
	// MonsterData Initialization
	UFUNCTION(BlueprintCallable)
	void InitializeMonsterDataConstructTime();

	FORCEINLINE virtual float GetMaxHp() override
	{
		return MaxHp;
	}
	FORCEINLINE virtual float GetHp() override
	{
		return Hp;
	}
	FORCEINLINE virtual void SetHp(float value) override
	{
		Hp = value;
	}

	void EnemyRebound(FVector direction, float power);

	void EnemyDie();

public:
	FORCEINLINE virtual void SetGenericTeamId(const FGenericTeamId& TeamID) override
	{
		this->TeamId = TeamID;
	}
	FORCEINLINE virtual FGenericTeamId GetGenericTeamId() const override
	{
		return TeamId;
	}

	FORCEINLINE UPlayerDetectorComponent* GetPlayerDetector() const
	{
		return PlayerDetector;
	}

	FORCEINLINE UEnemyAttackComponent* GetEnemyAttack() const
	{
		return EnemyAttack;
	}

	FORCEINLINE bool IsMovable() const;

	FORCEINLINE void SetHitting(bool isHit)
	{ bHitting = isHit; }

	FORCEINLINE bool IsHitting()
	{ return  bHitting; }

	FORCEINLINE FEnemyInfo* GetEnemyInfo()
	{
		return &EnemyInfo;
	}

	FORCEINLINE float GetEnemyAtk() const
	{
		return EnemyAtk;
	}
	
};
