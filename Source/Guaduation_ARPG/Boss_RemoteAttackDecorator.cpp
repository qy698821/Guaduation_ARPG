// Fill out your copyright notice in the Description page of Project Settings.


#include "Boss_RemoteAttackDecorator.h"
#include "ARPGBoss_Kwang.h"
#include "AIController.h"
#include "BehaviorTree/BlackboardComponent.h"

bool UBoss_RemoteAttackDecorator::CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const
{
	AARPGBoss_Kwang* Ptr = Cast<AARPGBoss_Kwang>(OwnerComp.GetAIOwner()->GetCharacter());
	if (Ptr)
	{
		float Distance = Ptr->GetDistanceTo(Ptr->CurrentPlayer);
		if (Distance > Ptr->DistanceJudX && Ptr->RemoteAttackCD >= Ptr->MaxRemoteAttackCD)
		{
			return true;
		}
	}
	return false;
}
