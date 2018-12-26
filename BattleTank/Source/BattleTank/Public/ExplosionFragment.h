// Copyright MetalMuffin Entertainment 2018

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "ExplosionFragment.generated.h" //MUST be last

//Forward Declarations
class UTankTurret;

UCLASS()
class BATTLETANK_API AExplosionFragment : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AExplosionFragment();

	void LaunchFragments(float FragmentLaunchSpeed);

protected:
	// Called when the game starts or when spawned
	//virtual void BeginPlay() override;  //TODO Verify the need for BeginPlay()

	UProjectileMovementComponent* ProjectileMovement = nullptr;

private:
	UTankTurret* Turret = nullptr;

	float FragmentLaunchSpeed = 0.f;

	UPROPERTY(EditDefaultsOnly, Category = "Setup")
	TSubclassOf<AExplosionFragment> ExplosionFragmentBlueprint;

	UFUNCTION(BlueprintCallable, Category = "Setup")
	void Initialize(UTankTurret* TurretToSet);

	UFUNCTION(BlueprintCallable, Category = "Setup")
	void DeathExplosion();

	void OnTimerExpire();

	UPROPERTY(EditDefaultsOnly, Category = "Setup")
	float DestroyDelay = 3.5f;

	UPROPERTY(VisibleAnywhere, Category = "Components")
	UParticleSystemComponent* FireTrail = nullptr;
};
