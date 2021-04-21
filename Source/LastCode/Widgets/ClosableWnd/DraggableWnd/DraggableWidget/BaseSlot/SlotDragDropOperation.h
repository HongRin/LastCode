#pragma once

#include "CoreMinimal.h"
#include "Blueprint/DragDropOperation.h"
#include "SlotDragDropOperation.generated.h"

UCLASS()
class LASTCODE_API USlotDragDropOperation : public UDragDropOperation
{
	GENERATED_BODY()

public :
	// �巡���� ������ ��Ÿ���ϴ�.
	class UBaseSlot* DraggingSlot;
};
