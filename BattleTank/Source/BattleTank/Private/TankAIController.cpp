// Copyright MetalMuffin Entertainment 2018

#include "Public/TankAIController.h" //MUST be first
#include "Public/Tank.h"
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
	UE_LOG(LogTemp, Error, TEXT("Controller Detatched!!")) //TODO remove
}

//Called EVERY Frame
void ATankAIController::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	APawn* ControlledTank = GetPawn();
	APawn* PlayerTank = GetWorld()->GetFirstPlayerController()->GetPawn();

	if (!ensure( ControlledTank )) { return; }
	if (!ensure( PlayerTank )) { return; }
	
	// Move towards Player
	MoveToActor(PlayerTank, AcceptanceRadius); //TODO check radius is in CM

	//Aim at Player
	UTankAimingComponent*  TankAimingComponent = ControlledTank->FindComponentByClass<UTankAimingComponent>();
	TankAimingComponent->AimAt(PlayerTank->GetActorLocation());

	//If aiming or locked
	if (TankAimingComponent->GetFiringState() == EFiringStatus::Locked)
	{
		TankAimingComponent->Fire();
	}

}
