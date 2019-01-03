// Copyright MetalMuffin Entertainment 2018

#include "Public/Tank.h" //MUST be first
#include "Engine/World.h"
#include "GameFramework/Actor.h"
#include "Public/ExplosionFragment.h"
#include "Math/UnrealMathUtility.h"



// Sets default values
ATank::ATank()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	//....
}

void ATank::BeginPlay()
{
	Super::BeginPlay();

	CurrentHealth = StartingHealth;
}

void ATank::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	TankLocation = { GetActorLocation().X, GetActorLocation().Y, GetActorLocation().Z + 240 }; //Offset the spawn location for Explosion Fragments
}

float ATank::GetHealthPercent() const
{
	return (float)CurrentHealth / (float)StartingHealth;
}

void ATank::DeathExplosion()
{
	if (!ensure(ExplosionFragmentBlueprint)) { return; }

	int32 NumberOfFragments = FMath::RandRange(4, 10);
	for (NumberOfFragments; NumberOfFragments >= 0; NumberOfFragments--)
	{
		float FragmentLaunchSpeed = FMath::RandRange(900.f, 15000.f); 

		AExplosionFragment* ExplosionFragment = GetWorld()->SpawnActor<AExplosionFragment>(
			ExplosionFragmentBlueprint,
			TankLocation, //Location
			GetRandonRotation() //Rotation
			);
		ExplosionFragment->LaunchFragments(FragmentLaunchSpeed); 
	}
}

// Creates a randon rotator for Explosion Fragment dispersion; ideally in a half sphere
FRotator ATank::GetRandonRotation()
{
	const float pitch = FMath::FRandRange(0.f, 360.f);
	const float yaw = FMath::FRandRange(0.f, 360.f);
	const float roll = 180.f; //FMath::FRandRange(0.f, 0.f);
	return FRotator(pitch, yaw, roll);
}

float ATank::TakeDamage(float DamageAmount, struct FDamageEvent const & DamageEvent, class AController * EventInstigator, AActor * DamageCauser)
{
	int32 DamagePoints = FPlatformMath::RoundToInt(DamageAmount);
	int32 DamageToApply = FMath::Clamp(DamagePoints, 0, CurrentHealth);

	CurrentHealth -= DamageToApply;
	if (CurrentHealth <= 0)
	{
		DeathExplosion();
		OnDeath.Broadcast();
	}
	
	return DamageToApply;
}
