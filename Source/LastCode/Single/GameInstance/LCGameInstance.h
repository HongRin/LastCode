#pragma once

#include "LastCode.h"

#include "Engine/GameInstance.h"
#include "Engine/AssetManager.h"
#include "Engine/StreamableManager.h"

#include "Single/ManagerClass/ManagerClass.h"

#include "LCGameInstance.generated.h"

#ifndef GAME_INST
#define GAME_INST
#define GetGameInst(worldContextObj) (Cast<ULCGameInstance>(worldContextObj->GetGameInstance()))
#endif

UCLASS()
class LASTCODE_API ULCGameInstance : public UGameInstance
{
	GENERATED_BODY()

private:
	// ����� �Ŵ��� Ŭ���� �ν��Ͻ��� �����մϴ�.
	TMap<FString, UManagerClass*> ManagerClasses;

	// �������� �ε��� ���� �̸��� �����մϴ�.
	FName NextLevelName;

private:
	// ManagerClass �� ��Ͻ�ŵ�ϴ�.
	void RegisterManagerClass(TSubclassOf<UManagerClass> managerClass);

public :
	virtual void Init() override;
	virtual void Shutdown() override;

	// ����� ManagerClass �� ����ϴ�.
	template<typename ManagerClassType>
	FORCEINLINE ManagerClassType* GetManagerClass()
	{
		return Cast<ManagerClassType>(ManagerClasses[ManagerClassType::StaticClass()->GetName()]);
	}

public:
	// �ּ� �ε��� ���� StreamableManager �� ��� �޼���
	template<>
	FORCEINLINE FStreamableManager* GetManagerClass<FStreamableManager>()
	{ return &UAssetManager::GetStreamableManager(); }

	FORCEINLINE void SetNextLevelName(FName nextLevelName)
	{
		NextLevelName = nextLevelName;
	}

	UFUNCTION(BlueprintCallable)
		FORCEINLINE FName GetNextLevelName() const
	{
		return NextLevelName;
	}

};
