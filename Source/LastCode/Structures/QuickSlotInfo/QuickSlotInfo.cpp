#include "QuickSlotInfo.h"

FQuickSlotInfo::FQuickSlotInfo()
{
}

FQuickSlotInfo::FQuickSlotInfo(FName quickSlotKey, FText quickSlotKeyName)
{
	QuickSlotKey = quickSlotKey;
	QuickSlotKeyName = quickSlotKeyName;
}
