#include "QuickManager.h"
#include "Actors/Characters/PlayerCharacter/PlayableCharacter.h"


#include "Widgets/PlayerWidget/QuickSlotBar.h"
#include "Widgets/WidgetControllerWidget/WidgetControllerWidget.h"

#include "Components/SkillController/SkillControllerComponent.h"
#include "Components/CanvasPanel.h"
#include "Components/CanvasPanelSlot.h"

#include "Single/GameInstance/LCGameInstance.h"
#include "Single/PlayerManager/PlayerManager.h"

UQuickManager::UQuickManager()
{
	static ConstructorHelpers::FClassFinder<UQuickSlotBar> BP_QUICK_SLOT_BAR(
		TEXT("WidgetBlueprint'/Game/Resources/Blueprints/Widgets/PlayerWidget/BP_QuickSlotBar.BP_QuickSlotBar_C'"));
	if (BP_QUICK_SLOT_BAR.Succeeded()) BP_QuickSlotBar = BP_QUICK_SLOT_BAR.Class;
	else UE_LOG(LogTemp, Error, TEXT("UQuickManager.cpp::%d::LINE:: BP_QUICK_SLOT_BAR is not loaed! "), __LINE__);
}

void UQuickManager::CreateQuickSlotBar(UWidgetControllerWidget* widgetController, EInputModeType changeInputMode, bool bShowCursor)
{
	QuickSlotBar = CreateWidget<UQuickSlotBar>(widgetController, BP_QuickSlotBar);

	widgetController->AddChildWidget(QuickSlotBar, EInputModeType::IM_GameOnly, false, 512.0f, 64.0f);
	Cast<UCanvasPanelSlot>(QuickSlotBar->Slot)->SetAnchors(FAnchors(0.5f, 0.5f, 0.5f, 0.5f));
	Cast<UCanvasPanelSlot>(QuickSlotBar->Slot)->SetAlignment(FVector2D(0.5f, -5.595f));
}

void UQuickManager::ReleaseQuickSlotBar()
{
	if (IsValid(QuickSlotBar))
	{
		QuickSlotBar->RemoveFromParent();
	}
}

void UQuickManager::QuickSlotEventExecution(FKey key)
{
	if (!key.IsGamepadKey())
	{
		for (int i = 0; i < GetManager(UPlayerManager)->GetPlayerInfo()->QuickSlotCount; ++i)
		{
			if (GetManager(UPlayerManager)->GetPlayerInfo()->QuickSlotInfos[i].QuickSlotKey == key.GetFName())
			{
				if (GetManager(UPlayerManager)->GetPlayerInfo()->QuickSlotInfos[i].IsEmpty() ||
					GetManager(UPlayerManager)->GetPlayerInfo()->QuickSlotInfos[i].IsCoolDownTime()) return;
				APlayableCharacter* playableCharacter = GetManager(UPlayerManager)->GetPlayableCharacter();
				playableCharacter->GetSkillControllerComponent()->PlayQuickSlotkill(
					GetManager(UPlayerManager)->GetPlayerInfo()->QuickSlotInfos[i].SkillCode,
					GetManager(UPlayerManager)->GetPlayerInfo()->QuickSlotInfos[i].SkillType);
			}
		}
	}
}
