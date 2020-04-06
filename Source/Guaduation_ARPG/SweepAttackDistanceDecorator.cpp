// Fill out your copyright notice in the Description page of Project Settings.


#include "SweepAttackDistanceDecorator.h"
#include "ARPGBoss_Kwang.h"
#include "AIController.h"
#include "BehaviorTree/BlackboardComponent.h"

bool USweepAttackDistanceDecorator::CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const
{
	AARPGBoss_Kwang* Ptr = Cast<AARPGBoss_Kwang>(OwnerComp.GetAIOwner()->GetCharacter());
	if (Ptr)
	{
		float Distance = Ptr->GetDistanceTo(Ptr->CurrentPlayer);
		if (Distance > Ptr->DistanceJudY && Distance <= Ptr->DistanceJudX)
		{
			if (Ptr->SweepAttackCD >= Ptr->MaxSweepAttackCD - 0.01f)
			{
				return true;
			}
		}
	}
	return false;
}