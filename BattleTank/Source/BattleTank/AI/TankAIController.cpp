// Copyright MetalMuffin Entertainment 2018

#include "AI/TankAIController.h" //MUST be first
#include "AI/TankPlayerController.h"
#include "Tanks/Tank.h"
#include "Tanks/Components/TankAimingComponent.h"
#include "AIController.h"
#include "GameFramework/Actor.h"
#include "Engine/World.h"


void ATankAIController::BeginPlay()
{
	Super::BeginPlay();

	//..
}

void ATankAIController::SetPawn(APawn* InPawn)
{
	Super::SetPawn(InPawn);

	if (InPawn)
	{
		ATank* PossessedTank = Cast<ATank>(InPawn);
		if (!ensure(PossessedTank))	{ return; }

		PossessedTank->OnDeath.AddUniqueDynamic(this, &ATankAIController::OnPossesedTankDeath);
	}
}

void ATankAIController::OnPossesedTankDeath()
{
	if (!ensure(GetPawn()))	{ return; }
	GetPawn()->DetachFromControllerPendingDestroy();
}

//Called EVERY Frame
void ATankAIController::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	APawn* ControlledTank = GetPawn();
	APawn* PlayerTank = GetWorld()->GetFirstPlayerController()->GetPawn();

}
