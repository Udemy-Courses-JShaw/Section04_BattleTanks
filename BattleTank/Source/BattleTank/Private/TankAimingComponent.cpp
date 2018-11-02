// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAimingComponent.h"
#include "GameFramework/Actor.h"
#include "Components/StaticMeshComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Public/TankBarrel.h"
#include "Public/TankTurret.h"


// Sets default values for this component's properties
UTankAimingComponent::UTankAimingComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}

void UTankAimingComponent::SetBarrelReference(UTankBarrel* BarrelToSet)
{
	Barrel = BarrelToSet;
}

void UTankAimingComponent::SetTurretReference(UTankTurret * TurretToSet)
{
	Turret = TurretToSet;
}

void UTankAimingComponent::AimAt(FVector HitLocation, float LaunchSpeed)
{
	if (!Barrel) 
	{ 
		UE_LOG(LogTemp, Error, TEXT("No Barrel!!"))
		return; 
	}
	else if (!Turret)
	{
		UE_LOG(LogTemp, Error, TEXT("No Turret!!"))
		return;
	};
	FVector OutLaunchVelocity; //OUT Parameter
	FVector StartLocation = Barrel->GetSocketLocation(FName("Projectile"));

	//Calculate the OutLaunchVelocity
	bool bHasAimSolution = UGameplayStatics::SuggestProjectileVelocity(
			this,
			OutLaunchVelocity,
			StartLocation,
			HitLocation,
			LaunchSpeed,
			false,
			0,
			0,
			ESuggestProjVelocityTraceOption::TraceFullPath
		);
	if (bHasAimSolution)
	{
		auto AimDirection = OutLaunchVelocity.GetSafeNormal();
		MoveBarrelTowards(AimDirection);
	}
	else
	{
		//return to 0 elevation if false
		FVector Idle = { 0.f, 0.f, 0.f };
		MoveBarrelTowards(Idle);
	}
}

void UTankAimingComponent::MoveBarrelTowards(FVector AimDirection)
{
	// find diff between curent barrel rotation and AinDirection
	auto BarrelElevation = Barrel->GetForwardVector().Rotation();
	auto AimAsRotation = AimDirection.Rotation();
	auto DeltaAim = AimAsRotation - BarrelElevation;

	Barrel->Elevate(DeltaAim.Pitch);
	Turret->Rotate(DeltaAim.Yaw);	
}

