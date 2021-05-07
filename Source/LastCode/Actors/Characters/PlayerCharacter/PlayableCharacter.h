#pragma once

#include "Actors/Characters/PlayerCharacter/Preview/PreviewCharacter.h"
#include "GenericTeamAgentInterface.h"
#include "PlayableCharacter.generated.h"

#ifndef GROUND_MOVE_SPEED
#define GROUND_MOVE_SPEED
#define WALK_SPEED			250.0f
#define RUN_SPEED			750.0f
#endif

UCLASS()
class LASTCODE_API APlayableCharacter : public APreviewCharacter,
	public IGenericTeamAgentInterface
{
	GENERATED_BODY()

#pragma region Components
private:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Basic", meta = (AllowPrivateAccess = "true"))
		class USkillControllerComponent* SkillController;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Basic", meta = (AllowPrivateAccess = "true"))
		class ULevelUpComponent* LevelUpSystem;
#pragma endregion

#pragma region ect Value
private:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Basic", meta = (AllowPrivateAccess = "true"))
		float MaxHp;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Basic", meta = (AllowPrivateAccess = "true"))
		float Hp;

	class APlayableController* PlayableController;

	UPROPERTY()
	class UPlayerManager* PlayerManager;

	UPROPERTY()
	class UQuickManager* QuickManager;
#pragma endregion

#pragma region StateValue
	bool bIsMoveable;

	bool bIsLobby;
	
	FGenericTeamId TeamId;
#pragma endregion

public:
	APlayableCharacter();

#pragma region Overrides
protected:
	virtual void BeginPlay() override;

	virtual void OnTakeDamage(
		AActor* DamagedActor,
		float Damage,
		const class UDamageType* DamageType,
		class AController* InstigatedBy,
		AActor* DamageCauser) override;

public:
	virtual void Tick(float DeltaTime) override;

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	virtual float GetMaxHp() override;
	virtual float GetHp() override;
	virtual void SetHp(float value) override;

	virtual void OnCharacterDie() override;

	float GetMaxStamina();
	float GetStamina();
	void SetStamina(float value);

#pragma endregion

private:
	void LoadAsset();

protected:
	virtual void InitializeComponent() override;

#pragma region Axis
protected:
	UFUNCTION(BlueprintCallable, Category = "CharacterAction")
		void InputHorizontal(float axis);

	UFUNCTION(BlueprintCallable, Category = "CharacterAction")
		void InputVertical(float axis);
#pragma endregion

#pragma region StateFunction
public:
	virtual void Jump() override;
	virtual void Landed(const FHitResult& Hit) override;

private:
	void Run();
	void Walk();
	void QuickSlotPressed(struct FKey key);
#pragma endregion

public :
	void SetImpluse(FVector direction, float power);
	void LookatControlDirection();

public:
	class UPlayerManager* GetPlayerManager();

	bool IsMoveable();

	FORCEINLINE virtual void SetGenericTeamId(const FGenericTeamId& TeamID) override
	{ this->TeamId = TeamID; }
	FORCEINLINE virtual FGenericTeamId GetGenericTeamId() const override
	{ return TeamId; }

	FORCEINLINE void ProhibitMove()
	{ bIsMoveable = false; }

	FORCEINLINE void AllowMove()
	{ bIsMoveable = true; }

	FORCEINLINE bool IsInAir() const
	{ return GetCharacterMovement()->IsFalling(); }

	FORCEINLINE USkillControllerComponent* GetSkillControllerComponent() const
	{ return SkillController; }

	FORCEINLINE void IsLobby(bool isLobby)
	{ bIsLobby = isLobby; }
};
