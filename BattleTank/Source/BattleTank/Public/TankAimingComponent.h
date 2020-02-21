// Copyright MetalMuffin Entertainment 2018

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "TankAimingComponent.generated.h"

/**
*  Aiming Component the is used by the AI to aim at the player
*/

//Enum for aiming state
UENUM(BlueprintType)
enum class EFiringStatus : uint8
{
	Reloading,
	Aiming,
	OutOfAmmo,
	Ready,
};

//Forward Declaration
class AProjectile;
class UTankBarrel;
class UTankTurret;

// Holds Barrel's properties and Elevate Method
UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BATTLETANK_API UTankAimingComponent : public UActorComponent
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintCallable, Category = "Setup")
	void Initialize(UTankBarrel* BarrelToSet, UTankTurret* TurretToSet);

	UPROPERTY(BlueprintReadOnly)
	FVector2D SecondaryCrosshairLocation;

	void AimAt(FVector HitLocation);

	UFUNCTION(BlueprintCallable, Category = "Setup")
	void Fire();
	
	UFUNCTION(BlueprintCallable, Category = "Setup")
	UTankBarrel* GetBarrelReference();

	EFiringStatus GetFiringState() const;

	UFUNCTION(BlueprintCallable, Category = "Setup")
	int32 GetRoundsLeft() const;

	UFUNCTION(BlueprintCallable, Category = "Setup")
	void SetAmmoCount(int32 AmmoIn);
 
	UPROPERTY(BlueprintReadWrite, Category = "Firing")
	float LastFireTime = 0;

	UPROPERTY(BlueprintReadWrite, Category = "Firing")
	float ReloadTimeInSeconds = 3;

protected:
	UPROPERTY(BlueprintReadOnly, Category = "State")
	EFiringStatus FiringStatus = EFiringStatus::Reloading;

	UPROPERTY(EditDefaultsOnly, Category = "Firing")
	int32 AmmoCount = 20;
	
private:
	// Sets default values for this component's properties
	UTankAimingComponent();

	virtual void BeginPlay() override;

	void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction * ThisTickfunction);

	void MoveBarrelTowards(FVector AimDirection);

	bool IsBarrelMoving();

	UTankBarrel* Barrel = nullptr;
	UTankTurret* Turret = nullptr;
			
	UPROPERTY(EditDefaultsOnly, Category = "Firing")
	float LaunchSpeed = 32000.f; 

	UFUNCTION(BlueprintCallable, Category = "Firing")
	float GetLastFireTime();

	FVector AimDirection = {};

	UPROPERTY(EditDefaultsOnly, Category = "Setup")
	TSubclassOf<AProjectile> ProjectileBluePrint;

};
