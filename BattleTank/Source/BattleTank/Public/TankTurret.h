// Copyright MetalMuffing Entertainment 2018

#pragma once

#include "CoreMinimal.h"
#include "Components/StaticMeshComponent.h"
#include "TankTurret.generated.h"

class UTankTurret;

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
