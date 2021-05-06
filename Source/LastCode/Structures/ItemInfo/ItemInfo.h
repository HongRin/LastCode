#pragma once

#include "CoreMinimal.h"

#include "Engine/DataTable.h"

#include "Enums/ItemType.h"

#include "ItemInfo.generated.h"

USTRUCT()
struct LASTCODE_API FItemInfo : public FTableRowBase
{
	GENERATED_USTRUCT_BODY()

public:
	// ������ �ڵ�
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Basic")
	FName ItemCode;

	// ������ Ÿ��
	// ��Ÿ, �Һ�, ���
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Basic")
	EItemType ItemType;

	// ������ �̸�
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Basic")
	FText ItemName;

	// ������ ����
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Basic")
	FText ItemDescription;

	// ������ �̹��� ���
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Basic")
	FSoftObjectPath ItemImagePath;

	// ���� �ִ� ����
	/// - ���Կ� ���� �� �ִ� �ִ� ������ ��Ÿ���ϴ�.
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Basic")
	int32 MaxSlotCount;

	// ������ �Ǹ� ����
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Basic")
	int32 Price;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Basic")
	bool bSaleItem;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Basic")
	int32 ActivationCharacterLevel;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Basic")
	float DropPercent;
			
public:
	FORCEINLINE bool IsEmpty() const
	{
		return ItemCode.IsNone();
	}

	FORCEINLINE bool operator==(FItemInfo& itemInfo)
	{
		return (this->ItemCode == itemInfo.ItemCode);
	}

	FORCEINLINE bool operator!=(FItemInfo& itemInfo)
	{
		return (this->ItemCode != itemInfo.ItemCode);
	}

};
