#pragma once
#include "LastCode.h"
#include "Blueprint/UserWidget.h"

#include "Enums/SlotType.h"
#include "Enums/SkillType.h"
#include "Widgets/ClosableWnd/DraggableWnd/DraggableWidget/BaseSlot/SlotDragDropOperation.h"

#include "BaseSlot.generated.h"

DECLARE_MULTICAST_DELEGATE_OneParam(FSlotMouseEventSignature, ESlotType)
DECLARE_MULTICAST_DELEGATE_OneParam(FSlotDragEventSignature, class USlotDragDropOperation*)

UCLASS()
class LASTCODE_API UBaseSlot : public UUserWidget
{
	GENERATED_BODY()

public:
	// ���콺 ���� ��ư Ŭ�� �� ȣ��Ǵ� �븮��
	FSlotMouseEventSignature OnMouseLeftButtonClicked;

	// ���콺 ���� ��ư ���� Ŭ�� �� ȣ��Ǵ� �븮��
	FSlotMouseEventSignature OnMouseLeftButtonDBClicked;

	// ���콺 ������ ��ư Ŭ�� �� ȣ��Ǵ� �븮��
	FSlotMouseEventSignature OnMouseRightButtonClicked;

	// ���� �巡�� ���� �� ȣ��Ǵ� �븮��
	FSlotDragEventSignature OnSlotDragStarted;

	// �巡�� ��� �� ȣ��Ǵ� �븮��
	FSlotDragEventSignature OnSlotDragFinished;
	FSlotDragEventSignature OnSlotDragFinishedOneShot;

	// �巡�� ��� �� ȣ��Ǵ� �븮��
	FSlotDragEventSignature OnSlotDragCancelled;
	FSlotDragEventSignature OnSlotDragCancelledOneShot;

private:
	// ���� �巡�� �� �����Ǵ� ���� �������Ʈ UClass
	TSubclassOf<UUserWidget> BP_SlotDragImage;

	TSubclassOf<class USkillDetailWnd> BP_SkillDetailWnd;

	class USkillDetailWnd* SkillDetailWnd;


	TSubclassOf<class UItemDetailWnd> BP_ItemDetailWnd;

	class UItemDetailWnd* ItemDetailWnd;

private :
	UPROPERTY()
		bool bDroppable;

private:
	UPROPERTY(meta = (BindWidget))
	class UImage* Image_SlotBackground;

	UPROPERTY(meta = (BindWidget))
	class UImage* Image_Slot;

	UPROPERTY(meta = (BindWidget))
	class UCanvasPanel* CanvasPanel_Detail;

protected:
	UPROPERTY()
	ESlotType SlotType;

	// ������ ���԰� �Բ� ���Ǵ� �ڵ带 ��Ÿ���ϴ�.
	///  ex) ������ �ڵ�, ��ų �ڵ�
	FName InCode;

	UPROPERTY()
	ESkillType SkillType;

	class UTexture2D* T_Null;

public:
	UBaseSlot(const FObjectInitializer& ObjectInitializer);

protected:
	// �� ������ ���콺 ��ħ�� ���۵Ǿ��� �� ȣ��Ǵ� �޼���
	virtual void NativeOnMouseEnter(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent) override final;

	// �� ������ ���콺�� ��ħ�� ������ ��� ȣ��Ǵ� �޼���
	virtual void NativeOnMouseLeave(const FPointerEvent& InMouseEvent) override final;

	// �ش� ������ ���콺 Ŭ�� �Է��� ���� ��� ȣ��˴ϴ�.
	virtual FReply NativeOnMouseButtonDown(
		const FGeometry& InGeometry, const FPointerEvent& InMouseEvent) override final;
	/// - FReply : �̺�Ʈ�� ��� ������� ó���Ǿ����� �˸��� ���� ����
	/// - InGeometry : ������ ��ġ, ũ�⸦ ��Ÿ���ϴ�.
	/// - InMouseEvent : ���콺 �Է� �̺�Ʈ�� ����

	// ���콺 Ŭ�� �Է��� ���� ��� ȣ��˴ϴ�.
	virtual FReply NativeOnMouseButtonUp(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent) override final;

	// �� ������ ���� Ŭ���Ǿ��� ��� ȣ��˴ϴ�.
	virtual FReply NativeOnMouseButtonDoubleClick(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent) override final;

	// �ش� ������ �巡�� �̺�Ʈ�� �߻����� ��� ȣ��˴ϴ�.
	virtual void NativeOnDragDetected(
		const FGeometry& InGeometry,
		const FPointerEvent& InMouseEvent,
		UDragDropOperation*& OutOperation) override final;
	/// - OutOperation : ��¿� �Ű� �����̸�, ������ �巡�� �۾� ��ü�� ��ȯ�ؾ� �մϴ�.

	// �巡���� �巡�� ��� �� ȣ��Ǵ� �޼���
	virtual void NativeOnDragCancelled(
		const FDragDropEvent& InDragDropEvent,
		UDragDropOperation* InOperation) override final;

	// �巡�װ� ������ ��� ȣ��Ǵ� �޼���
	virtual bool NativeOnDrop(
		const FGeometry& InGeometry,
		const FDragDropEvent& InDragDropEvent,
		UDragDropOperation* InOperation) override final;

public:
	// ������ �ʱ�ȭ�մϴ�.
	virtual void InitializeSlot(ESlotType slotType, FName inCode, ESkillType skillType);

	void SlotImageEmpty();

private:
	// ���� ����� �⺻ �������� ǥ���մϴ�.
	void ShowSlotNormalState();

	// ���� ����� ���콺 ��ħ ���·� ǥ���մϴ�.
	void ShowSlotHorverState();

	// ���� ����� ���� ���·� ǥ���մϴ�.
	void ShowSlotPressedState();

public:
	// ���� �̹��� ������ �⺻ / �巡�� �������� �����մϴ�.
	void SetSlotColorNormal();
	void SetSlotColorDragging();

protected:
	TTuple<UUserWidget*, class UImage*> CreateSlotDragWidget();
	/// - Ʃ��
	/// - ������ �̸��� ������ �ʰ�, ���� �ʵ带 ���� �� �մ� ����ü�Դϴ�.
	/// - ���� Ʃ���� �������α׷� ��ü���� ����� ������ ������ ���� �ƴ�,
	///   �Ͻ������� ����� ���� ������ ������ ������ �� ����մϴ�.
	/// - �𸮾󿡼� TTuple<Types...> �������� ������ �� ������, MakeTuple() �� ���� �ϳ��� �����͸� ������ �� �ֽ��ϴ�.
	/// - ������ Ʃ���� �ʵ忡�� Get<index>() �� ������ �� �ֽ��ϴ�.


public:
	FORCEINLINE class UImage* GetSlotBackgroundImage() const
	{
		return Image_SlotBackground;
	}

	FORCEINLINE class UImage* GetSlotImage() const
	{
		return Image_Slot;
	}

	FORCEINLINE FName GetInCode() const
	{ return InCode; }

	FORCEINLINE	ESlotType GetSlotType()
	{ return SlotType; }
};
