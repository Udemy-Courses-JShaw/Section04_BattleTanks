// Copyright MetalMuffin Entertainment 2018

#include "AI/TankPlayerController.h" //MUST be first
#include "Tanks/Tank.h"
#include "Tanks/Components/TankAimingComponent.h"
#include "Tanks/TankBarrel.h"
#include "Camera/PlayerCameraManager.h"
#include "Engine/Engine.h"
#include "Engine/World.h"
#include "GameFramework/PlayerController.h"
#include "GameFramework/Actor.h"


void ATankPlayerController::BeginPlay()
{
	Super::BeginPlay();

	if (!GetPawn()) { return; }
	UTankAimingComponent* AimingComponentRef = GetPawn()->FindComponentByClass<UTankAimingComponent>();
	if (!ensure(AimingComponentRef)) { return; }
	FoundAimingComponent(AimingComponentRef);
}

void ATankPlayerController::SetPawn(APawn* InPawn)
{
	Super::SetPawn(InPawn);

	if (InPawn)
	{
		auto PossessedTank = Cast<ATank>(InPawn);
		if (!ensure(PossessedTank)) { return; }

		PossessedTank->OnDeath.AddUniqueDynamic(this, &ATankPlayerController::OnPossesedTankDeath);
	}
}

void ATankPlayerController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	AimAtCrosshair();
}

void ATankPlayerController::AimAtCrosshair()
{
	if (!GetPawn()) { return; } //e.g. if not possessing
	UTankAimingComponent* AimingComponentRef = GetPawn()->FindComponentByClass<UTankAimingComponent>();
	if (!ensure(AimingComponentRef)) { return; }

	FVector HitLocation; //OUT parameter
	if (GetSightRayHitLocation(HitLocation))
	{
		AimingComponentRef->AimAt(HitLocation);
	}
}

/* 
** Get World location of linetrace through crosshair, true if hits landscape
** Also calculates the barrel reticle reference
*/
bool ATankPlayerController::GetSightRayHitLocation(FVector& HitLocation) const
{
	//Find Crosshair position in pixel coordinates
	int32 ViewPortSizeX, ViewPortSizeY;
	GetViewportSize(ViewPortSizeX, ViewPortSizeY);

	//Calculation or Barrel Reference reticle (SecondaryCrosshairLocation)
	UTankAimingComponent* AimingComponentRef = GetPawn()->FindComponentByClass<UTankAimingComponent>();
	if (!ensure(AimingComponentRef)) { return 0; }
	FVector2D ScreenCrossHair = FVector2D(ViewPortSizeX * CrossHairXLocation, ViewPortSizeY * CrossHairYLocation);

	FVector FiringLocation = AimingComponentRef->GetBarrelReference()->GetSocketLocation("Projectile");
	FVector EndLocation = FiringLocation + (AimingComponentRef->GetBarrelReference()->GetForwardVector() * 5000.f);
	FVector2D ScreenLocation;
	ProjectWorldLocationToScreen(EndLocation, ScreenLocation);
	float adjustedX = ScreenLocation.X / ViewPortSizeX;
	float adjustedY = ScreenLocation.Y / ViewPortSizeY;

	FVector2D adjustedScreenLocation = FVector2D(adjustedX, adjustedY);
	AimingComponentRef->SecondaryCrosshairLocation = adjustedScreenLocation;

	// "De-project" the screen position of the crosshair to a world direction
	FVector LookDirection;
	if (GetLookDirection(ScreenCrossHair, LookDirection))
	{
		//Linetrace along and look to see what we hit up to max range
		return GetLookVectorHitLocation(LookDirection, HitLocation);
	}
	return false;
}

bool ATankPlayerController::GetLookVectorHitLocation(FVector LookDirection, FVector& HitLocation) const
{
	FHitResult HitResult;
	FVector StartLocation = PlayerCameraManager->GetCameraLocation();
	FVector EndLocation = StartLocation + (LookDirection * LineTraceRange);
	
	//Linetracing for debugging aiming issues: Leaving here for future reference
	
	//const FName TraceTag("TraceTag");
	//GetWorld()->DebugDrawTraceTag = TraceTag;
	//FCollisionQueryParams CollisionParams;
	//CollisionParams.TraceTag = TraceTag;
	
	if (GetWorld()->LineTraceSingleByChannel(
				HitResult,
				StartLocation,
				EndLocation,
				ECollisionChannel::ECC_Camera
				//,CollisionParams
				)
		)
	{
		HitLocation = HitResult.Location;
		return true;
	}
	HitLocation = FVector(0);
	return false; //If Linetrace fails
}

bool ATankPlayerController::GetLookDirection(FVector2D ScreenCrossHair, FVector& LookDirection) const
{
	FVector WorldLocation; //Discarded
	
	return DeprojectScreenPositionToWorld(
		ScreenCrossHair.X,
		ScreenCrossHair.Y,
		WorldLocation,
		LookDirection
	);
}

void ATankPlayerController::OnPossesedTankDeath()
{
	StartSpectatingOnly();
}


