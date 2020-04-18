// Fill out your copyright notice in the Description page of Project Settings.


#include "Minions_Patrol_TaskNode.h"
#include "ARPGMinions_Down.h"
#include "Down_Minions_Controller.h"
#include "Runtime/Engine/Classes/Kismet/KismetMathLibrary.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "NavigationSystem.h"

EBTNodeResult::Type UMinions_Patrol_TaskNode::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	AARPGMinions_Down* Ptr = Cast<AARPGMinions_Down>(OwnerComp.GetAIOwner()->GetCharacter());
	if (Ptr)
	{
		Ptr->UpdateSpeed(Ptr->PatrolSpeed);
		UNavigationSystemV1* NavMesh = UNavigationSystemV1::GetCurrent(OwnerComp.GetAIOwner());
		if (NavMesh) 
		{
			FNavLocation RandomPt;
			const bool bFound = NavMesh->GetRandomReachablePointInRadius(Ptr->GetActorLocation(), Ptr->PatrolRadius, RandomPt);
			ADown_Minions_Controller* ControllerPtr = Cast<ADown_Minions_Controller>(OwnerComp.GetAIOwner());
			if (ControllerPtr) 
			{
				FName PatrolLocation = "PatrolLocation";
				if (bFound)
				{
					ControllerPtr->BBComponent->SetValueAsVector(PatrolLocation, RandomPt.Location);
					return EBTNodeResult::Succeeded;
				}
				else 
				{
					ControllerPtr->BBComponent->SetValueAsVector(PatrolLocation, Ptr->GetActorLocation());
					return EBTNodeResult::Succeeded;
				}
			}
		}
	}
	return EBTNodeResult::Failed;
}
