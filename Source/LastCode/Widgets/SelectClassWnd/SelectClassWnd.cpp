#include "SelectClassWnd.h"
#include "Actors/Characters/PlayerCharacter/Preview/PreviewCharacter.h"

#include "Structures/SCWndRowInfo/SCWndRowInfo.h"

#include "Components/TextBlock.h"
#include "Components/ProgressBar.h"
#include "Components/Button.h"

#include "Single/GameInstance/LCGameInstance.h"
#include "Single/PlayerManager/PlayerManager.h"

USelectClassWnd::USelectClassWnd(const FObjectInitializer& ObjInitializer) :
	Super(ObjInitializer)
{
	static ConstructorHelpers::FObjectFinder<UDataTable> DT_SCWND_INFO(
		TEXT("DataTable'/Game/Resources/DataTable/DT_SCWndRowInfo.DT_SCWndRowInfo'"));
	if (DT_SCWND_INFO.Succeeded()) DT_SCWndRowInfo = DT_SCWND_INFO.Object;
	else UE_LOG(LogTemp, Error, TEXT("USelectClassWnd.cpp::%d::LINE:: DT_SCWND_INFO is not loaded !"), __LINE__);

	static ConstructorHelpers::FObjectFinder<UDataTable> DT_SKILL_INFO(
		TEXT("DataTable'/Game/Resources/DataTable/DT_SkillInfo.DT_SkillInfo'"));
	if (DT_SKILL_INFO.Succeeded()) DT_SkillInfo = DT_SKILL_INFO.Object;
	else UE_LOG(LogTemp, Error, TEXT("USelectClassWnd.cpp::%d::LINE:: DT_SKILL_INFO is not loaded !"), __LINE__);
}

void USelectClassWnd::NativeConstruct()
{
	Super::NativeConstruct();

	Button_BattleSide->OnClicked.AddDynamic(this, &USelectClassWnd::BattleSideIconClicked);
	Button_Sniper->OnClicked.AddDynamic(this, &USelectClassWnd::SniperIconClicked);
	Button_Idle->OnClicked.AddDynamic(this, &USelectClassWnd::IdleButtonClicked);
	Button_Walk->OnClicked.AddDynamic(this, &USelectClassWnd::WalkButtonClicked);
	Button_Run->OnClicked.AddDynamic(this, &USelectClassWnd::RunButtonClicked);
	Button_Start->OnClicked.AddDynamic(this, &USelectClassWnd::StartButtonClicked);
}

void USelectClassWnd::SetPreviewCharacter(APreviewCharacter* previewCharacter)
{ PreviewCharacter = previewCharacter; }

void USelectClassWnd::UpdateRow()
{
	FString contextString;
	FSCWndRowInfo* SCwndRowInfo = DT_SCWndRowInfo->FindRow<FSCWndRowInfo>(GetManager(UPlayerManager)->GetPlayerInfo()->CharacterCode,
		contextString);

	Text_Name->SetText(SCwndRowInfo->CharacterClassName);
	Text_Weapon->SetText(SCwndRowInfo->WeaponName);
	Text_Explain->SetText(SCwndRowInfo->CharacterClassExplain);
}

void USelectClassWnd::PlayerSkillSetting()
{
	FString contextString;
	TArray<FSkillInfo*> skillInfo;

	DT_SkillInfo->GetAllRows<FSkillInfo>(contextString, skillInfo);

	for (int i = 0; i < skillInfo.Num(); ++i)
	{
		if (skillInfo[i]->CharacterCode == GetManager(UPlayerManager)->GetPlayerInfo()->CharacterCode ||
			skillInfo[i]->SkillType == ESkillType::SKT_ITEM)
			GetManager(UPlayerManager)->GetPlayerInfo()->SkillInfo.Add(*skillInfo[i]);
	}
}

void USelectClassWnd::BattleSideIconClicked()
{ 
	GetManager(UPlayerManager)->GetPlayerInfo()->CharacterCode = FName(TEXT("0002"));
	PreviewCharacter->InitializeAsset();
	UpdateRow();
	IdleButtonClicked();
	PlayAnimation(BattleSide);
}

void USelectClassWnd::SniperIconClicked()
{ 
	GetManager(UPlayerManager)->GetPlayerInfo()->CharacterCode = FName(TEXT("0001")); 
	PreviewCharacter->InitializeAsset();
	UpdateRow();
	IdleButtonClicked();
	PlayAnimation(Sniper);
}

void USelectClassWnd::IdleButtonClicked()
{ PreviewCharacter->GetCharacterMovement()->MaxWalkSpeed = 0; }

void USelectClassWnd::WalkButtonClicked()
{ PreviewCharacter->GetCharacterMovement()->MaxWalkSpeed = 250; }

void USelectClassWnd::RunButtonClicked()
{ PreviewCharacter->GetCharacterMovement()->MaxWalkSpeed = 750; }

void USelectClassWnd::StartButtonClicked()
{
	PlayerSkillSetting();
	Cast<ULCGameInstance>(GetGameInstance())->SetNextLevelName(FName(TEXT("LobbyMap")));
	UGameplayStatics::OpenLevel(this, FName(TEXT("LoadingLevel")));
}
