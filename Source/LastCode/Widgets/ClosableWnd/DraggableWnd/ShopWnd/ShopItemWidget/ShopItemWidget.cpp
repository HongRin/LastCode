#include "ShopItemWidget.h"

#include "Widgets/ClosableWnd/DraggableWnd/InventoryWnd/ItemSlot/ItemSlot.h"
#include "Components/TextBlock.h"

void UShopItemWidget::NativeConstruct()
{
	Super::NativeConstruct();


}

void UShopItemWidget::UpdateSaleItem(FItemInfo* itemInfo)
{
	BP_ItemSlot->InitializeSlot(ESlotType::SLT_ITME, itemInfo->ItemCode, ESkillType::SKT_ITEM);
	
	BP_ItemSlot->UpdateItemImage();
	BP_ItemSlot->SetSlotItemCount(0);

	Text_Name->SetText(itemInfo->ItemName);
	Text_Silver->SetText(FText::FromString(FString::FromInt(itemInfo->Price)));
	
}
