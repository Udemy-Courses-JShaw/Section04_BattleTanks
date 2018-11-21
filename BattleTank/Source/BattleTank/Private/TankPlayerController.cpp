// Copyright MetalMuffing Entertainment 2018

#include "Public/TankPlayerController.h"
#include "Public/Tank.h"
#include "Camera/PlayerCameraManager.h"
#include "Engine/Engine.h"
#include "Engine/World.h"
#include "GameFramework/PlayerController.h"
#include "GameFramework/Actor.h"


void ATankPlayerController::BeginPlay()
{
	Super::BeginPlay();

	auto ControlledTank = GetControlledTank();
	if (!ControlledTank)
	{
		UE_LOG(LogTemp, Warning, TEXT("PlayerController is not Possessing Tank!!"))
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("PlayerController Possessing %s !!"), *(ControlledTank->GetName()))
	}
}

void ATankPlayerController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	AimAtCrosshair();
}

ATank* ATankPlayerController::GetControlledTank() const
{
	return Cast<ATank>(GetPawn());
}

void ATankPlayerController::AimAtCrosshair()
{
	if (!GetControlledTank()){ return; }
	
	FVector HitLocation; //OUT parameter
	if (GetSightRayHitLocation(HitLocation))
	{
		GetControlledTank()->AimAt(HitLocation);
		//TODO tell controlled tank to aim at this point
	}
	//TODO: Complete AimAtCrosshair
}

void ATankPlayerController::SetupPlayerInputComponent(UInputComponent * InputComponent)
{
	/*InputComponent = GetOwner()->FindComponentByClass<UInputComponent>();
	if (InputComponent)
	{
		InputComponent->BindAction("Fire", IE_Pressed, this, &ATank::Fire);
	}*/
}

// Get World location of linetrace through crosshair, true if hits landscape
bool ATankPlayerController::GetSightRayHitLocation(FVector& HitLocation) const
{
	//TODO : Complete GetSightRayHitLocation()
	int32 ViewPortSizeX, ViewPortSizeY;
	GetViewportSize(ViewPortSizeX, ViewPortSizeY);
	auto ScreenCrossHair = FVector2D(ViewPortSizeX * CrossHairXLocation, ViewPortSizeY * CrossHairYLocation);
	FVector LookDirection;
	if (GetLookDirection(ScreenCrossHair, LookDirection))
	{
		//Linetrace along and look to see what we hit up to max range
		GetLookVectorHitLocation(LookDirection, HitLocation);
		return true;
	}
	return false;
}

bool ATankPlayerController::GetLookVectorHitLocation(FVector LookDirection, FVector& HitLocation) const
{
	FHitResult HitResult;
	auto StartLocation = PlayerCameraManager->GetCameraLocation();
	auto EndLocation = StartLocation + (LookDirection * LineTraceRange);
	
	if (GetWorld()->LineTraceSingleByChannel(
		HitResult,
		StartLocation,
		EndLocation,
		ECollisionChannel::ECC_Visibility)
		)
	{
		HitLocation = HitResult.Location;
		return true;
	}
	//HitLocation = FVector(0);
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
