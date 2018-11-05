// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/StaticMeshComponent.h"
#include "TankTrack.generated.h" //MUST be last!!

class UTankTrack;

/**
 * 
 */
UCLASS( meta=(BlueprintSpawnableComponent) )
class BATTLETANK_API UTankTrack : public UStaticMeshComponent
{
	GENERATED_BODY()
	
public:
	UFUNCTION(BlueprintCallable, Category = Input) // <<--- Uncomment this will cause an error for me: unresolved external symbol. 
	void SetThrottle(float Throttle);
	
	//Max force per track in newtons
	UPROPERTY(EditDefaultsOnly)
	float TrackMaxDriveForce = 146963.97f;
};
