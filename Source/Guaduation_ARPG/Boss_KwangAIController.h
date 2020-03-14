// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "Boss_KwangAIController.generated.h"

/**
 * 
 */
UCLASS()
class GUADUATION_ARPG_API ABoss_KwangAIController : public AAIController
{
	GENERATED_BODY()
public:

	ABoss_KwangAIController();

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class UBehaviorTreeComponent* BehaviorTreeCompo;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class UBlackboardComponent* BBComponent;

protected:
	virtual void OnPossess(APawn* InPawn) override;
	virtual void OnUnPossess() override;

	
};
