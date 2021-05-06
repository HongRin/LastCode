#include "QuickSlot.h"
#include "Components/ProgressBar.h"
#include "Components/TextBlock.h"
#include "Components/Image.h"
#include "Single/GameInstance/LCGameInstance.h"
#include "Single/PlayerManager/PlayerManager.h"
#include "Widgets/ClosableWnd/DraggableWnd/InventoryWnd/ItemSlot/ItemSlot.h"


void UQuickSlot::NativeConstruct()
{
	Super::NativeConstruct();
	InitiailzeBind();

	StartTime = 0.0f;

	Image_Star->SetVisibility(ESlateVisibility::Hidden);
}

void UQuickSlot::NativeTick(const FGeometry& MyGeometry, float inDeltaTime)
{
	Super::NativeTick(MyGeometry, inDeltaTime);

	UpdateCoolDownTime();
}

void UQuickSlot::InitiailzeBind() 
{
	OnSlotDragStarted.AddLambda(
		[this](class USlotDragDropOperation* op) {
			if (GetQuickSlotInfo(QuickSlotkey).IsEmpty()) return;

			auto widgetData = CreateSlotDragWidget();
			auto dragWidget = widgetData.Get<0>();
			auto dragImage = widgetData.Get<1>();

			op->DefaultDragVisual = dragWidget;
			dragImage->SetBrushFromTexture(Cast<UTexture2D>(GetSlotImage()->Brush.GetResourceObject()));

			auto Logop = Cast<UQuickSlot>(op->DraggingSlot);

			LogPlayerQuickSlotInfo();
		});

	OnSlotDragFinished.AddLambda(
		[this](class USlotDragDropOperation* op)
		{
			switch (op->DraggingSlot->GetSlotType())
			{
			case ESlotType::SLT_SKILL:
				SetQuickSlotInfo(FQuickSlotInfo(QuickSlotkey, QuickSlotName, ESkillType::SKT_ACTIVE, op->DraggingSlot->GetInCode()));
				UpdateQuickSlot();
				break;
			case ESlotType::SLT_QUICK: SwapQuickSlot(Cast<UQuickSlot>(op->DraggingSlot), this);
				break;
			case ESlotType::SLT_INVENTORY:
				if (Cast<UItemSlot>(op->DraggingSlot)->GetItemInfo()->ItemType == EItemType::Consumption)
				{
					SetQuickSlotInfo(FQuickSlotInfo(QuickSlotkey, QuickSlotName, ESkillType::SKT_ITEM, op->DraggingSlot->GetInCode()));
					UpdateQuickSlot();
				}
				break;
			}

			// 아이템 이미지 색상을 기본 색상으로 설정합니다.
			op->DraggingSlot->SetSlotColorNormal();

			LogPlayerQuickSlotInfo();
		});

	OnSlotDragCancelled.AddLambda(
		[this](class USlotDragDropOperation* op) { SetQuickSlotEmpty(); });

	GetManager(UPlayerManager)->GetQuickManager()->QuickSlotEventStarted.AddLambda(
		[this](FName code)
		{
			if (InCode == code)
			{
				if (SkillType == ESkillType::SKT_ITEM)
				{
					int32 index = GetManager(UPlayerManager)->GetInventory()->GetSlotIndexByCode(code);
					if (InCode == code)
						GetManager(UPlayerManager)->GetInventory()->RemoveItem(index);
						UpdateQuickSlot();
				}
				StartTime = GetWorld()->GetTimeSeconds();
				SetQuickLockandUnlock(true);
			} 
		});

	GetManager(UPlayerManager)->GetQuickManager()->SkillLevelUpdateEvent.AddLambda(
		[this](FName code, int32 skilLevel)
		{
			auto quickSlotInfo = GetCodeToQuickSlotInfo(code);
			if (QuickSlotkey == quickSlotInfo.QuickSlotKey)
				Text_Value->SetText(FText::FromString(FString::Printf(TEXT("Lv %d"), skilLevel)));
		});

	GetManager(UPlayerManager)->GetQuickManager()->ItemCountChangeEvent.AddLambda(
		[this](FName code, int32 count)
		{
			if (InCode == code)

				UpdateQuickSlot();
		});
}

void UQuickSlot::LogPlayerQuickSlotInfo()
{
	for (int i = 0; i < GetManager(UPlayerManager)->GetPlayerInfo()->QuickSlotInfos.Num(); ++i)
	{
		UE_LOG(LogTemp, Warning, TEXT(
			"LogPlayerQuickSlotInfo::QuickSlotInfos[%d]::QuickSlotKey[%s]::SkillCode[%s]::SkillType[%s]"), i + 1,
			*GetManager(UPlayerManager)->GetPlayerInfo()->QuickSlotInfos[i].QuickSlotKey.ToString(),
			*GetManager(UPlayerManager)->GetPlayerInfo()->QuickSlotInfos[i].SkillCode.ToString(),
			*GetESkillTypeToString(GetManager(UPlayerManager)->GetPlayerInfo()->QuickSlotInfos[i].SkillType));
	}
}

FString UQuickSlot::GetESkillTypeToString(ESkillType skillTypeValue)
{
	const UEnum* enumPtr = FindObject<UEnum>(ANY_PACKAGE, TEXT("ESkillType"), true);
	if (!enumPtr)
	{
		return FString("Invalid");

	}
	return enumPtr->GetNameStringByIndex((int32)skillTypeValue);
	
}

void UQuickSlot::UpdateCoolDownTime()
{
	if (StartTime <= 0 || InCode.IsNone()) return;

	float elapsedTime = GetWorld()->GetTimeSeconds() - StartTime;
	
	float coolTime = CoolDownTime - elapsedTime;

	ProgressBar_CoolDownTime->SetPercent((coolTime / CoolDownTime));

	if (elapsedTime > CoolDownTime)
	{
		PlayAnimation(QuickSlotActivation);
		SetQuickLockandUnlock(false);
		StartTime = 0.0f;
	}
}

void UQuickSlot::SetQuickSlotEmpty()
{
	SetQuickSlotInfo(FQuickSlotInfo(QuickSlotkey, QuickSlotName));
	UpdateQuickSlot();
}

void UQuickSlot::InitializeSlot(ESlotType slotType, FName inCode, ESkillType skillType)
{
	Super::InitializeSlot(slotType, inCode, skillType);
}

void UQuickSlot::UpdateQuickSlot()
{
	auto quickSlotInfo = GetQuickSlotInfo(QuickSlotkey);

	QuickSlotName = quickSlotInfo.QuickSlotName;

	if (InCode.IsNone())
	{
		Text_Value->SetText(FText::FromString(TEXT("")));
		SlotImageEmpty();
	}
	else
		UpdateQuickSlotInfoSkill();

	Text_InputKeyName->SetText(quickSlotInfo.QuickSlotName);
	ProgressBar_CoolDownTime->SetPercent(0.0f);
}
void UQuickSlot::UpdateQuickSlotInfoSkill()
{
	for (int i = 0; i < GetManager(UPlayerManager)->GetPlayerInfo()->SkillInfo.Num(); ++i)
	{
		if (GetManager(UPlayerManager)->GetPlayerInfo()->SkillInfo[i].SkillCode == InCode)
		{
			ULCGameInstance* gameInst = Cast<ULCGameInstance>(GetGameInstance());
			UTexture2D* itemImage =
				Cast<UTexture2D>(GetManager(FStreamableManager)->LoadSynchronous(GetManager(UPlayerManager)->GetPlayerInfo()->SkillInfo[i].ImageSprite));
			GetSlotImage()->SetBrushFromTexture(itemImage);
			int32 skillLevel = GetManager(UPlayerManager)->GetPlayerInfo()->SkillInfo[i].SkillLevel;
			if (GetManager(UPlayerManager)->GetPlayerInfo()->SkillInfo[i].SkillType == ESkillType::SKT_ITEM)
			{
				if (skillLevel <= 0) SetQuickSlotEmpty();
				Text_Value->SetText(FText::FromString(FString::FromInt(skillLevel)));
			}
			else
			{
				if (GetManager(UPlayerManager)->GetQuickManager()->SkillLevelUpdateEvent.IsBound())
					GetManager(UPlayerManager)->GetQuickManager()->SkillLevelUpdateEvent.Broadcast(
						QuickSlotkey, skillLevel);
			}
			CoolDownTime = GetManager(UPlayerManager)->GetPlayerInfo()->SkillInfo[i].SKillCoolDownTime;
		}
	}
}

void UQuickSlot::SwapQuickSlot(UQuickSlot* firstQuickSlot, UQuickSlot* SecondQuickSlot)
{
	auto tempItemInfo = firstQuickSlot->GetQuickSlotInfo();
	firstQuickSlot->SetQuickSlotInfo(SecondQuickSlot->GetQuickSlotInfo());
	SecondQuickSlot->SetQuickSlotInfo(tempItemInfo);

	firstQuickSlot->UpdateQuickSlot();
	SecondQuickSlot->UpdateQuickSlot();
}

FQuickSlotInfo UQuickSlot::GetQuickSlotInfo(FName quickSlotkey) const
{
	for (int i = 0; i < GetManager(UPlayerManager)->GetPlayerInfo()->QuickSlotCount; ++i)
	{
		if (GetManager(UPlayerManager)->GetPlayerInfo()->QuickSlotInfos[i].QuickSlotKey == quickSlotkey)
		{
			return GetManager(UPlayerManager)->GetPlayerInfo()->QuickSlotInfos[i];
		}
	}

	return FQuickSlotInfo();
}

FQuickSlotInfo UQuickSlot::GetCodeToQuickSlotInfo(FName code) const
{
	for (int i = 0; i < GetManager(UPlayerManager)->GetPlayerInfo()->QuickSlotCount; ++i)
	{
		if (GetManager(UPlayerManager)->GetPlayerInfo()->QuickSlotInfos[i].SkillCode == code)
		{
			return GetManager(UPlayerManager)->GetPlayerInfo()->QuickSlotInfos[i];
		}
	}

	return FQuickSlotInfo();
}

void UQuickSlot::SetQuickSlotInfo(FQuickSlotInfo quickSlotInfo)
{
	FName quickSlotKey = QuickSlotkey.IsNone() ? quickSlotInfo.QuickSlotKey : QuickSlotkey;

	for (int i = 0; i < GetManager(UPlayerManager)->GetPlayerInfo()->QuickSlotCount; ++i)
	{
		if (GetManager(UPlayerManager)->GetPlayerInfo()->QuickSlotInfos[i].QuickSlotKey == quickSlotKey)
		{
			GetManager(UPlayerManager)->GetPlayerInfo()->QuickSlotInfos[i].SkillCode = quickSlotInfo.SkillCode;
			GetManager(UPlayerManager)->GetPlayerInfo()->QuickSlotInfos[i].SkillType = quickSlotInfo.SkillType;
			QuickSlotInfo = GetManager(UPlayerManager)->GetPlayerInfo()->QuickSlotInfos[i];
			InitializeSlot(ESlotType::SLT_QUICK, quickSlotInfo.SkillCode, quickSlotInfo.SkillType);
		}
	}
}

void UQuickSlot::SetQuickLockandUnlock(bool isLock)
{
	for (int i = 0; i < GetManager(UPlayerManager)->GetPlayerInfo()->QuickSlotInfos.Num(); ++i)
	{
		if (GetManager(UPlayerManager)->GetPlayerInfo()->QuickSlotInfos[i].QuickSlotKey == QuickSlotkey)
			GetManager(UPlayerManager)->GetPlayerInfo()->QuickSlotInfos[i].bQuickSlotCoolDownTime = isLock;
	}
}