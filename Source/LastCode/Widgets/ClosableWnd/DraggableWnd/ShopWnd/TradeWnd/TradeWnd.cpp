#include "TradeWnd.h"

#include "Structures/ItemInfo/ItemInfo.h"

#include "Single/GameInstance/LCGameInstance.h"
#include "Single/PlayerManager/PlayerManager.h"

#include "Widgets/ClosableWnd/DraggableWnd/InventoryWnd/ItemSlot/InventoryItemSlot.h"
#include "Widgets/ClosableWnd/DraggableWnd/ShopWnd/ShopWnd.h"


#include "Components/EditableTextBox.h"
#include "Components/TextBlock.h"
#include "Components/Button.h"

void UTradeWnd::NativeConstruct()
{
	Super::NativeConstruct();

	Button_Trade->OnClicked.AddDynamic(this, &UTradeWnd::OnTradeButtonClicked);
	Button_Cancel->OnClicked.AddDynamic(this, &UTradeWnd::OnCancelButtonClicked);
	EditableTextBox_TradeCount->OnTextChanged.AddDynamic(this, &UTradeWnd::OnTradeCountTextChanged);
}

void UTradeWnd::InitializeTradeWnd(class UItemSlot* connectedItemSlot, bool bSaleItem, UShopWnd* shopWnd)
{
	ConnectedItemSlot = connectedItemSlot;
	IsSaleItem = bSaleItem;
	ShopWnd = shopWnd;
	Text_Name->SetText(ConnectedItemSlot->GetItemInfo()->ItemName);
	Text_Price->SetText(FText::FromString(FString::FromInt(ConnectedItemSlot->GetItemInfo()->Price)));
}

void UTradeWnd::OnTradeButtonClicked()
{
	if (OnTradeButtonClickedEvent.IsBound())
		OnTradeButtonClickedEvent.Broadcast(this);
}

void UTradeWnd::OnTradeCountTextChanged(const FText& Text)
{
	// EditableTextBox �� ������ int32 ���� �����ͷ� �����մϴ�.
	Action(fnSetEditTextContentFromInt, (UEditableTextBox*, int32)) =
		[](UEditableTextBox* editableTextBox, int32 value)
	{ editableTextBox->SetText(FText::FromString(FString::FromInt(value))); };

	// TextBlock �� ������ int32 ���� �����ͷ� �����մϴ�.
	Action(fnSetTextBlockContentFromInt, (UTextBlock*, int32)) =
		[](UTextBlock* textBlock, int32 value)
	{ textBlock->SetText(FText::FromString(FString::FromInt(value))); };

	// ���޵� FText �����͸� ���ڷ� �����Ͽ� ��ȯ�մϴ�.
	Func(int32, fnTextToInt, (const FText&)) =
		[](const FText& fromText)
	{
		return FCString::Atoi(*fromText.ToString());
		/// - FCString : C Style �� ���ڿ��� �Բ� ���Ǵ� �Լ����� �����ϴ� ����ü
	};

	// �ԷµǾ��ִ� ���ڿ��� ������� ������, ���ڰ� �ƴ϶��
	if (!Text.IsNumeric())
	{
		EditableTextBox_TradeCount->SetText(FText());
		fnSetTextBlockContentFromInt(Text_Result, 0);
		return;
	}

	// �Էµ� ���ڿ��� ���ڷ� �����Ͽ� �����մϴ�.
	int32 tradeCount = fnTextToInt(Text);

	// ��ȯ ������ �ִ� ������ ������ �����մϴ�.
	int32 maxTradeCount = 0;

	// ������ ������ ��Ÿ���ϴ�.
	int32 price = 0;

	if(IsSaleItem)
	{
		// ������
		int32 silver = GetManager(UPlayerManager)->GetPlayerInfo()->Silver;

		// ������ ���� ����
		price = ConnectedItemSlot->GetItemInfo()->Price;

		// �ִ� ���� ������ ������ ������ �ִ�� ���� ������ ������ ������ �����մϴ�.
		maxTradeCount = (int32)(silver / price);

		// ��� �������̶�� �ִ� ���� ���� ������ 1 �� �����մϴ�.
		if (ConnectedItemSlot->GetItemInfo()->ItemType == EItemType::Equipment)
			if (maxTradeCount != 0) maxTradeCount = 1;
	}
	else
	{
		// �Ǹ��Ϸ��� ������ ���� �ε����� ����ϴ�.
		int32 slotIndex = Cast<UInventoryItemSlot>(ConnectedItemSlot)->GetItemSlotIndex();

		// �Ǹ��Ϸ��� ������ ���� ������ ����ϴ�.
		auto slotInfo = GetManager(UPlayerManager)->GetPlayerInfo()->InventoryItemInfos[slotIndex];

		// ������ ������ ����ϴ�.
		price = ConnectedItemSlot->GetItemInfo()->Price;

		// �ִ� �Ǹ� ������ ������ ������ ������ ������ ������ �����մϴ�.
		maxTradeCount = slotInfo.ItemCount;
	}

	// �ִ� ��ȯ ������ �ʰ��ߴٸ� �Էµ� ���ڸ� �ִ� ��ȯ ���� ������ �����մϴ�.
	if (tradeCount > maxTradeCount) tradeCount = maxTradeCount;

	// ���� ������ �����մϴ�.
	fnSetEditTextContentFromInt(EditableTextBox_TradeCount, tradeCount);

	// ������ �����մϴ�.
	fnSetTextBlockContentFromInt(Text_Result, price * tradeCount);

}

void UTradeWnd::OnCancelButtonClicked()
{
	ShopWnd->CloseTradeWnd();
}

bool UTradeWnd::IsInputTextEmpty() const
{
	return EditableTextBox_TradeCount->GetText().IsEmpty();
}

int32 UTradeWnd::GetInputTradeCount() const
{
	return FCString::Atoi(*EditableTextBox_TradeCount->GetText().ToString());
}
