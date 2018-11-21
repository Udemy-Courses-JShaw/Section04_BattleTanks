// Copyright MetalMuffing Entertainment 2018

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
	//Sets a throttle between -1 and +1
	UFUNCTION(BlueprintCallable, Category = Input) 
	void SetThrottle(float Throttle);
	
	//Max force per track in NEWTONS
	UPROPERTY(EditDefaultsOnly)
	float TrackMaxDriveForce = 146963.97f;
};
