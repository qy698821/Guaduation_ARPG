// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTDecorator.h"
#include "Boss_SuperArmorDecorator.generated.h"

/**
 * 
 */
UCLASS()
class GUADUATION_ARPG_API UBoss_SuperArmorDecorator : public UBTDecorator
{
	GENERATED_BODY()
protected:
	virtual bool CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const override;
};
