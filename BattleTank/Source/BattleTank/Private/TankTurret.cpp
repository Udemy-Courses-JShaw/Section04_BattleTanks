// Fill out your copyright notice in the Description page of Project Settings.

#include "Public\TankTurret.h"
#include "Engine\World.h"


// Sets default values for this component's properties
UTankTurret::UTankTurret()
{
	// Attach The barrel to circumvent the v4.20 error - Barrel Mesh dissapears after complation
	
	/*
	USceneComponent Parent = ;
	USceneComponent Socket = ->GetSocketLocation(FName("Barrel"));
	BarrelMesh->CreateDefaultSubobject<UTankBarrel>(FName("BarrelMesh"));
	BarrelMesh->SetupAttachment(Parent, Socket);
	///tank_fbx_Barrel
	BarrelMesh = ;
	*/
}

// Called when the game starts
void UTankTurret::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}

//Rotation of Turret
void UTankTurret::Rotate(float RelativeRotaitonIn)
{
	float RelativeSpeed = FMath::Clamp<float>(RelativeRotaitonIn, -20, 20);
	auto RotationChange = RelativeSpeed * MaxDegreesPerSecond * GetWorld()->DeltaTimeSeconds;
	auto NewRoatation = RelativeRotation.Yaw + RotationChange;
	auto Roation = NewRoatation + RotationChange;

	SetRelativeRotation(FRotator(0, Roation, 0));
}
