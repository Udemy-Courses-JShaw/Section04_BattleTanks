// Copyright MetalMuffing Entertainment 2018

#include "Public/TankAIController.h"
#include "Public/TankPlayerController.h"
#include "Public/TankAimingComponent.h"
#include "AIController.h"
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

	APawn* ControlledTank = GetPawn();
	APawn* PlayerTank = GetWorld()->GetFirstPlayerController()->GetPawn();
	UTankAimingComponent*  TankAimingComponent = ControlledTank->FindComponentByClass<UTankAimingComponent>();

	if (!ensure(PlayerTank) && ControlledTank ) { return; }
	
	// Move towards Player
	MoveToActor(PlayerTank, AcceptanceRadius); //TODO check radius is in CM

	//Aim at Player
	TankAimingComponent->AimAt(PlayerTank->GetActorLocation());

	// TODO Fix Firing
	//ConrolledTank->Fire();

}