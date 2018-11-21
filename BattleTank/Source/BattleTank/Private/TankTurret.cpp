// Copyright MetalMuffing Entertainment 2018

#include "Public/TankTurret.h"
#include "Engine/World.h"

//Rotation of Turret
void UTankTurret::Rotate(float RelativeRotaitonIn)
{
	float RelativeSpeed = FMath::Clamp<float>(RelativeRotaitonIn, -20, 20);
	auto RotationChange = RelativeSpeed * MaxDegreesPerSecond * GetWorld()->DeltaTimeSeconds;
	auto Rotation = RelativeRotation.Yaw + RotationChange;

	SetRelativeRotation(FRotator(0, Rotation, 0));
}
