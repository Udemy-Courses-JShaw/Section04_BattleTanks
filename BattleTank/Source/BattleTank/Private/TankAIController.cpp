// Copyright MetalMuffing Entertainment 2018

#include "Public/TankAIController.h"
#include "Public/Tank.h"
#include "TankPlayerController.h"
#include "GameFramework/Actor.h"
#include "Engine/World.h"


void ATankAIController::BeginPlay()
{
	Super::BeginPlay();

	//..
}

void ATankAIController::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	ATank* ConrolledTank = Cast<ATank>(GetPawn());
	ATank* PlayerTank = Cast<ATank>(GetWorld()->GetFirstPlayerController()->GetPawn());

	if (ensure(PlayerTank))
	{
		// Move towards Player
		MoveToActor(PlayerTank, AcceptanceRadius); //TODO check radius is in CM

		//Aim at Player
		ConrolledTank->AimAt(PlayerTank->GetActorLocation());

		ConrolledTank->Fire();
	}

}