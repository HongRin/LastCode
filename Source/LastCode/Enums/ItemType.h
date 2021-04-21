#pragma once

#include "CoreMinimal.h"
#include "ItemType.generated.h"

// ������ Ÿ���� ��Ÿ�� �� ���Ǵ� ���� �����Դϴ�.
UENUM(BlueprintType)
enum class EItemType : uint8
{
	EtCetera		UMETA(DisplayName = EtCeteraItem),
	Consumption		UMETA(DisplayName = ConsumptionItem),
	Equipment		UMETA(DisplayName = EquipmentItem)
};

