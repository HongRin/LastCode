#pragma once

#include "CoreMinimal.h"
#include "ItemType.generated.h"

// 아이템 타입을 나타낼 때 사용되는 열거 형식입니다.
UENUM(BlueprintType)
enum class EItemType : uint8
{
	EtCetera		UMETA(DisplayName = EtCeteraItem),
	Consumption		UMETA(DisplayName = ConsumptionItem),
	Equipment		UMETA(DisplayName = EquipmentItem)
};

