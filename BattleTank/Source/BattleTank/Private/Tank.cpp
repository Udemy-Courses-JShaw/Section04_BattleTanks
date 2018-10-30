// Fill out your copyright notice in the Description page of Project Settings.

#include "Tank.h"
#include "Components/StaticMeshComponent.h"
#include "Components/SceneComponent.h"
#include "Public/TankBarrel.h"
#include "Public/TankTurret.h"
#include "Public/TankAIController.h"
#include "Public/TankAimingComponent.h"

void ATank::SetBarrelReference(UTankBarrel* BarrelToSet)
{
	TankAimingComponent->SetBarrelReference(BarrelToSet);
}

void ATank::SetTurretReference(UTankTurret * TurretToSet)
{
	TankAimingComponent->SetTurretReference(TurretToSet);
}

// Sets default values
ATank::ATank()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	//nullPtr Protection not needed at contruction
	TankAimingComponent = CreateDefaultSubobject<UTankAimingComponent>(FName("Aiming Component"));
	
	// Attach The barrel to circumvent the v4.20 error - Barrel Mesh dissapears after complation
	//TankBarrelComponent->CreateDefaultSubobject<UTankBarrel>(FName("BarrelMesh"));
	/*
	USceneComponent Parent = ;
	USceneComponent Socket = ->GetSocketLocation(FName("Barrel"));
	BarrelMesh->CreateDefaultSubobject<UTankBarrel>(FName("BarrelMesh"));
	BarrelMesh->SetupAttachment(Parent, Socket);
	///tank_fbx_Barrel
	BarrelMesh = ;
	*/
}

// Called when the game starts or when spawned
void ATank::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called to bind functionality to input
void ATank::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void ATank::AimAt(FVector HitLocation)
{
	TankAimingComponent->AimAt(HitLocation, LaunchSpeed);
}