#pragma once

#include "LastCode.h"
#include "Blueprint/UserWidget.h"
#include "ItemDetailWnd.generated.h"

UCLASS()
class LASTCODE_API UItemDetailWnd : public UUserWidget
{
	GENERATED_BODY()

private :
	class UDataTable* DT_ItemInfo;

private:
	UPROPERTY(meta = (BindWidget))
		class UImage* Image_ItemSprite;

	UPROPERTY(meta = (BindWidget))
		class UTextBlock* Text_Name;

	UPROPERTY(meta = (BindWidget))
		class UTextBlock* Text_ItemType;

	UPROPERTY(meta = (BindWidget))
		class UTextBlock* Text_Explain;

public :
	UItemDetailWnd(const FObjectInitializer& ObjInitializer);

protected:
	virtual void NativeConstruct() override;

public:
	void UpdateItemDetailWnd(FName ItemCode);
	
};
