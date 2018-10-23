// Fill out your copyright notice in the Description page of Project Settings.

#include "TankPlayerController.h"
#include "Camera/PlayerCameraManager.h"
#include "Engine/Engine.h"
#include "GameFramework/PlayerController.h"
#include "GameFramework/Actor.h"


void ATankPlayerController::BeginPlay()
{
	Super::BeginPlay();

	auto ControlledTank = GetControlledPlayerTank();
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

ATank* ATankPlayerController::GetControlledPlayerTank() const
{
	return Cast<ATank>(GetPawn());
}

void ATankPlayerController::AimAtCrosshair()
{
	if (!GetControlledPlayerTank()){ return; }
	
	FVector HitLocation; //OUT parameter
	if (GetSightRayHitLocation(HitLocation))
	{
		UE_LOG(LogTemp, Warning, TEXT("HitLocation: %s: "), *HitLocation.ToString())
		//TODO tell controlled tank to aim at this point
	}
	//TODO: Complete AimAtCrosshair
}

// Get World location of linetrace through crosshair, true if hits landscape
bool ATankPlayerController::GetSightRayHitLocation(FVector& HitLocation) const
{
	//TODO : Complete GetSightRayHitLocation()
	//Setup Parmaeters
	FCollisionQueryParams HitParameters;
	FHitResult HitResult = {};
	//Raycast from camera out to range
	/*GetWorld()->GetFirstPlayerController()->ActorLineTraceSingle(
		HitResult,
		GetWorld()->GetFirstPlayerController()->PlayerCameraManager->GetCameraLocation,
		HitLocation,
		ECC_Visibility,
		HitParameters
	);*/
	HitLocation = FVector(1.);
	return true;
}
