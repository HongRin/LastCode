#include "ItemDetailWnd.h"
#include "Single/GameInstance/LCGameInstance.h"
#include "Single/PlayerManager/PlayerManager.h"
#include "Engine/DataTable.h"
#include "Structures/ItemInfo/ItemInfo.h"
#include "Components/TextBlock.h"
#include "Components/Image.h"

UItemDetailWnd::UItemDetailWnd(const FObjectInitializer& ObjInitializer) :
	Super(ObjInitializer)
{
	static ConstructorHelpers::FObjectFinder<UDataTable> DT_ITEM_INFO(
		TEXT("DataTable'/Game/Resources/DataTable/DT_ItemInfo.DT_ItemInfo'"));
	if (DT_ITEM_INFO.Succeeded()) DT_ItemInfo = DT_ITEM_INFO.Object;
}

void UItemDetailWnd::NativeConstruct()
{
	Super::NativeConstruct();

	SetVisibility(ESlateVisibility::HitTestInvisible);

}

void UItemDetailWnd::UpdateItemDetailWnd(FName ItemCode)
{
	FString contextString;
	auto ItemInfo = DT_ItemInfo->FindRow<FItemInfo>(ItemCode, contextString);

	Text_Name->SetText(ItemInfo->ItemName);

	switch(ItemInfo->ItemType)
	{
	case EItemType::Consumption :
		Text_ItemType->SetText(FText::FromString(FString(TEXT("ItemType : 소비아이템"))));
		break;
	case EItemType::Equipment :
		Text_ItemType->SetText(FText::FromString(FString(TEXT("ItemType : 장비아이템"))));
		break;
	case EItemType::EtCetera :
		Text_ItemType->SetText(FText::FromString(FString(TEXT("ItemType : 기타아이템"))));
		break;
	}
	Text_Explain->SetText(ItemInfo->ItemDescription);

	auto itemImage = Cast<UTexture2D>(GetManager(FStreamableManager)->LoadSynchronous(ItemInfo->ItemImagePath));

	Image_ItemSprite->SetBrushFromTexture(itemImage);
}
