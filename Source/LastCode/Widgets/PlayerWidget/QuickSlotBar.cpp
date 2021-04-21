#include "QuickSlotBar.h"

#include "Components/HorizontalBox.h"

#include "Single/GameInstance/LCGameInstance.h"
#include "Single/PlayerManager/PlayerManager.h"
#include "Widgets/QuickSlot/QuickSlot.h"

UQuickSlotBar::UQuickSlotBar(const FObjectInitializer& ObjInitializer) :
	Super(ObjInitializer)
{
	static ConstructorHelpers::FClassFinder<UQuickSlot> BP_QUICK_SLOT(
		TEXT("WidgetBlueprint'/Game/Resources/Blueprints/Widgets/QuikSlot/BP_QuickSlot.BP_QuickSlot_C'"));
	if (BP_QUICK_SLOT.Succeeded()) BP_QuickSlot = BP_QUICK_SLOT.Class;
	else UE_LOG(LogTemp, Error, TEXT("UQuickSlotBar.cpp::%d::LINE::BP_QUICK_SLOT is not loaded !"), __LINE__);
}

void UQuickSlotBar::NativeConstruct()
{
	Super::NativeConstruct();

	InitializeQuickSlots();
}

void UQuickSlotBar::InitializeQuickSlots()
{
	for (int i = 0; i < GetManager(UPlayerManager)->GetPlayerInfo()->QuickSlotInfos.Num(); ++i)
	{
		UQuickSlot* quickSlot = CreateWidget<UQuickSlot>(this, BP_QuickSlot);
		quickSlot->SetQuickSlotInfo(GetManager(UPlayerManager)->GetPlayerInfo()->QuickSlotInfos[i]);
		quickSlot->SetQuickSlotKey(GetManager(UPlayerManager)->GetPlayerInfo()->QuickSlotInfos[i].QuickSlotKey);
		quickSlot->UpdateQuickSlot();
		HorizontalBox_QuickSlotList->AddChild(quickSlot);
	}
}
