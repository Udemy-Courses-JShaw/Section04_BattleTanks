// Copyright MetalMuffin Entertainment 2018

#include "TankTrack.h"

UTankTrack::UTankTrack()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}

void UTankTrack::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction * ThisTickfunction)
{
	//Super::TickComponent();
	
	float SlippageRight = FVector::DotProduct(GetRightVector(), GetComponentVelocity());
	
	// Work-out required acceleration this frame to correct
	FVector CorrectionAcceleration = -(SlippageRight / DeltaTime * GetRightVector());
	
	// calculate and apply sideways force (F = M A)
	auto TankRoot = Cast<UStaticMeshComponent>(GetOwner()->GetRootComponent());
	auto CorrectionForce = (TankRoot->GetMass() * CorrectionAcceleration) / 2; //Divide by 2 because 2 tracks
	TankRoot->AddForce(CorrectionForce);
}

void UTankTrack::SetThrottle(float Throttle)
{
	//TODO Clamp the Throttle Values

	FVector ForceApplied = GetForwardVector() * Throttle * TrackMaxDriveForce;
	FVector ForceLocation = GetComponentLocation();
	UPrimitiveComponent* TankRoot = Cast<UPrimitiveComponent>(GetOwner()->GetRootComponent());
	TankRoot->AddForceAtLocation(ForceApplied, ForceLocation);
}
