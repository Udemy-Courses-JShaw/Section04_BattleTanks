// Copyright MetalMuffin Entertainment 2018

#pragma once

#include "CoreMinimal.h"
#include "Components/StaticMeshComponent.h"
#include "TankBarrel.generated.h"

class UTankBarrel;

UCLASS( meta=(BlueprintSpawnableComponent) )
class BATTLETANK_API UTankBarrel : public UStaticMeshComponent
{
	GENERATED_BODY()

public:
	//-1 is max downward movement speed, +1 is max upward speed of barrel
	UFUNCTION(BlueprintCallable, Category = "Aiming")
	void Elevate(float RelativeSpeedIn);
	
private:
	UPROPERTY(EditDefaultsOnly, Category = Setup)
	float MaxDegreesPerSecond = 5.f; 

	UPROPERTY(EditDefaultsOnly, Category = Setup)
	float MaxElevationDegrees = 45.f;
	
	UPROPERTY(EditDefaultsOnly, Category = Setup)
	float MinElevationDegrees = 0.f; 
};
