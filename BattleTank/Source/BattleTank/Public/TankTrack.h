// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/StaticMeshComponent.h"
#include "TankTrack.generated.h"

class UTankTrack;

/*
* Tank tracks are used to set maximum Driving force, and to apply that force to tha tank.
*/
UCLASS( meta=(BlueprintSpawnableComponent) )
class BATTLETANK_API UTankTrack : public UStaticMeshComponent
{
	GENERATED_BODY()
	
public:
	//Sets A throttle between -1 and +1
	UFUNCTION(BlueprintCallable, Category = Input)
	void Throttle(float Throttle);
	
	
};
