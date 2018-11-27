// Copyright MetalMuffing Entertainment 2018

#pragma once

#include "AIController.h"
#include "BattleTank.h"
#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "TankAIController.generated.h" //MUST be last !!

//Forward declarations
class ATank;

UCLASS()
class BATTLETANK_API ATankAIController : public AAIController
{
	GENERATED_BODY()
	
private:

	virtual void BeginPlay() override;
	virtual void Tick(float DeltaSeconds) override;

	float AcceptanceRadius = 3000.f; //Used for Nav Calculations: How close to the player can the AI get
		
	
};
