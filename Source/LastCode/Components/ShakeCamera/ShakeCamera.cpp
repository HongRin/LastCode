#include "ShakeCamera.h"

UShakeCamera::UShakeCamera()
{
    OscillationDuration = 0.25f;
    OscillationBlendInTime = 0.05f;
    OscillationBlendOutTime = 0.05f;

    RotOscillation.Pitch.Amplitude = FMath::RandRange(0.4f, 0.6f);
    RotOscillation.Pitch.Frequency = FMath::RandRange(50.0f, 60.0f);

    RotOscillation.Yaw.Amplitude = FMath::RandRange(0.4f, 0.6f);
    RotOscillation.Yaw.Frequency = FMath::RandRange(50.0f, 60.0f);
}