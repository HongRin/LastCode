
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Interfaces/ObjectPoolable.h"
#include "PoolableSkillParticleActor.generated.h"

UCLASS()
class LASTCODE_API APoolableSkillParticleActor : public AActor,
	public IObjectPoolable
{
	GENERATED_BODY()
	
private:
	class UParticleSystem* SkillParticle;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	class UParticleSystemComponent* SkillParticleSystem;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	int32 Id;

	UPROPERTY()
	bool bCanRecyclable;

public:
	APoolableSkillParticleActor();

protected:
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;

public:
	FORCEINLINE virtual int32 GetID() const override
	{
		return Id;
	}

	FORCEINLINE virtual void SetID(int32 id)
	{
		Id = id;
	}

	// 재사용 가능 여부를 나타내는 변수에 대한 접근자 / 설정자
	FORCEINLINE virtual bool GetCanRecyclable() const override
	{
		return bCanRecyclable;
	}

	FORCEINLINE virtual void SetCanRecyclable(bool canRecyclable) override
	{
		bCanRecyclable = canRecyclable;
	}

	// 재활용이 되는 시점에서 호출되는 메서드
	virtual void OnRecycleStart() override;

private:
	UFUNCTION()
		void OnParticleSystemFinished(class UParticleSystemComponent* PSystem);

public:
	void PlayParticle(class UParticleSystem* skillParticle, FVector loc, FRotator rot = FRotator::ZeroRotator);
};
