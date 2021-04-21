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

	// 아이템 정보 설정
	SetItemInfo(inCode);

	// 아이템 이미지 갱신
	UpdateItemImage();
}

void UItemSlot::UpdateItemImage()
{
	UTexture2D* itemImage = nullptr;

	// 아이템 정보가 비어있다면 투명한 이미지를 사용합니다.
	if (ItemInfo.IsEmpty()) itemImage = T_Null;

	// 아이템 정보가 비어있지 않을 경우
	else
	{
		// 아이템 이미지 경로가 비어있다면 투명한 이미지 사용
		if (ItemInfo.ItemImagePath.IsNull())
			itemImage = T_Null;

		// 아이템 이미지 경로가 비어있지 않다면 아이템 이미지를 로드하여 사용합니다.
		else itemImage = Cast<UTexture2D>(
			GetManager(FStreamableManager)->LoadSynchronous(ItemInfo.ItemImagePath));
		//FStreamableDelegate onLoadFin;
		//onLoadFin.BindLambda([]() { 
		//	GetSlotImage()->SetBrushFromTexture(itemImage);
		//	});
		//GetManager(FStreamableManager)->RequestAsyncLoad(ItemInfo.ItemImagePath, onLoadFin);
	}

	// 아이템 이미지 적용
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
	// 아이템 코드가 비어있다면
	if (itemCode.IsNone())
	{
		// 아이템 정보를 비웁니다.
		ItemInfo = FItemInfo();
		return;
	}

	// 아이템 정보 찾기
	FString contextString;
	FItemInfo* findedItemInfo = DT_ItemInfo->FindRow<FItemInfo>(itemCode, contextString);

	// 아이템 정보를 찾지 못했다면 아이템 정보를 비웁니다.
	if (findedItemInfo == nullptr) ItemInfo = FItemInfo();
	else ItemInfo = *findedItemInfo;
}
