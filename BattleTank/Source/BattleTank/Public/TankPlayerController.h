// Copyright MetalMuffing Entertainment 2018

#pragma once

#include "BattleTank.h"
#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "TankPlayerController.generated.h" //MUST always be last!!

//Forward Declarations
class ATank;
class UTankAimingComponent;

/**
 * 
 */
UCLASS()
class BATTLETANK_API ATankPlayerController : public APlayerController
{
	GENERATED_BODY()

private:

	virtual void BeginPlay() override;
	virtual void Tick(float) override;

	//Starts moving the tank barrel and turret towards the crosshair made in the UI 
	void AimAtCrosshair();

	// Returns out parameter, true if Hit landscape
	bool GetSightRayHitLocation(FVector& HitLocation) const;

	bool GetLookVectorHitLocation(FVector LookDirection, FVector& HitLocation) const;
	bool GetLookDirection(FVector2D ScreenLocation, FVector& LookDirection) const;

	UPROPERTY(EditDefaultsOnly)
	float CrossHairXLocation = 0.5f;

	UPROPERTY(EditDefaultsOnly)
	float CrossHairYLocation = 0.33333f;

	UPROPERTY(EditDefaultsOnly)
	float LineTraceRange = 1000000.0f;  //10K range

protected:
	UFUNCTION(BlueprintCallable, Category = "Setup")
	ATank* GetControlledTank() const;
	
	UFUNCTION(BlueprintImplementableEvent, Category = "Setup")
	void FoundAimingComponent(UTankAimingComponent* AimCompRef);
};