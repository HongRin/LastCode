#include "PlayableCharacter.h"

#include "Actors/Controllers/PlayerController/PlayableController/PlayableController.h"

#include "AnimInstance/PlayerCharacter/PlayableCharacterAnimInstance.h"

#include "Components/ZoomableSpringArm/ZoomableSpringArmComponent.h"
#include "Components/SkillController/SkillControllerComponent.h"

#include "Single/GameInstance/LCGameInstance.h"
#include "Single/PlayerManager/PlayerManager.h"

#include "GameFramework/PlayerInput.h"


APlayableCharacter::APlayableCharacter()
{
	PrimaryActorTick.bCanEverTick = true;

	// 컨트롤러 Yaw 회전을 사용하지 않도록 설정합니다.
	bUseControllerRotationYaw = false;

	SetGenericTeamId(TEAM_PLAYER);

	// 이동 방향으로 회전합니다.
	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 720.0f, 0.0f);

	// 점프 초기 가속력 설정합니다.
	GetCharacterMovement()->JumpZVelocity = 800.0f;

	// 캐릭터가 받는 중력 설정합니다.
	GetCharacterMovement()->GravityScale = 2.5f;

	// 공중에서 캐릭터를 80% 제어 가능하도록 설정합니다.
	GetCharacterMovement()->AirControl = 0.8f;

	// 컴포넌트를 초기화합니다.
	InitializeComponent();

	bIsMoveable = true;

}

void APlayableCharacter::BeginPlay()
{
	Super::BeginPlay();

	// 초기 캐릭터 이동속도 설정합니다.
	GetCharacterMovement()->MaxWalkSpeed = WALK_SPEED;

	GetPlayerManager();

	LoadAsset();

	Tags.Add(TEXT("Player"));

	QuickManager = GetManager(UPlayerManager)->GetQuickManager();

}

void APlayableCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void APlayableCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

#pragma region BindAction
	PlayerInputComponent->BindAction(TEXT("Run"), EInputEvent::IE_Pressed, this, &APlayableCharacter::Run);
	PlayerInputComponent->BindAction(TEXT("Run"), EInputEvent::IE_Released, this, &APlayableCharacter::Walk);
	PlayerInputComponent->BindAction(TEXT("Jump"), EInputEvent::IE_Pressed, this, &APlayableCharacter::Jump);
	PlayerInputComponent->BindAction(TEXT("LeftMouseButton"), EInputEvent::IE_Pressed, SkillController, &USkillControllerComponent::LRegularAttack);
	PlayerInputComponent->BindAction(TEXT("RightMouseButton"), EInputEvent::IE_Pressed, SkillController, &USkillControllerComponent::RRegularAttack);
	PlayerInputComponent->BindAction(TEXT("Dash"), EInputEvent::IE_DoubleClick, SkillController,
		&USkillControllerComponent::Dash);
	PlayerInputComponent->BindAction(TEXT("QuickSlotKey"), EInputEvent::IE_Pressed, this,
		&APlayableCharacter::QuickSlotPressed);
	
#pragma endregion


#pragma region BindAxis
	PlayerInputComponent->BindAxis(TEXT("Horizontal"), this,
		&APlayableCharacter::InputHorizontal);
	PlayerInputComponent->BindAxis(TEXT("Vertical"), this,
		&APlayableCharacter::InputVertical);
#pragma endregion
}

#pragma region BaseCharacterOverrides

void APlayableCharacter::OnTakeDamage(AActor* DamagedActor, float Damage, const UDamageType* DamageType, AController* InstigatedBy, AActor* DamageCauser)
{
	Super::OnTakeDamage(
		DamagedActor,
		Damage,
		DamageType,
		InstigatedBy,
		DamageCauser);
	
	if (GetManager(UPlayerManager)->GetPlayerStateManager()->OnUpdateHp.IsBound())
		GetManager(UPlayerManager)->GetPlayerStateManager()->OnUpdateHp.Broadcast();

	PlayAnimMontage(HitAnim);
}

float APlayableCharacter::GetMaxHp()
{
	return GetManager(UPlayerManager)->GetPlayerInfo()->MaxHp;
}

float APlayableCharacter::GetHp()
{
	return GetManager(UPlayerManager)->GetPlayerInfo()->Hp;
}

void APlayableCharacter::SetHp(float value)
{
	GetManager(UPlayerManager)->GetPlayerInfo()->Hp = value;
}
float APlayableCharacter::GetMaxStamina()
{
	return GetManager(UPlayerManager)->GetPlayerInfo()->MaxStamina;
}
float APlayableCharacter::GetStamina()
{
	return GetManager(UPlayerManager)->GetPlayerInfo()->Stamina;
}
void APlayableCharacter::SetStamina(float value)
{
	GetManager(UPlayerManager)->GetPlayerInfo()->Stamina = value;
}
#pragma endregion

void APlayableCharacter::LoadAsset()
{
	InitializeAsset();
	GetMesh()->SetAnimClass(InitPlayerInfo->AnimInstancePath);
	GetMesh()->SetRelativeLocationAndRotation(FVector(0.0f, 0.0f, -85.0f), FRotator(0.0f, -90.0f, 0.0f));
}

void APlayableCharacter::InitializeComponent()
{
	SkillController = CreateDefaultSubobject<USkillControllerComponent>(TEXT("SKILL_CONTROLLER_COM"));
}

void APlayableCharacter::InputHorizontal(float axis)
{
	if (!IsMoveable()) return;

	// 컨트롤러 회전중 Yaw 회전만을 저장합니다.
	FRotator yawRotation(0.0f, GetControlRotation().Yaw, 0.0f);

	// 컨트롤러 기준 오른쪽 방향을 저장합니다.
	FVector rightVector = FRotationMatrix(yawRotation).GetUnitAxis(EAxis::Y);

	AddMovementInput(rightVector, axis);
}

void APlayableCharacter::InputVertical(float axis)
{
	if (!IsMoveable()) return;
	// 컨트롤러 회전중 Yaw 회전만을 저장합니다.
	FRotator yawRotation(0.0f, GetControlRotation().Yaw, 0.0f);

	// 컨트롤러 기준 앞쪽 방향을 저장합니다.
	FVector forwardVector = FRotationMatrix(yawRotation).GetUnitAxis(EAxis::X);

	AddMovementInput(forwardVector, axis);
}

void APlayableCharacter::Jump()
{
	if (!IsMoveable() || SkillController->IsSkillable()) return;
	Super::Jump();
}

void APlayableCharacter::Landed(const FHitResult& Hit)
{
	Super::Landed(Hit);
}

void APlayableCharacter::Run()
{
	if (!IsMoveable()) return;
	GetCharacterMovement()->MaxWalkSpeed = RUN_SPEED;
}

void APlayableCharacter::Walk()
{
	if (!IsMoveable() || SkillController->IsSkillable()) return;
	GetCharacterMovement()->MaxWalkSpeed = WALK_SPEED;
}

void APlayableCharacter::QuickSlotPressed(FKey key)
{
	QuickManager->QuickSlotEventExecution(key);
}

void APlayableCharacter::SetImpluse(FVector direction, float power)
{
	GetCharacterMovement()->AddImpulse(direction * power, true);
}

void APlayableCharacter::LookatControlDirection()
{
	FRotator controlRotation = GetControlRotation();
	controlRotation.Roll = controlRotation.Pitch = 0.0f;

	SetActorRotation(controlRotation);
}

UPlayerManager* APlayableCharacter::GetPlayerManager()
{
	return PlayerManager = (IsValid(PlayerManager)) ? PlayerManager :
		Cast<ULCGameInstance>(GetGameInstance())->
		GetManagerClass<UPlayerManager>();
}

bool APlayableCharacter::IsMoveable()
{
	return bIsMoveable && !IsInAir() && !SkillController->IsAttacking() && !IsDie();
}
