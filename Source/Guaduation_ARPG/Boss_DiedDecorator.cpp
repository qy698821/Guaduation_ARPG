// Fill out your copyright notice in the Description page of Project Settings.


#include "Boss_DiedDecorator.h"
#include "ARPGBoss_Kwang.h"
#include "AIController.h"
#include "BehaviorTree/BlackboardComponent.h"

bool UBoss_DiedDecorator::CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const
{
	AARPGBoss_Kwang* Ptr = Cast<AARPGBoss_Kwang>(OwnerComp.GetAIOwner()->GetCharacter());
	if (Ptr) 
	{
		if (Ptr->IsDied) 
		{
			return true;
		}
		else 
		{
			return false;
		}
	}
	return true;
}
