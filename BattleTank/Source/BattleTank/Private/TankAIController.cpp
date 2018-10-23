// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAIController.h"
#include "AIController.h"
#include "GameFramework/Actor.h"
#include "../Public/TankAIController.h"


void ATankAIController::BeginPlay()
{
	Super::BeginPlay();

	auto PlayerTank = GetPlayerTank();
	if (!PlayerTank)
	{
		UE_LOG(LogTemp, Warning, TEXT("AIController Cant find Player Tank!!"))
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("AIController found player: %s !!"), *(PlayerTank->GetName()))
	}

}

ATank * ATankAIController::GetControlledAITank() const
{
	return Cast<ATank>(GetPawn());
}

ATank * ATankAIController::GetPlayerTank() const
{
	auto PlayerPawn = GetWorld()->GetFirstPlayerController()->GetPawn();
	if (!PlayerPawn){ return nullptr; }
	return Cast<ATank>(PlayerPawn);
}
