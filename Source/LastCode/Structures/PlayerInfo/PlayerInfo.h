#pragma once

#include "Enums/StaminaType.h"
#include "Enums/ClearType.h"
#include "Structures/SkillInfo/SkillInfo.h"
#include "Structures/SkillReinforceInfo/SkillReinforceInfo.h"
#include "Structures/QuickSlotInfo/QuickSlotInfo.h"
#include "Structures/QuickSlotSkillIfno/QuickSlotSkillInfo.h"
#include "Structures/ItemSlotInfo/ItemSlotInfo.h"
#include "PlayerInfo.generated.h"

USTRUCT()
struct LASTCODE_API FPlayerInfo
{

	GENERATED_USTRUCT_BODY()

public:
	// 캐릭터 코드
	UPROPERTY()
	FName CharacterCode;

	UPROPERTY()
	int32 Level;

	// 최대 체력
	UPROPERTY()
	float MaxHp;

	// 현재 체력
	UPROPERTY()
	float Hp;

	// 공격력
	UPROPERTY()
	float Atk;
	
	// 최대 스태미나
	UPROPERTY()
	float MaxStamina;

	// 스태미나
	UPROPERTY()
	float Stamina;

	UPROPERTY()
	int32 Exp;

	UPROPERTY()
	int32 MaxExp;

	UPROPERTY()
	int32 SkillPoint;

	UPROPERTY()
	EStaminaType StaminaType;

	UPROPERTY()
	TArray<FSkillInfo> SkillInfo;

	UPROPERTY()
	TArray<FQuickSlotInfo> QuickSlotInfos;

	UPROPERTY()
	TArray<FQuickSlotSkillInfo> QuickSlotSkillInfos;

	// 인벤토리 슬롯 개수
	UPROPERTY()
	int32 InventorySlotCount;

	// 소지중인 아이템 정보
	UPROPERTY()
	TArray<FItemSlotInfo> InventoryItemInfos;

	// 소지금
	UPROPERTY()
	int32 Silver;

	UPROPERTY()
	EClearType ClearType;

	FPlayerInfo();

};
