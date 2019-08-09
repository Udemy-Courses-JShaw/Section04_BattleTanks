// Copyright MetalMuffin Entertainment 2018

#pragma once

#include "CoreMinimal.h"
#include "Components/StaticMeshComponent.h"
#include "Public/SprungWheel.h"

#include "TankTrack.generated.h" //MUST be last!!

/**
 * TankTrack is used to set maximum driving force, and to apply forces to the tank.
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
	float TrackMaxDriveForce = 40000000.0f;

private:
	UTankTrack();

	TArray<class ASprungWheel*> GetWheels() const;

	void DriveTrack(float CurrentThrottle);

};
