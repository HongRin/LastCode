#include "TradeWnd.h"

#include "Structures/ItemInfo/ItemInfo.h"

#include "Widgets/ClosableWnd/DraggableWnd/InventoryWnd/ItemSlot/InventoryItemSlot.h"


#include "Components/EditableTextBox.h"
#include "Components/TextBlock.h"
#include "Components/Button.h"

void UTradeWnd::NativeConstruct()
{
	Super::NativeConstruct();

	Button_Trade->OnClicked.AddDynamic(this, &UTradeWnd::OnTradeButtonClicked);
	Button_Cancel->OnClicked.AddDynamic(this, &UTradeWnd::OnCancelButtonClicked);
}

void UTradeWnd::InitializeTradeWnd(class UItemSlot* connectedItemSlot, bool bSaleItem)
{
	ConnectedItemSlot = connectedItemSlot;
	Text_Name->SetText(ConnectedItemSlot->GetItemInfo()->ItemName);
	Text_Price->SetText(FText::FromString(FString::FromInt(ConnectedItemSlot->GetItemInfo()->Price)));
}

void UTradeWnd::OnTradeButtonClicked()
{

}

void UTradeWnd::OnCancelButtonClicked()
{

}

bool UTradeWnd::IsInputTextEmpty() const
{
	return EditableTextBox_TradeCount->GetText().IsEmpty();
}

int32 UTradeWnd::GetInputTradeCount() const
{
	return FCString::Atoi(*EditableTextBox_TradeCount->GetText().ToString());
}
