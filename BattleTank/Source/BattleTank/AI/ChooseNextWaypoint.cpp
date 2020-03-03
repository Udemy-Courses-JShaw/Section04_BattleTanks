// Copyright MetalMuffin Entertainment 2018


#include "ChooseNextWaypoint.h"
#include "BehaviorTree/BlackboardComponent.h"

EBTNodeResult::Type UChooseNextWaypoint::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	auto BlackboardComponent = OwnerComp.GetBlackboardComponent();
	auto Index = BlackboardComponent->GetValueAsInt(BBIndexKey.SelectedKeyName);

	UE_LOG(LogTemp, Warning, TEXT("Waypoint Index: %i"), Index)
	
	return EBTNodeResult::Succeeded;
}
