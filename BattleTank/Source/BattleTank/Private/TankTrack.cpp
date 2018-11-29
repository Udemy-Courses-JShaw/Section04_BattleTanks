// Copyright MetalMuffing Entertainment 2018

#include "TankTrack.h"

void UTankTrack::SetThrottle(float Throttle)
{
	//TODO Clamp the Throttle Values

	FVector ForceApplied = GetForwardVector() * Throttle * TrackMaxDriveForce;
	FVector ForceLocation = GetComponentLocation();
	UPrimitiveComponent* TankRoot = Cast<UPrimitiveComponent>(GetOwner()->GetRootComponent());
	TankRoot->AddForceAtLocation(ForceApplied, ForceLocation);
}
