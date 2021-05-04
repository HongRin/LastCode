#pragma once

#include "LastCode.h"
#include "Widgets/ClosableWnd/ClosableWnd.h"
#include "ShopWnd.generated.h"

UCLASS()
class LASTCODE_API UShopWnd : public UClosableWnd
{
	GENERATED_BODY()

private :
	class TSubclassOf<class UShopItemWidget> BP_ShopItemWidget;

	class TSubclassOf<class UTradeWnd> BP_TradeWnd;

	class UTradeWnd* TradeWnd;

	class UDataTable* DT_SaleItemInfo;

	UPROPERTY(meta = (BindWidget))
	class UGridPanel* GridPanel_SaleList;

	UPROPERTY(meta = (BindWidget))
	class UCanvasPanel* CanvasPanel_Trade;

public :
	UShopWnd(const FObjectInitializer& ObjInitializer);

protected :
	virtual void NativeConstruct() override; 

private :
	void InitializeSaleItem();

	// 아이템을 판매합니다.
	void SaleItem(class UInventoryWnd* inventoryWnd, class UItemSlot* itemSlot);

public :
	class UTradeWnd* CreateTradeWnd(class UItemSlot* connectedItemSlot, bool bSaleItem);

	void CloseTradeWnd();

public:
	// 인벤토리 창을 상점 창 우측에 띄웁니다.
	UFUNCTION()
	void FloatingInventoryWnd();

};
