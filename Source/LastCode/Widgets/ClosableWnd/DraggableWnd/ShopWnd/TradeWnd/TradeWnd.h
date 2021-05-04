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
	// 트레이드 버튼이 눌렸을 경우 호출되는 대리자
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
	// 입력한 문자열이 비어있는지 확인합니다.
	bool IsInputTextEmpty() const;

	// 입력한 개수를 int32 형식으로 반환합니다.
	int32 GetInputTradeCount() const;

	FORCEINLINE class UItemSlot* GetConnectedItemSlot() const
	{ return ConnectedItemSlot; }

};
