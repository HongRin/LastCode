#include "QuickSlotInfo.h"

FQuickSlotInfo::FQuickSlotInfo()
{
	QuickSlotKey = FName(TEXT(""));
	bQuickSlotCoolDownTime = false;
}

FQuickSlotInfo::FQuickSlotInfo(FName quickSlotKey, FText quickSlotName)
{
	QuickSlotKey = quickSlotKey;
	QuickSlotName = quickSlotName;
	SkillType = ESkillType::SKT_None;
	bQuickSlotCoolDownTime = false;
	Clear();
}

FQuickSlotInfo::FQuickSlotInfo(FName quickSlotKey, FText quickSlotName, ESkillType skillType, FName skillCode)
{
	QuickSlotKey = quickSlotKey;

	QuickSlotName = quickSlotName;

	SkillType = skillType;

	SkillCode = skillCode;
	
	bQuickSlotCoolDownTime = false;
}
