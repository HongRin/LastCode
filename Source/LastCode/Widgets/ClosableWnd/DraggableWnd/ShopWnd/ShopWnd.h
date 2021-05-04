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

	// �������� �Ǹ��մϴ�.
	void SaleItem(class UInventoryWnd* inventoryWnd, class UItemSlot* itemSlot);

public :
	class UTradeWnd* CreateTradeWnd(class UItemSlot* connectedItemSlot, bool bSaleItem);

	void CloseTradeWnd();

public:
	// �κ��丮 â�� ���� â ������ ���ϴ�.
	UFUNCTION()
	void FloatingInventoryWnd();

};
