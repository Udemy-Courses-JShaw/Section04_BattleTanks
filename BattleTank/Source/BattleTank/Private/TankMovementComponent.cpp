// Copyright MetalMuffing Entertainment 2018

#include "TankMovementComponent.h"
#include "Public/TankTrack.h"

void UTankMovementComponent::Initialize(UTankTrack* LeftTrackToSet, UTankTrack* RightTrackToSet)
{
	LeftTrack = LeftTrackToSet;
	RightTrack = RightTrackToSet;
}

void UTankMovementComponent::IntendMoveForward(float Throw)
{
	if (!LeftTrack || !RightTrack) { return; }
	LeftTrack->SetThrottle(Throw);
	RightTrack->SetThrottle(Throw);
	//TODO Prevent 2x throttle
}

void UTankMovementComponent::RequestDirectMove(const FVector& MoveVelocity, bool bForceMaxSpeed)
{
	auto TankForwardDirection = GetOwner()->GetActorForwardVector().GetSafeNormal();
	auto AIForwardIntention = MoveVelocity.GetSafeNormal();

	auto MoveForwardThrow = FVector::DotProduct(TankForwardDirection, AIForwardIntention);
	auto MoveCrossProduct = FVector::CrossProduct(TankForwardDirection , AIForwardIntention);
	auto TurnThrow = MoveCrossProduct.Z;
	// IntendMoveForward(MoveForwardThrow);
	IntendRotateClockwise(TurnThrow);

	//UE_LOG(LogTemp, Warning, TEXT("MoveVelocity is %s, vectoring to: %s"), *MoveVelocity.ToString(), *TankName)
}

void UTankMovementComponent::IntendRotateClockwise(float Throw)
{
	if (!LeftTrack || !RightTrack) { return; }
	LeftTrack->SetThrottle(Throw);
	RightTrack->SetThrottle(-Throw);
}