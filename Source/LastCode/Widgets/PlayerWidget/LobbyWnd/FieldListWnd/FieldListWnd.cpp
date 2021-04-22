#include "FieldListWnd.h"

#include "Engine/DataTable.h"
#include "Structures/FieldInfo/FieldInfo.h"

#include "Widgets/PlayerWidget/LobbyWnd/FieldListWnd/FieldRow/FieldRow.h"

#include "Components/CanvasPanel.h"
#include "Components/ScrollBox.h"
#include "Components/Button.h"

UFieldListWnd::UFieldListWnd(const FObjectInitializer& ObjInitializer) :
	Super(ObjInitializer)
{
	static ConstructorHelpers::FObjectFinder<UDataTable> DT_FIELD_INFO(
		TEXT("DataTable'/Game/Resources/DataTable/DT_FieldInfo.DT_FieldInfo'"));
	if (DT_FIELD_INFO.Succeeded()) DT_FieldInfo = DT_FIELD_INFO.Object;
	else UE_LOG(LogTemp, Error, TEXT("UFieldListWnd.cpp::%d::LINE:: DT_FIELD_INFO is not loaded !"), __LINE__);

	static ConstructorHelpers::FClassFinder<UFieldRow> BP_FIELD_ROW(
		TEXT("WidgetBlueprint'/Game/Resources/Blueprints/Widgets/PlayerWidget/FieldList/BP_FieldRow.BP_FieldRow_C'"));
	if (BP_FIELD_ROW.Succeeded()) BP_FieldRow = BP_FIELD_ROW.Class;
	else UE_LOG(LogTemp, Error, TEXT("UFieldListWnd.cpp::%d::LINE:: BP_FIELD_ROW is not loaded !"), __LINE__);
}

void UFieldListWnd::NativeConstruct()
{
	Super::NativeConstruct();

	CanvasPanel_Help->SetVisibility(ESlateVisibility::Hidden);

	Button_Previous->OnClicked.AddDynamic(this, &UFieldListWnd::PreviousButtonClicked);
	Button_Next->OnClicked.AddDynamic(this, &UFieldListWnd::NextButtonClicked);
	Button_Help->OnHovered.AddDynamic(this, &UFieldListWnd::HelpButtonHovered);
	Button_Help->OnUnhovered.AddDynamic(this, &UFieldListWnd::HelpButtonOnUnhovered);

	CurrentOffset = ScrollBox_List->GetScrollOffset();
	NextOffset = 0.0f;

	InitializeFieldListWnd();

}

void UFieldListWnd::NativeTick(const FGeometry& MyGeometry, float inDeltaTime)
{
	Super::NativeTick(MyGeometry, inDeltaTime);

	if (!FMath::IsNearlyEqual(CurrentOffset, NextOffset, 0.99f)) SetScroll(inDeltaTime);
}

void UFieldListWnd::SetScroll(float time)
{
	UE_LOG(LogTemp, Warning, TEXT("SetScroll"));
	ScrollBox_List->SetScrollOffset(FMath::FInterpTo(CurrentOffset, NextOffset, time, 10.0f));
	CurrentOffset = ScrollBox_List->GetScrollOffset();
}

void UFieldListWnd::InitializeFieldListWnd()
{
	FString contextString;
	TArray<FFieldInfo*> fieldInfos;
	DT_FieldInfo->GetAllRows<FFieldInfo>(contextString, fieldInfos);

	for (int i = 0; i < fieldInfos.Num(); ++i)
	{
		UFieldRow* fieldRow = CreateWidget<UFieldRow>(this, BP_FieldRow);
		ScrollBox_List->AddChild(fieldRow);
		fieldRow->UpdateFieldRow(fieldInfos[i]);
	}
}

void UFieldListWnd::PreviousButtonClicked()
{
	NextOffset = CurrentOffset - 352.0f;
	if (NextOffset <= 0.0f) NextOffset = 0.0f;
}

void UFieldListWnd::NextButtonClicked()
{
	NextOffset = CurrentOffset + 352.0f;
	if (NextOffset >= ScrollBox_List->GetScrollOffsetOfEnd()) 
		NextOffset = ScrollBox_List->GetScrollOffsetOfEnd();
}

void UFieldListWnd::HelpButtonHovered()
{
	CanvasPanel_Help->SetVisibility(ESlateVisibility::HitTestInvisible);
}

void UFieldListWnd::HelpButtonOnUnhovered()
{
	CanvasPanel_Help->SetVisibility(ESlateVisibility::Hidden);
}
