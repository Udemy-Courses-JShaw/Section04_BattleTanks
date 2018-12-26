// Copyright MetalMuffin Entertainment 2018

#include "ExplosionFragment.h"
#include "Engine/World.h"
#include "Math/UnrealMathUtility.h"
#include "Particles/ParticleSystemComponent.h"
#include "Public/TankTurret.h"
#include "TimerManager.h"

// Sets default values
AExplosionFragment::AExplosionFragment()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	ProjectileMovement = CreateDefaultSubobject<UProjectileMovementComponent>(FName("Projectile Movement"));
	ProjectileMovement->bAutoActivate = false;

	FireTrail = CreateDefaultSubobject<UParticleSystemComponent>(FName("Fire Trail"));
	FireTrail->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);

}

void AExplosionFragment::Initialize(UTankTurret* TurretToSet)
{
	Turret = TurretToSet;
}

// Called when the game starts or when spawned
//void AExplosionFragment::BeginPlay()
//{
//	Super::BeginPlay();
//	
//}

void AExplosionFragment::LaunchFragments(float FragmentLaunchSpeed)
{
	ProjectileMovement->SetVelocityInLocalSpace(FVector::ForwardVector * FragmentLaunchSpeed);
	ProjectileMovement->Activate();
}

void AExplosionFragment::DeathExplosion()
{
	if (!ensure(Turret)) { return; }
	if (!ensure(ExplosionFragmentBlueprint)) { return; }

	ProjectileMovement->SetVelocityInLocalSpace(FVector::ForwardVector * FragmentLaunchSpeed);
	FireTrail->Activate();

	FTimerHandle TimerHandle;
	GetWorld()->GetTimerManager().SetTimer(
		TimerHandle,
		this,
		&AExplosionFragment::OnTimerExpire,
		1,
		false,
		-1.0f
	);

	int32 NumberOfFragments = FMath::RandRange(3, 10);
	for (NumberOfFragments; NumberOfFragments >= 0; NumberOfFragments--)
	{
		float FragmentLaunchSpeed = FMath::RandRange(100.f, 1000.f); //TODO Change to realistic values

		AExplosionFragment* ExplosionFragment = GetWorld()->SpawnActor<AExplosionFragment>(
			ExplosionFragmentBlueprint,
			Turret->GetSocketLocation(FName("ExplosionFragments")),
			Turret->GetSocketRotation(FName("ExplosionFragments"))
			);
		LaunchFragments(FragmentLaunchSpeed); //TODO Verify this works correctly
	}
}

void AExplosionFragment::OnTimerExpire()
{
	Destroy();
}