#include "FieldRow.h"

#include "Single/GameInstance/LCGameInstance.h"
#include "Single/PlayerManager/PlayerManager.h"

#include "Components/TextBlock.h"
#include "Components/Image.h"
#include "Components/Button.h"
#include "Components/CanvasPanel.h"

UFieldRow::UFieldRow(const FObjectInitializer& ObjInitializer) :
	Super(ObjInitializer)
{
}

void UFieldRow::NativeConstruct()
{
	Super::NativeConstruct();

	Difficulty = 0;


	Button_Next->OnClicked.AddDynamic(this, &UFieldRow::NextButtonClicked);
	Button_Previous->OnClicked.AddDynamic(this, &UFieldRow::PreviousButtonClicked);
}

void UFieldRow::UpdateFieldRow(FFieldInfo* fieldInfo)
{
	Text_Name->SetText(FText::FromString(fieldInfo->FieldName.ToString()));

	auto imageTexture = Cast<UTexture2D>(GetManager(FStreamableManager)->LoadSynchronous(fieldInfo->FieldImagePath));

	Image_Field->SetBrushFromTexture(imageTexture);

	SetLock(fieldInfo->FieldUnLockLevel);

	SetDifficulty();
}

void UFieldRow::SetDifficulty()
{
	switch (Difficulty)
	{
	case 0 :
		Text_Difficulty->SetText(FText::FromString(FString(TEXT("Normal"))));
		Text_Difficulty->SetColorAndOpacity(FLinearColor(1.0f, 1.0f, 1.0f, 1.0f));
		Image_Diffuclty->SetColorAndOpacity(FLinearColor(1.0f, 1.0f, 1.0f, 0.0f));
		break;
	case 1:
		Text_Difficulty->SetText(FText::FromString(FString(TEXT("Expert"))));
		Text_Difficulty->SetColorAndOpacity(FLinearColor(0.14f, 0.45f, 1.0f, 1.0f));
		Image_Diffuclty->SetColorAndOpacity(FLinearColor(0.0f, 0.03f, 1.0f, 0.2f));

		break;
	case 2:
		Text_Difficulty->SetText(FText::FromString(FString(TEXT("Master"))));
		Text_Difficulty->SetColorAndOpacity(FLinearColor(0.25f, 0.0f, 1.0f, 1.0f));
		Image_Diffuclty->SetColorAndOpacity(FLinearColor(0.38f, 0.0f, 1.0f, 0.2f));
		break;
	case 3:
		Text_Difficulty->SetText(FText::FromString(FString(TEXT("King"))));
		Text_Difficulty->SetColorAndOpacity(FLinearColor(1.0f, 0.0f, 0.8f, 1.0f));
		Image_Diffuclty->SetColorAndOpacity(FLinearColor(1.0f, 0.3f, 0.0f, 0.2f));
		break;
	case 4:
		Text_Difficulty->SetText(FText::FromString(FString(TEXT("Slayer"))));
		Text_Difficulty->SetColorAndOpacity(FLinearColor(1.0f, 0.0f, 0.0f, 1.0f));
		Image_Diffuclty->SetColorAndOpacity(FLinearColor(1.0f, 0.0f, 0.0f, 0.2f));

		break;
	}
}

void UFieldRow::SetLock(int32 unLockLevel)
{
	int32 playerLevel = GetManager(UPlayerManager)->GetPlayerInfo()->Level;
	
	if (playerLevel > unLockLevel)
	{
		Text_Qualification->SetText(FText::FromString(FString(TEXT(""))));
		CanvasPanel_Lock->SetVisibility(ESlateVisibility::Hidden);
	}
	else
	{
		CanvasPanel_Lock->SetVisibility(ESlateVisibility::Visible);
		Text_Qualification->SetText(FText::FromString(FString::Printf(TEXT("Requires level %d of the player"), unLockLevel)));
	}
}

void UFieldRow::PreviousButtonClicked()
{
	--Difficulty;
	if (Difficulty < 0) Difficulty = 0;
	else PlayAnimation(DifficultyDown);
	SetDifficulty();
}

void UFieldRow::NextButtonClicked()
{
	++Difficulty;
	if (Difficulty > 4) Difficulty = 4;
	else PlayAnimation(DifficultyUp);
	SetDifficulty();
}
