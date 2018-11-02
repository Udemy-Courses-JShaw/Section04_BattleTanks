// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/StaticMeshComponent.h"
#include "TankBarrel.generated.h"

class UTankBarrel;

UCLASS( meta=(BlueprintSpawnableComponent) )
class BATTLETANK_API UTankBarrel : public UStaticMeshComponent
{
	GENERATED_BODY()
	
protected:
	//Attaching the barrel to circumvent Unreal v4.20 bug (barrel keeps dissapearing on compile)
	//UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Mesh")
	UTankBarrel* BarrelMesh = nullptr;

public:
	//-1 is max downward movement speed, +1 is max upward speed of barrel
	void Elevate(float RelativeSpeedIn);
	
private:
	UPROPERTY(EditDefaultsOnly, Category = Setup)
	float MaxDegreesPerSecond = 5.f; 

	UPROPERTY(EditDefaultsOnly, Category = Setup)
	float MaxElevationDegrees = 45.f;
	
	UPROPERTY(EditDefaultsOnly, Category = Setup)
	float MinElevationDegrees = 0.f; 
};
