#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "TradeWnd.generated.h"

DECLARE_MULTICAST_DELEGATE_OneParam(FTradeWndButtonSignature, class UTradeWnd*)

UCLASS()
class LASTCODE_API UTradeWnd : public UUserWidget
{
	GENERATED_BODY()

public:
	// Ʈ���̵� ��ư�� ������ ��� ȣ��Ǵ� �븮��
	FTradeWndButtonSignature OnTradeButtonClickedEvent;

private :
	UPROPERTY(meta = (BindWidget))
	class UTextBlock* Text_Name;

	UPROPERTY(meta = (BindWidget))
	class UTextBlock* Text_Price;

	UPROPERTY(meta = (BindWidget))
	class UTextBlock* Text_Result;

	UPROPERTY(meta = (BindWidget))
	class UEditableTextBox* EditableTextBox_TradeCount;

	UPROPERTY(meta = (BindWidget))
	class UButton* Button_Trade;

	UPROPERTY(meta = (BindWidget))
	class UButton* Button_Cancel;

private :
	class UItemSlot* ConnectedItemSlot;

	class UShopWnd* ShopWnd;

	bool IsSaleItem;

protected :
	virtual void NativeConstruct() override;

public :
	void InitializeTradeWnd(class UItemSlot* connectedItemSlot, bool bSaleItem, class UShopWnd* shopWnd);


private :
	UFUNCTION()
	void OnTradeButtonClicked();

	UFUNCTION()
	void OnTradeCountTextChanged(const FText& Text);

public :
	UFUNCTION()
	void OnCancelButtonClicked();

public :
	// �Է��� ���ڿ��� ����ִ��� Ȯ���մϴ�.
	bool IsInputTextEmpty() const;

	// �Է��� ������ int32 �������� ��ȯ�մϴ�.
	int32 GetInputTradeCount() const;

	FORCEINLINE class UItemSlot* GetConnectedItemSlot() const
	{ return ConnectedItemSlot; }

};
