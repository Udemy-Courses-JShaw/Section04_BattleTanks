// Copyright MetalMuffin Entertainment 2018

#include "Public/TankTurret.h"
#include "Engine/World.h"

//Rotation of Turret
void UTankTurret::Rotate(float RelativeRotaitonIn)
{
	float RelativeSpeed = FMath::Clamp<float>(RelativeRotaitonIn, -20, 20);
	float RotationChange = RelativeSpeed * MaxDegreesPerSecond * GetWorld()->DeltaTimeSeconds;
	float Rotation = RelativeRotation.Yaw + RotationChange;

	SetRelativeRotation(FRotator(0, Rotation, 0));
}
