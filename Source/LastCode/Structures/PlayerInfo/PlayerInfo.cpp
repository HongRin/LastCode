#include "PlayerInfo.h"

FPlayerInfo::FPlayerInfo()
{
	CharacterCode = FName(TEXT(""));
	Level = 10;
	Hp = 200.0f;
	MaxHp = 400.0f;
	Atk = 100.0f;
	MaxStamina = 100.0f;
	Stamina = 30.0f;
	SkillPoint = 8;

	QuickSlotInfos.Add(FQuickSlotInfo(TEXT("One"), FText::FromString(TEXT("1"))));
	QuickSlotInfos.Add(FQuickSlotInfo(TEXT("Two"), FText::FromString(TEXT("2"))));
	QuickSlotInfos.Add(FQuickSlotInfo(TEXT("Three"), FText::FromString(TEXT("3"))));
	QuickSlotInfos.Add(FQuickSlotInfo(TEXT("Four"), FText::FromString(TEXT("4"))));
	QuickSlotInfos.Add(FQuickSlotInfo(TEXT("Five"), FText::FromString(TEXT("5"))));
	QuickSlotInfos.Add(FQuickSlotInfo(TEXT("Six"), FText::FromString(TEXT("6"))));
	QuickSlotInfos.Add(FQuickSlotInfo(TEXT("Seven"), FText::FromString(TEXT("7"))));
	QuickSlotInfos.Add(FQuickSlotInfo(TEXT("Eight"), FText::FromString(TEXT("8"))));

	InventorySlotCount = 50;

	QuickSlotCount = 8;

	for (int32 i = 0; i < InventorySlotCount; ++i)
		InventoryItemInfos.Add(FItemSlotInfo());

	// TEST
	Silver = 30000;

	ClearType = EClearType::CT_None;
}
