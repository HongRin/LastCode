#include "PlayerInfo.h"

FPlayerInfo::FPlayerInfo()
{
	CharacterCode = FName(TEXT(""));
	Level = 10;
	Hp = 400.0f;
	MaxHp = 400.0f;
	Atk = 100.0f;
	MaxStamina = 150.0f;
	Stamina = 150.0f;
	SkillPoint = 8;

	InventorySlotCount = 50;

	QuickSlotInfos.Add(FQuickSlotInfo(FName(TEXT("One")), FText::FromString(TEXT("1"))));
	QuickSlotInfos.Add(FQuickSlotInfo(FName(TEXT("Two")), FText::FromString(TEXT("2"))));
	QuickSlotInfos.Add(FQuickSlotInfo(FName(TEXT("Three")), FText::FromString(TEXT("3"))));
	QuickSlotInfos.Add(FQuickSlotInfo(FName(TEXT("Four")), FText::FromString(TEXT("4"))));
	QuickSlotInfos.Add(FQuickSlotInfo(FName(TEXT("Five")), FText::FromString(TEXT("5"))));
	QuickSlotInfos.Add(FQuickSlotInfo(FName(TEXT("Six")), FText::FromString(TEXT("6"))));
	QuickSlotInfos.Add(FQuickSlotInfo(FName(TEXT("Seven")), FText::FromString(TEXT("7"))));
	QuickSlotInfos.Add(FQuickSlotInfo(FName(TEXT("Eight")), FText::FromString(TEXT("8"))));

	for (int i = 0; i < QuickSlotInfos.Num(); ++i)
		QuickSlotSkillInfos.Add(FQuickSlotSkillInfo(QuickSlotInfos[i].QuickSlotKey));

	for (int32 i = 0; i < InventorySlotCount; ++i)
		InventoryItemInfos.Add(FItemSlotInfo());

	// TEST
	Silver = 30000;

	ClearType = EClearType::CT_None;
}
