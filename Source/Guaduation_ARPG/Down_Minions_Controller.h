// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "Down_Minions_Controller.generated.h"

/**
 * 
 */
UCLASS()
class GUADUATION_ARPG_API ADown_Minions_Controller : public AAIController
{
	GENERATED_BODY()
public:

	ADown_Minions_Controller();

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		class UBehaviorTreeComponent* BehaviorTreeCompo;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		class UBlackboardComponent* BBComponent;

protected:
	virtual void OnPossess(APawn* InPawn) override;
	virtual void OnUnPossess() override;
};
