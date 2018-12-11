// Copyright MetalMuffin Entertainment 2018

#pragma once

#include "CoreMinimal.h"
#include "Components/StaticMeshComponent.h"
#include "TankTrack.generated.h" //MUST be last!!

class UTankTrack;

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

	virtual void BeginPlay() override;

	void ApplySidewaysForce();

	UFUNCTION()
	void OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, FVector NormalImpulse, const FHitResult& Hit);
	
	void DriveTrack();

	float CurrentThrottle = 0.;

};
