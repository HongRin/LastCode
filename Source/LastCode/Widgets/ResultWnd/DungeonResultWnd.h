#pragma once

#include "LastCode.h"
#include "Blueprint/UserWidget.h"
#include "Enums/ClearType.h"
#include "Structures/ItemSlotInfo/ItemSlotInfo.h"
#include "DungeonResultWnd.generated.h"

UCLASS()
class LASTCODE_API UDungeonResultWnd : public UUserWidget
{
	GENERATED_BODY()

private:
	TSubclassOf<class UItemSlot> BP_ItemSlot;

private :
	UPROPERTY(meta = (BindWidget))
	class UOverlay* Overlay_GameOver;

	UPROPERTY(meta = (BindWidget))
	class UOverlay* Overlay_GameClear;

	UPROPERTY(meta = (BindWidget))
	class UCanvasPanel* CanvasPanel_Reward;

	UPROPERTY(meta = (BindWidget))
	class UTextBlock* Text_Kill;

	UPROPERTY(meta = (BindWidget))
	class UTextBlock* Text_Score;

	UPROPERTY(meta = (BindWidget))
	class UTextBlock* Text_Exp;

	UPROPERTY(meta = (BindWidget))
	class UTextBlock* Text_Silver;

	UPROPERTY(meta = (BindWidget))
	class UButton* Button_Exit;

	UPROPERTY(meta = (BindWidget))
	class UGridPanel* GridPanel_ItemList;

	UPROPERTY(meta = (BindWidgetAnim), meta = (AllowPrivateAccess = true))
	class UWidgetAnimation* GameOverAnimation;

	UPROPERTY(meta = (BindWidgetAnim), meta = (AllowPrivateAccess = true))
	class UWidgetAnimation* GameClearAnimation;

public :
	UDungeonResultWnd(const FObjectInitializer& ObjIntializer);

protected :
	virtual void NativeConstruct() override;

public :
	void DungeonResultAnimation(EClearType clearType);

	void InitializeReward(int32 kill, int32 monsterCount, int32 exp, int32 silver, TArray<FItemSlotInfo> dropItems);

private :
	void UpdateDropItems(TArray<FItemSlotInfo> dropItems);

	void PlayerReward(int32 exp, int32 silver, TArray<FItemSlotInfo> dropItems);

private :
	UFUNCTION()
	void OnExitClicked();
};
