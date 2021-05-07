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
	// ĳ���� �ڵ�
	UPROPERTY()
	FName CharacterCode;

	UPROPERTY()
	int32 Level;

	// �ִ� ü��
	UPROPERTY()
	float MaxHp;

	// ���� ü��
	UPROPERTY()
	float Hp;

	// ���ݷ�
	UPROPERTY()
	float Atk;
	
	// �ִ� ���¹̳�
	UPROPERTY()
	float MaxStamina;

	// ���¹̳�
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

	// �κ��丮 ���� ����
	UPROPERTY()
	int32 InventorySlotCount;

	// �������� ������ ����
	UPROPERTY()
	TArray<FItemSlotInfo> InventoryItemInfos;

	// ������
	UPROPERTY()
	int32 Silver;

	UPROPERTY()
	EClearType ClearType;

	FPlayerInfo();

};
