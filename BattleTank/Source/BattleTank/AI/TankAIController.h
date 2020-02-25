// Copyright MetalMuffin Entertainment 2018

#pragma once

#include "AIController.h"
#include "BattleTank.h"
#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "TankAIController.generated.h" //MUST be last !!


UCLASS()
class BATTLETANK_API ATankAIController : public AAIController
{
	GENERATED_BODY()
	
private:
	virtual void BeginPlay() override;

	virtual void SetPawn(APawn* InPawn) override;

	virtual void Tick(float DeltaSeconds) override;

	UFUNCTION(BlueprintCallable)
	void OnPossesedTankDeath();

protected:
	UPROPERTY(EditDefaultsOnly, Category = "Settings") 
	float AcceptanceRadius = 8000.f; //Used for Nav Calculations: How close to the player can the AI get
		
public:
};
