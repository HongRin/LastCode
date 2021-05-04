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
	// 마우스 더블 클릭 입력이 있을 경우 호출됩니다.
	virtual FReply NativeOnMouseButtonDoubleClick(
		const FGeometry& InGeometry, const FPointerEvent& InMouseEvent) override;
	/// - InGeometry : 위젯의 위치, 크기를 나타냅니다.
	/// - InMouseEvent : 입력 이벤트 종류

private:
	// 아이템을 구매합니다.
	void BuyItem();
	
};
