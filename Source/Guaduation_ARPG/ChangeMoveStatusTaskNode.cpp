// Fill out your copyright notice in the Description page of Project Settings.


#include "ChangeMoveStatusTaskNode.h"
#include "ARPGBoss_Kwang.h"
#include "AIController.h"
#include "Runtime/Engine/Classes/Kismet/KismetMathLibrary.h"
#include "BehaviorTree/BlackboardComponent.h"

EBTNodeResult::Type UChangeMoveStatusTaskNode::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	AARPGBoss_Kwang* Ptr = Cast<AARPGBoss_Kwang>(OwnerComp.GetAIOwner()->GetCharacter());
	if (Ptr)
	{
		Ptr->ChangeMoveStatus();
		return EBTNodeResult::Succeeded;
	}
	else
	{
		return EBTNodeResult::Failed;
	}
}
