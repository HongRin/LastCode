#pragma once

#include "LastCode.h"
#include "Widgets/ClosableWnd/ClosableWnd.h"
#include "InventoryWnd.generated.h"



UCLASS()
class LASTCODE_API UInventoryWnd : public UClosableWnd
{
	GENERATED_BODY()

public :

private:
	TSubclassOf<class UInventoryItemSlot> BP_InventoryItemSlot;

private:
	TArray<class UInventoryItemSlot*> ItemSlots;

private:
	UPROPERTY(meta = (BindWidget))
		class UGridPanel* GridPanel_ItemSlots;

	UPROPERTY(meta = (BindWidget))
		class UTextBlock* Text_Silver;

public:
	UInventoryWnd(const FObjectInitializer& ObjectInitializer);

protected:
	virtual void NativeConstruct() override;

private:
	void InitializeInventoryWnd();

	// 아이템 슬롯을 생성합니다.
	class UInventoryItemSlot* CreateItemSlot();

public:
	// 인벤토리 아이템 슬롯들을 갱신합니다.
	void UpdateInventoryItemSlots();

	// 소지금을 갱신합니다.
	void UpdateSilver();

public:
	TArray<class UInventoryItemSlot*>& GetItemSlots()
	{ return ItemSlots; }
	
};
