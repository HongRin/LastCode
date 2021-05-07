#include "DungeonLevel.h"

#include "Engine/World.h"
#include "Engine/EngineTypes.h"
#include "UserWidget.h"

#include "Actors/Characters/PlayerCharacter/PlayableCharacter.h"
#include "Actors/Controllers/PlayerController/PlayableController/PlayableController.h"
#include "Actors/Characters/EnemyCharacter/EnemyCharacter.h"

#include "Single/GameInstance/LCGameInstance.h"
#include "Single/PlayerManager/PlayerManager.h"

#include "Widgets/ResultWnd/DungeonResultWnd.h"
#include "Widgets/WidgetControllerWidget/WidgetControllerWidget.h"

#include "Components/CanvasPanel.h"
#include "Components/CanvasPanelSlot.h"


ADungeonLevel::ADungeonLevel()
{
	PrimaryActorTick.bCanEverTick = true;

	static ConstructorHelpers::FClassFinder<UDungeonResultWnd> BP_RESULT_WND(
		TEXT("WidgetBlueprint'/Game/Resources/Blueprints/Widgets/LoadingWnd/BP_DungeonResultWnd.BP_DungeonResultWnd_C'"));
	if (BP_RESULT_WND.Succeeded()) BP_DungeonResultWnd = BP_RESULT_WND.Class;

	ClearType = EClearType::CT_None;
	RewardExp = 0;
	RewardSilver = 0;
	Kill = 0;
}

void ADungeonLevel::BeginPlay()
{
	Super::BeginPlay();

	FirstMonsterCount = EnemyCharacters.Num();

	UE_LOG(LogTemp, Warning, TEXT("%d"), FirstMonsterCount);

	GetManager(UPlayerManager)->GetPlayableCharacter()->IsLobby(false);
}

void ADungeonLevel::DungeonClear()
{
	if (EnemyCharacters.Num() == 0)
		ClearType = EClearType::CT_Clear;
	else if (GetManager(UPlayerManager)->GetPlayableCharacter()->IsDie())
		ClearType = EClearType::CT_Fail;

	if (ClearType != EClearType::CT_None)
	{
		if (!IsValid(ResultWnd))
		{
			UWidgetControllerWidget* widgetController =
				GetManager(UPlayerManager)->GetPlayableController()->GetWidgetControllerWidget();
			ResultWnd = CreateWidget<UDungeonResultWnd>(widgetController, BP_DungeonResultWnd);
			widgetController->AddChildWidget(ResultWnd, EInputModeType::IM_UIOnly, true, 1920.0f, 1080.0f);
			Cast<UCanvasPanelSlot>(ResultWnd->Slot)->SetAnchors(FAnchors(0.0f, 0.0f, 0.0f, 0.0f));
			Cast<UCanvasPanelSlot>(ResultWnd->Slot)->SetAlignment(FVector2D(0.0f, 0.0f));
			ResultWnd->InitializeReward(Kill, FirstMonsterCount, RewardExp, RewardSilver, DropItems);
			ResultWnd->DungeonResultAnimation(ClearType);
		}
	}
}

void ADungeonLevel::RemoveEnemyCharacters(class AEnemyCharacter* enemyCharacter)
{
	EnemyCharacters.Remove(enemyCharacter);
	++Kill;
}

void ADungeonLevel::SetDropItems(FName itemCode, int32 maxSlotCount)
{
	if (DropItems.Num() == 0)
	{
		DropItems.Add(FItemSlotInfo(itemCode, 1, maxSlotCount));
		return;
	}

	for (int i = 0; i < DropItems.Num(); ++i)
	{
		if (DropItems[i].ItemCode == itemCode)
		{
			++DropItems[i].ItemCount;
			return;
		}
	}

	DropItems.Add(FItemSlotInfo(itemCode, 1, maxSlotCount));
}
