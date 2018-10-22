// Fill out your copyright notice in the Description page of Project Settings.

#include "TankPlayerController.h"
#include "Engine/Engine.h"
#include "GameFramework/PlayerController.h"
#include "GameFramework/Actor.h"


void ATankPlayerController::BeginPlay()
{
	Super::BeginPlay();

	auto ControlledTank = GetControlledPlayerTank();
	if (!ControlledTank)
	{
		UE_LOG(LogTemp, Warning, TEXT("PlayerController is not Possessing Tank!!"))
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("PlayerController Possessing %s !!"), *(ControlledTank->GetName()))
	}
}

ATank* ATankPlayerController::GetControlledPlayerTank() const
{
	return Cast<ATank>(GetPawn());
}


