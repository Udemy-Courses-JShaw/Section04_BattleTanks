// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/StaticMeshComponent.h"
#include "TankTurret.generated.h"

class UTankTurret;
/*
* Turret is used for rotation of hte barrel for aiming without facing the entire tank.
* Tank body and turret are able to move independantly.
*/
UCLASS( meta=(BlueprintSpawnableComponent) )
class BATTLETANK_API UTankTurret : public UStaticMeshComponent
{
	GENERATED_BODY()

protected:

public:	
	void Rotate(float RelativeRotaitonIn);

private:
	UPROPERTY(EditDefaultsOnly, Category = Setup)
	float MaxDegreesPerSecond = 5.f;
		
	
};
