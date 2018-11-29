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
	FVector TankForwardDirection = GetOwner()->GetActorForwardVector().GetSafeNormal();
	FVector AIForwardIntention = MoveVelocity.GetSafeNormal();

	float MoveForwardThrow = FVector::DotProduct(TankForwardDirection, AIForwardIntention);
	FVector MoveCrossProduct = FVector::CrossProduct(TankForwardDirection , AIForwardIntention);
	float TurnThrow = MoveCrossProduct.Z;
	
	IntendMoveForward(MoveForwardThrow);
	IntendRotateClockwise(TurnThrow);
}

void UTankMovementComponent::IntendRotateClockwise(float Throw)
{
	if (!LeftTrack || !RightTrack) { return; }
	LeftTrack->SetThrottle(Throw);
	RightTrack->SetThrottle(-Throw);
}