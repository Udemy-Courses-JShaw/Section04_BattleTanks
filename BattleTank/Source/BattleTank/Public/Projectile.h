// Copyright MetalMuffing Entertainment 2018

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Projectile.generated.h"

class AProjectile;

UCLASS()
class BATTLETANK_API AProjectile : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AProjectile();
	
	void LaunchProjectile(float LaunchSpeed);

protected:

private:	
	UProjectileMovementComponent* ProjectileMovement = nullptr;

	
	
};
