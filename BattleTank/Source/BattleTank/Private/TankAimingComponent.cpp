// Copyright MetalMuffin Entertainment 2018

#include "TankAimingComponent.h"
#include "GameFramework/Actor.h"
#include "GameFramework/Controller.h"
#include "Components/StaticMeshComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Math/Vector.h"
#include "Public/TankBarrel.h"
#include "Public/TankTurret.h"
#include "Public/Projectile.h"



// Sets default values for this component's properties
UTankAimingComponent::UTankAimingComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}

void UTankAimingComponent::BeginPlay() 
{
	Super::BeginPlay();

	LastFireTime = GetWorld()->GetTimeSeconds();
}

void UTankAimingComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction * ThisTickfunction)
{
	if (GetRoundsLeft() <= 0)
	{
		FiringStatus = EFiringStatus::OutOfAmmo;
	}
	else if (LastFireTime + ReloadTimeInSeconds >= GetWorld()->GetTimeSeconds())
	{
		FiringStatus = EFiringStatus::Reloading;
	}
	else if (IsBarrelMoving())
	{
		FiringStatus = EFiringStatus::Aiming;
	}
	else
	{
		FiringStatus = EFiringStatus::Ready;
	}

}

EFiringStatus UTankAimingComponent::GetFiringState() const
{
	return FiringStatus;
}

int32 UTankAimingComponent::GetRoundsLeft() const
{
	return AmmoCount;
}

int32 UTankAimingComponent::GetAmmoCount() const
{
	return AmmoCount;
}

void UTankAimingComponent::SetAmmoCount(int32 AmmoIn)
{
	AmmoCount = AmmoIn;
}

void UTankAimingComponent::Initialize(UTankBarrel* BarrelToSet, UTankTurret* TurretToSet)
{
	Turret = TurretToSet;
	Barrel = BarrelToSet;
}


void UTankAimingComponent::AimAt(FVector HitLocation)
{
	if (!ensure(Barrel)) { 	return; }

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
			0.f,
			0.f,
			ESuggestProjVelocityTraceOption::DoNotTrace
		);

	if (bHasAimSolution)
	{
		AimDirection = OutLaunchVelocity.GetSafeNormal();
		MoveBarrelTowards(AimDirection);
	}

}

void UTankAimingComponent::Fire()
{
	if (!ensure(Barrel)) { return; }
	if (!ensure(ProjectileBluePrint)) { return; }

	if (GetFiringState() == EFiringStatus::Reloading || GetFiringState() == EFiringStatus::OutOfAmmo)
	{ 
		return ;
	}

	if (GetFiringState() == EFiringStatus::Aiming || GetFiringState() == EFiringStatus::Ready )
	{
		AProjectile* Projectile = GetWorld()->SpawnActor<AProjectile>(
			ProjectileBluePrint,
			Barrel->GetSocketLocation(FName("Projectile")),
			Barrel->GetSocketRotation(FName("Projectile"))
			);
		AmmoCount--;

		Projectile->LaunchProjectile(LaunchSpeed);

		//Sets Reload Timer
		LastFireTime = GetWorld()->GetTimeSeconds();
		//UE_LOG(LogTemp, Warning, TEXT("FireTime: %f"), LastFireTime + ReloadTimeInSeconds)
	}
}

void UTankAimingComponent::MoveBarrelTowards(FVector AimDirection)
{
	if (!ensure(Barrel) || !ensure(Turret)) { return; }
	// find diff between current barrel rotation and AimDirection
	FRotator BarrelElevation = Barrel->GetForwardVector().Rotation();
	FRotator AimAsRotation = AimDirection.Rotation();
	FRotator DeltaAim = AimAsRotation - BarrelElevation;

	Barrel->Elevate(DeltaAim.Pitch);
	if (FMath::Abs(DeltaAim.Yaw) < 180)
	{
		Turret->Rotate(DeltaAim.Yaw);
	}
	else
	{
		Turret->Rotate(-DeltaAim.Yaw);
	}
}

bool UTankAimingComponent::IsBarrelMoving()
{
	if (!ensure(Barrel)) { return false; }
	FVector BarrelForward = Barrel->GetForwardVector();
	return !BarrelForward.Equals(AimDirection, 0.1);
	
}

float UTankAimingComponent::GetLastFireTime()
{
	return LastFireTime;
}
