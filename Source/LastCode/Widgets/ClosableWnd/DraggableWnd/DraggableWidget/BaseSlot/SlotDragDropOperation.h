#pragma once

#include "CoreMinimal.h"
#include "Blueprint/DragDropOperation.h"
#include "SlotDragDropOperation.generated.h"

UCLASS()
class LASTCODE_API USlotDragDropOperation : public UDragDropOperation
{
	GENERATED_BODY()

public :
	// µå·¡±ëÇÒ ½½·ÔÀ» ³ªÅ¸³À´Ï´Ù.
	class UBaseSlot* DraggingSlot;
};
