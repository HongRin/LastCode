#include "QuickSlotSkillInfo.h"

FQuickSlotSkillInfo::FQuickSlotSkillInfo()
{
	QuickSlotKey = TEXT("");
	SkillType = ESkillType::SKT_None;
	SkillCode = TEXT("");
	bQuickSlotCoolDownTime = false;
}

FQuickSlotSkillInfo::FQuickSlotSkillInfo(FName quickSlotKey)
{
	QuickSlotKey = quickSlotKey;
	SkillType = ESkillType::SKT_None;
	SkillCode = TEXT("");
	bQuickSlotCoolDownTime = false;
}

FQuickSlotSkillInfo::FQuickSlotSkillInfo(FName quickSlotKey, ESkillType skillType, FName skillCode)
{
	QuickSlotKey = quickSlotKey;

	SkillType = skillType;

	SkillCode = skillCode;

	bQuickSlotCoolDownTime = false;
}
