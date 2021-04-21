#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "TipWnd.generated.h"

UCLASS()
class LASTCODE_API UTipWnd : public UUserWidget
{
	GENERATED_BODY()
	
private :
	UPROPERTY(meta = (BindWidget))
	class UTextBlock* Text_Explanation;

protected :
	virtual void NativeConstruct() override;

public :
	void SetExplanation(FText explanation);
};
