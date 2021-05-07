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
	Text_InputKeyName->SetText(QuickSlotKeyName);
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
			if (GetQuickSlotSkillInfo().IsEmpty()) return;

			auto widgetData = CreateSlotDragWidget();
			auto dragWidget = widgetData.Get<0>();
			auto dragImage = widgetData.Get<1>();

			op->DefaultDragVisual = dragWidget;
			dragImage->SetBrushFromTexture(Cast<UTexture2D>(GetSlotImage()->Brush.GetResourceObject()));

			auto Logop = Cast<UQuickSlot>(op->DraggingSlot);
		});

	OnSlotDragFinished.AddLambda(
		[this](class USlotDragDropOperation* op)
		{
			switch (op->DraggingSlot->GetSlotType())
			{
			case ESlotType::SLT_SKILL:
				SetQuickSlotSkillInfo(FQuickSlotSkillInfo(QuickSlotKey, ESkillType::SKT_ACTIVE, op->DraggingSlot->GetInCode()));
				UpdateQuickSlot();
				break;
			case ESlotType::SLT_QUICK: SwapQuickSlot(Cast<UQuickSlot>(op->DraggingSlot), this);
				break;
			case ESlotType::SLT_INVENTORY:
				if (Cast<UItemSlot>(op->DraggingSlot)->GetItemInfo()->ItemType == EItemType::Consumption)
				{
					SetQuickSlotSkillInfo(FQuickSlotSkillInfo(QuickSlotKey, ESkillType::SKT_ITEM, op->DraggingSlot->GetInCode()));
					UpdateQuickSlot();
				}
				break;
			}

			// 아이템 이미지 색상을 기본 색상으로 설정합니다.
			op->DraggingSlot->SetSlotColorNormal();
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

	GetManager(UPlayerManager)->GetQuickManager()->ItemCountChangeEvent.AddLambda(
		[this](FName code, int32 count)
		{
			if (InCode == code)

				UpdateQuickSlot();
		});
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
	for (int i = 0; i < GetManager(UPlayerManager)->GetPlayerInfo()->QuickSlotSkillInfos.Num(); ++i)
	{
		if (GetManager(UPlayerManager)->GetPlayerInfo()->QuickSlotSkillInfos[i].QuickSlotKey == QuickSlotKey)
		{
			GetManager(UPlayerManager)->GetPlayerInfo()->QuickSlotSkillInfos[i] = FQuickSlotSkillInfo(QuickSlotKey);
			QuickSlotSkillInfo = FQuickSlotSkillInfo(QuickSlotKey);
			InitializeSlot(ESlotType::SLT_QUICK, QuickSlotSkillInfo.SkillCode, QuickSlotSkillInfo.SkillType);
		}
	}
	UpdateQuickSlot();
}

void UQuickSlot::InitializeSlot(ESlotType slotType, FName inCode, ESkillType skillType)
{
	Super::InitializeSlot(slotType, inCode, skillType);
}

void UQuickSlot::UpdateQuickSlot()
{
	if (InCode.IsNone())
	{
		Text_Value->SetText(FText::FromString(TEXT("")));
		SlotImageEmpty();
	}
	else
		UpdateQuickSlotInfoSkill();

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
			else Text_Value->SetText(FText::FromString(TEXT("")));
			CoolDownTime = GetManager(UPlayerManager)->GetPlayerInfo()->SkillInfo[i].SKillCoolDownTime;
		}
	}
}

void UQuickSlot::SwapQuickSlot(UQuickSlot* firstQuickSlot, UQuickSlot* SecondQuickSlot)
{
	auto tempItemInfo = firstQuickSlot->GetQuickSlotSkillInfo();
	firstQuickSlot->SetQuickSlotSkillInfo(SecondQuickSlot->GetQuickSlotSkillInfo());
	SecondQuickSlot->SetQuickSlotSkillInfo(tempItemInfo);

	firstQuickSlot->UpdateQuickSlot();
	SecondQuickSlot->UpdateQuickSlot();
}

FQuickSlotSkillInfo UQuickSlot::GetCodeToQuickSlotSkillInfo(FName code) const
{
	for (int i = 0; i < GetManager(UPlayerManager)->GetPlayerInfo()->QuickSlotSkillInfos.Num(); ++i)
	{
		if (GetManager(UPlayerManager)->GetPlayerInfo()->QuickSlotSkillInfos[i].SkillCode == code)
		{
			return GetManager(UPlayerManager)->GetPlayerInfo()->QuickSlotSkillInfos[i];
		}
	}

	return FQuickSlotSkillInfo();
}

void UQuickSlot::SetQuickSlotInfo(FQuickSlotInfo quickSlotInfo)
{
	QuickSlotKey = quickSlotInfo.QuickSlotKey;
	QuickSlotKeyName = quickSlotInfo.QuickSlotKeyName;
}

void UQuickSlot::InitializeQuickSlotSkillInfo(FQuickSlotSkillInfo quickSlotSkillInfo)
{
	QuickSlotSkillInfo  = quickSlotSkillInfo;
	InitializeSlot(ESlotType::SLT_QUICK, quickSlotSkillInfo.SkillCode, quickSlotSkillInfo.SkillType);
}

void UQuickSlot::SetQuickSlotSkillInfo(FQuickSlotSkillInfo quickSlotSkillInfo)
{
	for (int i = 0; i < GetManager(UPlayerManager)->GetPlayerInfo()->QuickSlotSkillInfos.Num(); ++i)
	{
		if (GetManager(UPlayerManager)->GetPlayerInfo()->QuickSlotSkillInfos[i].QuickSlotKey == QuickSlotKey)
		{
			quickSlotSkillInfo.QuickSlotKey = QuickSlotKey;
			GetManager(UPlayerManager)->GetPlayerInfo()->QuickSlotSkillInfos[i] = quickSlotSkillInfo;
			QuickSlotSkillInfo = quickSlotSkillInfo;
			InitializeSlot(ESlotType::SLT_QUICK, quickSlotSkillInfo.SkillCode, quickSlotSkillInfo.SkillType);
			return;
		}
	}
}

void UQuickSlot::SetQuickLockandUnlock(bool isLock)
{
	for (int i = 0; i < GetManager(UPlayerManager)->GetPlayerInfo()->QuickSlotSkillInfos.Num(); ++i)
	{
		if (GetManager(UPlayerManager)->GetPlayerInfo()->QuickSlotSkillInfos[i].QuickSlotKey == QuickSlotKey)
			GetManager(UPlayerManager)->GetPlayerInfo()->QuickSlotSkillInfos[i].bQuickSlotCoolDownTime = isLock;
	}
}