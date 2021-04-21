#include "TipWnd.h"
#include "Components/TextBlock.h"

void UTipWnd::NativeConstruct()
{
	Super::NativeConstruct();
}

void UTipWnd::SetExplanation(FText explanation)
{
	Text_Explanation->SetText(explanation);
}
