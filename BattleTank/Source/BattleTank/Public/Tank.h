// Copyright MetalMuffin Entertainment 2018

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"

#include "Tank.generated.h" //MUST always be last

//Delegate Broadcast for OnDeath()
DECLARE_DYNAMIC_MULTICAST_DELEGATE( FTankDelegate );

//Forward Decalrations
class AExplosionFragment;
class UTankTurret;

UCLASS()
class BATTLETANK_API ATank : public APawn
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintCallable, Category = "Health")
	virtual float TakeDamage(float DamageAmount, struct FDamageEvent const & DamageEvent, class AController * EventInstigator, AActor * DamageCauser) override;

	//Returns health as a % of starting health between 0 ,1
	UFUNCTION(BlueprintPure, Category = "Health")
	float GetHealthPercent() const;

	FTankDelegate OnDeath;

	UPROPERTY(BlueprintReadWrite, Category = "Player Status")
	bool IsTankDead = false;

	UFUNCTION(BlueprintCallable, Category = "Setup")
	void DeathExplosion();

	/** Sound to play each time we fire */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Gameplay")
	class USoundBase* FireSound;

	/** Sound to play each time tank dies */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Gameplay")
	class USoundBase* DeathSound;

private:
	// Sets default values for this pawn's properties
	ATank();

	virtual void BeginPlay() override;

	virtual void Tick(float DeltaTime) override;

	FVector TankLocation = {};
	
	UPROPERTY(EditDefaultsOnly, Category = "Setup")
	int32 StartingHealth = 100;
	
	UPROPERTY(VisibleAnywhere, Category = "Health")
	int32 CurrentHealth; //Initialised in BeginPlay()

	UPROPERTY(EditDefaultsOnly, Category = "Setup")
	TSubclassOf<AExplosionFragment> ExplosionFragmentBlueprint;

	//Used in Deathexplosion()
	FRotator GetRandomRotation();

	UFUNCTION(BlueprintCallable, Category = "Health")
	void KillPlayer();
};
