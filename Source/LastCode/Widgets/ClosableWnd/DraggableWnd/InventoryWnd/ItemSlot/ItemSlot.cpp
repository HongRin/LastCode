 #include "ItemSlot.h"

#include "Single/GameInstance/LCGameInstance.h"

#include "Components/Image.h"
#include "Components/TextBlock.h"

UItemSlot::UItemSlot(const FObjectInitializer& objectInitializer) :
	Super(objectInitializer)
{
	static ConstructorHelpers::FObjectFinder<UDataTable> DT_ITEM_INFO(
		TEXT("DataTable'/Game/Resources/DataTable/DT_ItemInfo.DT_ItemInfo'"));
	if (DT_ITEM_INFO.Succeeded()) DT_ItemInfo = DT_ITEM_INFO.Object;


}

void UItemSlot::InitializeSlot(ESlotType slotType, FName inCode, ESkillType skillType)
{
	Super::InitializeSlot(slotType, inCode, skillType);

	// ������ ���� ����
	SetItemInfo(inCode);

	// ������ �̹��� ����
	UpdateItemImage();
}

void UItemSlot::UpdateItemImage()
{
	UTexture2D* itemImage = nullptr;

	// ������ ������ ����ִٸ� ������ �̹����� ����մϴ�.
	if (ItemInfo.IsEmpty()) itemImage = T_Null;

	// ������ ������ ������� ���� ���
	else
	{
		// ������ �̹��� ��ΰ� ����ִٸ� ������ �̹��� ���
		if (ItemInfo.ItemImagePath.IsNull())
			itemImage = T_Null;

		// ������ �̹��� ��ΰ� ������� �ʴٸ� ������ �̹����� �ε��Ͽ� ����մϴ�.
		else itemImage = Cast<UTexture2D>(
			GetManager(FStreamableManager)->LoadSynchronous(ItemInfo.ItemImagePath));
		//FStreamableDelegate onLoadFin;
		//onLoadFin.BindLambda([]() { 
		//	GetSlotImage()->SetBrushFromTexture(itemImage);
		//	});
		//GetManager(FStreamableManager)->RequestAsyncLoad(ItemInfo.ItemImagePath, onLoadFin);
	}

	// ������ �̹��� ����
	GetSlotImage()->SetBrushFromTexture(itemImage);
}

void UItemSlot::SetSlotItemCount(int32 itemCount, bool bVisible01Count)
{
	FText itemCountText = FText::FromString(FString::FromInt(itemCount));

	Text_ItemCount->SetText(
		(!bVisible01Count && itemCount <= 1) ?
		FText() : itemCountText);
}


void UItemSlot::SetItemInfo(FName itemCode)
{
	// ������ �ڵ尡 ����ִٸ�
	if (itemCode.IsNone())
	{
		// ������ ������ ���ϴ�.
		ItemInfo = FItemInfo();
		return;
	}

	// ������ ���� ã��
	FString contextString;
	FItemInfo* findedItemInfo = DT_ItemInfo->FindRow<FItemInfo>(itemCode, contextString);

	// ������ ������ ã�� ���ߴٸ� ������ ������ ���ϴ�.
	if (findedItemInfo == nullptr) ItemInfo = FItemInfo();
	else ItemInfo = *findedItemInfo;
}
