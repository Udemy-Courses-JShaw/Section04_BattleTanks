// Copyright MetalMuffin Entertainment 2018


#include "PatrolComponent.h"

TArray<AActor*> UPatrolComponent::GetPatrolPoints() const
{
	return PatrolPointsCPP;
}

