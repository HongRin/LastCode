#include "SkillDetailWnd.h"
#include "Single/GameInstance/LCGameInstance.h"
#include "Single/PlayerManager/PlayerManager.h"
#include "Components/TextBlock.h"
#include "Components/Image.h"


void USkillDetailWnd::NativeConstruct()
{
	Super::NativeConstruct();

	SetVisibility(ESlateVisibility::HitTestInvisible);
}

void USkillDetailWnd::UpdateSkillDetailWnd(FName skillCode)
{
	ULCGameInstance* gameInst = Cast<ULCGameInstance>(GetGameInstance());

	FSkillInfo skillInfo;

	for (int i = 0; i < GetManager(UPlayerManager)->GetPlayerInfo()->SkillInfo.Num(); ++i)
	{
		if (skillCode == GetManager(UPlayerManager)->GetPlayerInfo()->SkillInfo[i].SkillCode)
		{
			skillInfo = GetManager(UPlayerManager)->GetPlayerInfo()->SkillInfo[i];
		}
	}
	

	UTexture2D* itemImage =
		Cast<UTexture2D>(GetManager(FStreamableManager)->LoadSynchronous(skillInfo.ImageSprite));

	Image_SkillSprite->SetBrushFromTexture(itemImage);

	Text_SkillLevel->SetText(FText::FromString(FString(TEXT("Lv ")) + FString::FromInt(skillInfo.SkillLevel)));

	Text_Name->SetText(skillInfo.SkillName);

	Text_Explain->SetText(skillInfo.SkillExplain);

	Text_CoolDownTime->SetText(FText::FromString(FString::Printf(TEXT("CoolDownTime : %.1f Second"), skillInfo.SKillCoolDownTime)));

	Text_Damage->SetText(FText::FromString(FString::Printf(TEXT("Damage : %.1f %"), skillInfo.SkillValue)));

	Text_Stamina->SetText(FText::FromString(FString::Printf(TEXT("Consumption Energy : %.0f"), skillInfo.SkillStamina)));
}
