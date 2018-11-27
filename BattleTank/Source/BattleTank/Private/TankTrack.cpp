// Copyright MetalMuffing Entertainment 2018

#include "TankTrack.h"

void UTankTrack::SetThrottle(float Throttle)
{
	//TODO Clamp the Throttle Values

	auto ForceApplied = GetForwardVector() * Throttle * TrackMaxDriveForce;
	auto ForceLocation = GetComponentLocation();
	auto TankRoot = Cast<UPrimitiveComponent>(GetOwner()->GetRootComponent());
	TankRoot->AddForceAtLocation(ForceApplied, ForceLocation);
}
