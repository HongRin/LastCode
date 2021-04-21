#pragma once

#include "LastCode.h"
#include "Actors/Characters/BaseCharacter.h"

#include "Structures/PlayerInfo/PlayerInfo.h"
#include "Structures/PlayerInfo/InitializePlayerInfo.h"

#include "PreviewCharacter.generated.h"

UCLASS()
class LASTCODE_API APreviewCharacter : public ABaseCharacter
{
	GENERATED_BODY()
	
private :
	class UDataTable* DT_InitPlayerInfo;

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Basic", meta = (AllowPrivateAccess = "true"))
	class UZoomableSpringArmComponent* SpringArm;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Basic", meta = (AllowPrivateAccess = "true"))
	class UCameraComponent* Camera;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "StaticMesh", meta = (AllowPrivateAccess = "true"))
	class UStaticMeshComponent* RWeaponMesh;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "StaticMesh", meta = (AllowPrivateAccess = "true"))
	class UStaticMeshComponent* LWeaponMesh;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "SkeletalMesh", meta = (AllowPrivateAccess = "true"))
	class USkeletalMeshComponent* MaskMesh;

	FInitializePlayerInfo* InitPlayerInfo;

private :
	FPlayerInfo* PlayerInfo;
	class ULCGameInstance* GameInst;

public:
	APreviewCharacter();

protected:
	virtual void BeginPlay() override;

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	virtual void PossessedBy(AController* NewController) override;

public :
	void InitializeAsset();

protected :
	virtual void InitializeComponent();

public:
	virtual float GetMaxHp() override;
	virtual float GetHp() override;
	virtual void SetHp(float value) override;

};
