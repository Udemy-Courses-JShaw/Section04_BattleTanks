// Copyright MetalMuffin Entertainment 2018

#include "ExplosionFragment.h" //MUST be first
#include "GameFramework/Actor.h"
#include "Math/UnrealMathUtility.h"
#include "Particles/ParticleSystemComponent.h"
#include "Public/TankTurret.h"
#include "TimerManager.h"

// Sets default values
AExplosionFragment::AExplosionFragment()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	CollisionMesh = CreateDefaultSubobject<UStaticMeshComponent>(FName("Collision Mesh"));
	SetRootComponent(CollisionMesh);
	CollisionMesh->SetVisibility(false);

	FireTrail = CreateDefaultSubobject<UParticleSystemComponent>(FName("Fire Trail"));
	FireTrail->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);

	ProjectileMovement = CreateDefaultSubobject<UProjectileMovementComponent>(FName("Projectile Movement"));
	ProjectileMovement->bAutoActivate = false;
}

 //Called when the game starts or when spawned
void AExplosionFragment::BeginPlay()
{
	Super::BeginPlay();
	
	SetLifeSpan(DestroyDelay);
}

void AExplosionFragment::LaunchFragments(float FragmentLaunchSpeed)
{
	ProjectileMovement->SetVelocityInLocalSpace(FVector::ForwardVector * FragmentLaunchSpeed);
	ProjectileMovement->Activate();
}

void AExplosionFragment::OnTimerExpire()
{
	Destroy();
}