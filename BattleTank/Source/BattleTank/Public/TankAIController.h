// Fill out your copyright notice in the Description page of Project Settings.

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
		
	
};
