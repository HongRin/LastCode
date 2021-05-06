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
	// 아이템 코드
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Basic")
	FName ItemCode;

	// 아이템 타입
	// 기타, 소비, 장비
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Basic")
	EItemType ItemType;

	// 아이템 이름
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Basic")
	FText ItemName;

	// 아이템 설명
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Basic")
	FText ItemDescription;

	// 아이템 이미지 경로
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Basic")
	FSoftObjectPath ItemImagePath;

	// 슬롯 최대 개수
	/// - 슬롯에 담을 수 있는 최대 개수를 나타냅니다.
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Basic")
	int32 MaxSlotCount;

	// 아이템 판매 가격
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
