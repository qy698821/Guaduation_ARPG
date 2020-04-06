// Fill out your copyright notice in the Description page of Project Settings.


#include "Boss_SweepAttackTaskNode.h"
#include "ARPGBoss_Kwang.h"
#include "AIController.h"
#include "Runtime/Engine/Classes/Kismet/KismetMathLibrary.h"
#include "BehaviorTree/BlackboardComponent.h"

EBTNodeResult::Type UBoss_SweepAttackTaskNode::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	AARPGBoss_Kwang* Ptr = Cast<AARPGBoss_Kwang>(OwnerComp.GetAIOwner()->GetCharacter());
	if (Ptr)
	{
		if (Ptr->IsAttack)
		{
			return EBTNodeResult::Succeeded;
		}
		else
		{
			Ptr->OnSweepAttack();
			return EBTNodeResult::Succeeded;
		}
	}
	else
	{
		return EBTNodeResult::Failed;
	}
}