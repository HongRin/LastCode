#pragma once

#include "LastCode.h"
#include "Widgets/ClosableWnd/ClosableWnd.h"
#include "SkillStateWnd.generated.h"

UCLASS()
class LASTCODE_API USkillStateWnd : public UClosableWnd
{
	GENERATED_BODY()
	
private :
	TSubclassOf<class USkillStateRow> BP_SkillStateRow;

private :
	TArray<FSkillInfo> ActiveSkillInfo;

private :
	UPROPERTY(meta = (BindWidget))
	class UScrollBox* ScrollBox_List;

	UPROPERTY(meta = (BindWidget))
	class UTextBlock* Text_SkillPoint;

public :
	USkillStateWnd();

protected :
	void NativeConstruct() override;

private :
	void UpdateSkillStateWnd();

public :
	void UpdateSkillPointText();
};
