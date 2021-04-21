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
	// 등록한 매니저 클래스 인스턴스를 저장합니다.
	TMap<FString, UManagerClass*> ManagerClasses;

	// 다음으로 로드할 레벨 이름을 저장합니다.
	FName NextLevelName;

private:
	// ManagerClass 를 등록시킵니다.
	void RegisterManagerClass(TSubclassOf<UManagerClass> managerClass);

public :
	virtual void Init() override;
	virtual void Shutdown() override;

	// 등록한 ManagerClass 를 얻습니다.
	template<typename ManagerClassType>
	FORCEINLINE ManagerClassType* GetManagerClass()
	{
		return Cast<ManagerClassType>(ManagerClasses[ManagerClassType::StaticClass()->GetName()]);
	}

public:
	// 애셋 로딩을 위한 StreamableManager 를 얻는 메서드
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
