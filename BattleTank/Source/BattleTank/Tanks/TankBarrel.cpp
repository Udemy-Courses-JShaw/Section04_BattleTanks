// Copyright MetalMuffin Entertainment 2018

#include "Tanks/TankBarrel.h"
#include "Engine/World.h"


void UTankBarrel::Elevate(float RelativeSpeedIn)
{
	float RelativeSpeed = FMath::Clamp<float>(RelativeSpeedIn, -1, +1);
	float ElevationChange = RelativeSpeed * MaxDegreesPerSecond * GetWorld()->DeltaTimeSeconds;
	float RawNewElevation = GetRelativeRotation().Pitch + ElevationChange;
	float Elevation = FMath::Clamp<float>(RawNewElevation, MinElevationDegrees, MaxElevationDegrees) + ElevationChange;

	SetRelativeRotation(FRotator(Elevation, 0, 0));
}


