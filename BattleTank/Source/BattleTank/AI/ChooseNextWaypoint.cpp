// Copyright MetalMuffin Entertainment 2018


#include "ChooseNextWaypoint.h"
#include "AIController.h"
#include "Tanks/Tank.h"
#include "Tanks/Components/PatrolComponent.h"
#include "BehaviorTree/BlackboardComponent.h"

EBTNodeResult::Type UChooseNextWaypoint::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	//Get Patrol Route
	auto ControlledPawn = OwnerComp.GetAIOwner()->GetPawn();
	auto PatrolRoute = ControlledPawn->FindComponentByClass<UPatrolComponent>();
	//Warn against no components
	if (!ensure(PatrolRoute)) 
	{ 
		UE_LOG(LogTemp, Warning, TEXT("No Patrol Points Component!"))
		return EBTNodeResult::Failed; 
	}

	//Warn against Empty Patrol routes
	auto PatrolPoints = PatrolRoute->GetPatrolPoints();
	if (PatrolPoints.Num() == 0)
	{
		UE_LOG(LogTemp, Warning, TEXT("No Patrol Points added!"))
		return EBTNodeResult::Failed;
	}

	//Set Next Waypoint
	auto BlackboardComponent = OwnerComp.GetBlackboardComponent();
	auto Index = BlackboardComponent->GetValueAsInt(IndexKey.SelectedKeyName);
	BlackboardComponent->SetValueAsObject(WaypointKey.SelectedKeyName, PatrolPoints[Index]);

	//Cycle Index
	auto NextIndex = (Index + 1) % PatrolPoints.Num();
	BlackboardComponent->SetValueAsInt(IndexKey.SelectedKeyName, NextIndex);

	//UE_LOG(LogTemp, Warning, TEXT("Waypoint Index: %i"), Index)
	
	return EBTNodeResult::Succeeded;
}
