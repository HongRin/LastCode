#include "PlayerInfo.h"

FPlayerInfo::FPlayerInfo()
{
	CharacterCode = FName(TEXT(""));
	Level = 10;
	Hp = 200.0f;
	MaxHp = 400.0f;
	Atk = 0.0f;
	MaxStamina = 100.0f;
	Stamina = 30.0f;
	Money = 10000;
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

	for (int32 i = 0; i < InventorySlotCount; ++i)
		InventoryItemInfos.Add(FItemSlotInfo());

	InventoryItemInfos[1] = (FItemSlotInfo(FName(TEXT("60000")), 3));
	InventoryItemInfos[12] = (FItemSlotInfo(FName(TEXT("60001")), 10));
	InventoryItemInfos[2] = (FItemSlotInfo(FName(TEXT("60002")), 1));
	InventoryItemInfos[3] = (FItemSlotInfo(FName(TEXT("60003")), 1));

	// TEST
	Silver = 10000;

}
