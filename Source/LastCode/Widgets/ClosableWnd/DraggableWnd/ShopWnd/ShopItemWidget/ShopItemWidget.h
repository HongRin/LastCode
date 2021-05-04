#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "ShopItemWidget.generated.h"

UCLASS()
class LASTCODE_API UShopItemWidget : public UUserWidget
{
	GENERATED_BODY()

private :
	UPROPERTY(meta = (BindWidget))
	class UItemSlot* BP_ItemSlot;

	UPROPERTY(meta = (BindWidget))
	class UTextBlock* Text_Name;

	UPROPERTY(meta = (BindWidget))
	class UTextBlock* Text_Silver;


private :
	class UShopWnd* ShopWnd;

protected :
	virtual void NativeConstruct() override;

public :
	void UpdateSaleItem(struct FItemInfo* itemInfo, class UShopWnd* shopWnd);

protected:
	// ���콺 ���� Ŭ�� �Է��� ���� ��� ȣ��˴ϴ�.
	virtual FReply NativeOnMouseButtonDoubleClick(
		const FGeometry& InGeometry, const FPointerEvent& InMouseEvent) override;
	/// - InGeometry : ������ ��ġ, ũ�⸦ ��Ÿ���ϴ�.
	/// - InMouseEvent : �Է� �̺�Ʈ ����

private:
	// �������� �����մϴ�.
	void BuyItem();
	
};
