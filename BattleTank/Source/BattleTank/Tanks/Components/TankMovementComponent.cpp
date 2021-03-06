// Copyright MetalMuffin Entertainment 2018

#include "TankMovementComponent.h"
#include "Tanks/TankTrack.h"

void UTankMovementComponent::Initialize(UTankTrack* LeftTrackToSet, UTankTrack* RightTrackToSet)
{
	LeftTrack = LeftTrackToSet;
	RightTrack = RightTrackToSet;
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

void UTankMovementComponent::IntendMoveForward(float Throw)
{
	if (!ensure(LeftTrack && RightTrack)) { return; }
	LeftTrack->SetThrottle(Throw);
	RightTrack->SetThrottle(Throw);
}

void UTankMovementComponent::IntendRotateClockwise(float Throw)
{
	if (!ensure(LeftTrack && RightTrack)) { return; }
	LeftTrack->SetThrottle(Throw);
	RightTrack->SetThrottle(-Throw);
}