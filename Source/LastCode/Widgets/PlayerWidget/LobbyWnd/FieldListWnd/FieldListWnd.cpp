#include "FieldListWnd.h"

#include "Components/ScrollBox.h"
#include "Components/Button.h"

UFieldListWnd::UFieldListWnd(const FObjectInitializer& ObjInitializer) :
	Super(ObjInitializer)
{

}

void UFieldListWnd::NativeConstruct()
{
	Super::NativeConstruct();

	Button_Previous->OnClicked.AddDynamic(this, &UFieldListWnd::PreviousButtonClicked);
	Button_Next->OnClicked.AddDynamic(this, &UFieldListWnd::NextButtonClicked);

	CurrentOffset = ScrollBox_List->GetScrollOffset();
	NextOffset = 0.0f;

}

void UFieldListWnd::NativeTick(const FGeometry& MyGeometry, float inDeltaTime)
{
	Super::NativeTick(MyGeometry, inDeltaTime);

	if (bScrollable) SetScroll(inDeltaTime);
}

void UFieldListWnd::SetScroll(float time)
{
	UE_LOG(LogTemp, Warning, TEXT("SetScroll"));
	ScrollBox_List->SetScrollOffset(FMath::FInterpTo(CurrentOffset, NextOffset, time, 10.0f));
	CurrentOffset = ScrollBox_List->GetScrollOffset();
	UE_LOG(LogTemp, Warning, TEXT("%.5f"), CurrentOffset);
	bScrollable = bNextButton ? (CurrentOffset < NextOffset) : (CurrentOffset > NextOffset);
	if(!bScrollable) UE_LOG(LogTemp, Warning, TEXT("SetScrollFin"));
}

void UFieldListWnd::PreviousButtonClicked()
{
	NextOffset = CurrentOffset - 352.0f;
	if (NextOffset <= 0.0f) NextOffset = 0.0f;
	bScrollable = true;
	bNextButton = false;
}

void UFieldListWnd::NextButtonClicked()
{
	NextOffset = CurrentOffset + 352.0f;
	if (NextOffset >= ScrollBox_List->GetScrollOffsetOfEnd()) 
		NextOffset = ScrollBox_List->GetScrollOffsetOfEnd();
	bScrollable = true;
	bNextButton = true;
}
