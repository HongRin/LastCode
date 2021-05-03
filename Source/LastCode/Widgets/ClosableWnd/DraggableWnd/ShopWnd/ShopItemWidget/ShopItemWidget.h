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


protected :
	virtual void NativeConstruct() override;

public :
	void UpdateSaleItem(struct FItemInfo* itemInfo);
	
};
