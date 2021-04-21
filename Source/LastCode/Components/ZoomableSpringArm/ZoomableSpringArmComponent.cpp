#include "ZoomableSpringArmComponent.h"

UZoomableSpringArmComponent::UZoomableSpringArmComponent()
{
	// �ش� ������Ʈ���� Tick �̺�Ʈ�� Ȱ��ȭ ��ŵ�ϴ�.
	PrimaryComponentTick.bCanEverTick = true;

	// ĳ���Ϳ� ī�޶��� �Ÿ��� �����մϴ�.
	TargetArmLength = TargetLength =
		((CAMERA_ZOOM_MAX + CAMERA_ZOOM_MIN) * 0.5f);

	// �� ��Ʈ�� ȸ���� ����ϵ��� �մϴ�.
	bUsePawnControlRotation = true;

	// �� ���ǵ� ����
	ZoomSpeed = 20.0f;
}


void UZoomableSpringArmComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	UpdateLength(DeltaTime);
}

void UZoomableSpringArmComponent::UpdateLength(float dt)
{
	TargetArmLength = FMath::Lerp(
		TargetArmLength,
		TargetLength,
		10.0f * dt);
}

void UZoomableSpringArmComponent::ZoomCamera(float axis)
{
	TargetLength = FMath::Clamp(
		TargetLength + (axis * ZoomSpeed),
		CAMERA_ZOOM_MIN,
		CAMERA_ZOOM_MAX);
}
