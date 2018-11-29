// Copyright MetalMuffing Entertainment 2018

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Tank.generated.h" //MUST always be last

//Forward Decalrations
class AProjectile;
class UTankBarrel;
class UTankAimingComponent;


UCLASS()
class BATTLETANK_API ATank : public APawn
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintCallable, Category = Input)
	void Fire();
	
	void AimAt(FVector HitLocation);

protected:
	UPROPERTY(BlueprintReadOnly)
	UTankAimingComponent* TankAimingComponent = nullptr;

private:	
	// Sets default values for this pawn's properties
	ATank();

	virtual void BeginPlay() override;

	//remove once fire() is moved to AimComponent
	UPROPERTY(EditDefaultsOnly, Category = Firing)
	float LaunchSpeed = 167000.f; //launchspeed for a tank shell: 1670 M/s

	UPROPERTY(EditDefaultsOnly, Category = Setup)
	TSubclassOf<AProjectile> ProjectileBluePrint;

	//Local Barrel reference for Spawning projectile
	UTankBarrel* Barrel = nullptr;

	float ReloadTimeInSeconds = 5;
	double LastFireTime = 0;
};
