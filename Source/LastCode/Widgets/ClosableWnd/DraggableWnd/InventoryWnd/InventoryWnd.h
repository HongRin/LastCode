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

	// ������ ������ �����մϴ�.
	class UInventoryItemSlot* CreateItemSlot();

public:
	// �κ��丮 ������ ���Ե��� �����մϴ�.
	void UpdateInventoryItemSlots();

	// �������� �����մϴ�.
	void UpdateSilver();

public:
	TArray<class UInventoryItemSlot*>& GetItemSlots()
	{ return ItemSlots; }
	
};
