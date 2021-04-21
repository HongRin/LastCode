#include "PreviewCharacter.h"
#include "Engine/DataTable.h"

#include "AnimInstance/PlayerCharacter/Preview/PreviewCharacterAnimInstance.h"

#include "Components/ZoomableSpringArm/ZoomableSpringArmComponent.h"

#include "Single/GameInstance/LCGameInstance.h"
#include "Single/PlayerManager/PlayerManager.h"


APreviewCharacter::APreviewCharacter()
{
	static ConstructorHelpers::FObjectFinder<UDataTable> DT_INIT_PLAYER_INFO(
		TEXT("DataTable'/Game/Resources/DataTable/DT_InitializePlayerInfo.DT_InitializePlayerInfo'"));
	if (DT_INIT_PLAYER_INFO.Succeeded()) DT_InitPlayerInfo = DT_INIT_PLAYER_INFO.Object;
	else UE_LOG(LogTemp, Error, TEXT("APreviewCharacter.cpp::%d::LINE:: DT_INIT_PLAYER_INFO is not loaded !"));

	// 컨트롤러 Yaw 회전을 사용하지 않도록 설정합니다.
	bUseControllerRotationYaw = false;

	InitializeComponent();
}

void APreviewCharacter::BeginPlay()
{
	Super::BeginPlay();

	PlayerInfo = GetManager(UPlayerManager)->GetPlayerInfo();
	GameInst = Cast<ULCGameInstance>(GetWorld()->GetGameInstance());

	GetCharacterMovement()->MaxWalkSpeed = 0.0f;
}

void APreviewCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis(TEXT("MouseWheel"), SpringArm,
		&UZoomableSpringArmComponent::ZoomCamera);
}

void APreviewCharacter::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);
}

void APreviewCharacter::InitializeAsset()
{
	FString contextString;
	struct FInitializePlayerInfo* initPlayerInfo = DT_InitPlayerInfo->FindRow<FInitializePlayerInfo>(PlayerInfo->CharacterCode,
		contextString);

	InitPlayerInfo = initPlayerInfo;
	PlayerInfo->StaminaType = initPlayerInfo->StaminaType;

	USkeletalMesh* bodySkeletalMesh = Cast<USkeletalMesh>(GetManager(FStreamableManager)->LoadSynchronous(initPlayerInfo->SkeletalMeshBodyPath));

	if (IsValid(bodySkeletalMesh))
	{
		GetMesh()->SetSkeletalMesh(bodySkeletalMesh);
		GetMesh()->SetRelativeLocationAndRotation(FVector(0.0f, 0.0f, -85.0f), FRotator(0.0f, 90.0f, 0.0f));
	}
	else UE_LOG(LogTemp, Error, TEXT("APreviewCharacter.cpp::%d::LINE:: bodySkeletalMesh is not loaded !"));

	UStaticMesh* rWeaponStaticMesh = Cast<UStaticMesh>(GetManager(FStreamableManager)->LoadSynchronous(initPlayerInfo->StaticMeshRWeaponPath));
	if (IsValid(rWeaponStaticMesh)) RWeaponMesh->SetStaticMesh(rWeaponStaticMesh);
	else UE_LOG(LogTemp, Error, TEXT("APreviewCharacter.cpp::%d::LINE:: weaponStaticMesh is not loaded !"));

	UStaticMesh* lWeaponStaticMesh = Cast<UStaticMesh>(GetManager(FStreamableManager)->LoadSynchronous(initPlayerInfo->StaticMeshLWeaponPath));
	if (IsValid(lWeaponStaticMesh)) LWeaponMesh->SetStaticMesh(lWeaponStaticMesh);
	else UE_LOG(LogTemp, Error, TEXT("APreviewCharacter.cpp::%d::LINE:: weaponStaticMesh is not loaded !"));

	USkeletalMesh* maskSkeletalMesh = Cast<USkeletalMesh>(GetManager(FStreamableManager)->LoadSynchronous(initPlayerInfo->SkeletalMeshMaskPath));
	if (IsValid(maskSkeletalMesh)) 	MaskMesh->SetSkeletalMesh(maskSkeletalMesh);
	else UE_LOG(LogTemp, Error, TEXT("APreviewCharacter.cpp::%d::LINE:: maskSkeletalMesh is not loaded !"));

	if(IsValid(initPlayerInfo->PreviewAnimInstancePath))
	GetMesh()->SetAnimClass(initPlayerInfo->PreviewAnimInstancePath);
	else UE_LOG(LogTemp, Error, TEXT("APreviewCharacter.cpp::%d::LINE:: initPlayerInfo->PreviewAnimInstancePath is not loaded !"));
}

void APreviewCharacter::InitializeComponent()
{
	SpringArm = CreateDefaultSubobject<UZoomableSpringArmComponent>(TEXT("SPRING_ARM"));
	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("CAMERA"));
	SpringArm->SetupAttachment(GetRootComponent());
	Camera->SetupAttachment(SpringArm);

	RWeaponMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("SM_RWEAPON"));
	RWeaponMesh->SetupAttachment(GetMesh(), TEXT("RWeaponSocket"));
	LWeaponMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("SM_LWEAPON"));
	LWeaponMesh->SetupAttachment(GetMesh(), TEXT("LWeaponSocket"));
	MaskMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("SK_MASK"));
	MaskMesh->SetupAttachment(GetMesh(), TEXT("MaskSocket"));
}

#pragma region Override...
float APreviewCharacter::GetMaxHp() { return 0.0f; }

float APreviewCharacter::GetHp() { return 0.0f; }

void APreviewCharacter::SetHp(float value) {}
#pragma endregion