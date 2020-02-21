// Copyright MetalMuffin Entertainment 2018

#include "Public/TankPlayerController.h" //MUST be first
#include "Public/Tank.h"
#include "Public/TankAimingComponent.h"
#include "Public/TankBarrel.h"
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

// Get World location of linetrace through crosshair, true if hits landscape
bool ATankPlayerController::GetSightRayHitLocation(FVector& HitLocation) const
{
	//Find Crosshair position in pixel coordinates
	int32 ViewPortSizeX, ViewPortSizeY;
	GetViewportSize(ViewPortSizeX, ViewPortSizeY);
	FVector2D ScreenCrossHair = FVector2D(ViewPortSizeX * CrossHairXLocation, ViewPortSizeY * CrossHairYLocation);
	
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

	FVector2D ScreenLocation;
	int32 viewSizeX, viewSizeY;
	GetViewportSize(viewSizeX, viewSizeY);

	float adjustedX = ScreenLocation.X / viewSizeX;
	float adjustedY = ScreenLocation.Y / viewSizeY;
	UTankAimingComponent* AimingComponentRef = GetPawn()->FindComponentByClass<UTankAimingComponent>();
	if (!ensure(AimingComponentRef)) { return 0; }

	FVector StartLocation = AimingComponentRef->GetBarrelReference()->GetSocketLocation(FName("Projectile"));
	FVector EndLocation = StartLocation + (AimingComponentRef->GetBarrelReference()->GetForwardVector() * 5000.f);


	ProjectWorldLocationToScreen(EndLocation, ScreenLocation);

	FVector2D adjustedScreenLocation = FVector2D(adjustedX, adjustedY);
	AimingComponentRef->SecondaryCrosshairLocation = adjustedScreenLocation;
	
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
