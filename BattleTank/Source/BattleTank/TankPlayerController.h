// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "BattleTank.h"
#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "Public/Tank.h"
#include "TankPlayerController.generated.h" //MUST always be last!!

/**
 * 
 */
UCLASS()
class BATTLETANK_API ATankPlayerController : public APlayerController
{
	GENERATED_BODY()
	
public:

	FVector Hitlocation;

	virtual void BeginPlay() override;
	virtual void Tick(float) override;

	ATank* GetControlledPlayerTank() const;
	
	//Starts moving the tank barrel and turret towards the crosshair made in the UI 
	void AimAtCrosshair();
private:
	// Returns out parameter, true if Hit landscape
	bool GetSightRayHitLocation(FVector& HitLocation) const;
	
};
