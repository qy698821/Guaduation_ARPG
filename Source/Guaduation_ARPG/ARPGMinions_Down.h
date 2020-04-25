// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "EnemyBase.h"
#include "BehaviorTree/BehaviorTree.h"
#include "ARPGMinions_Down.generated.h"

/**
 * 
 */
UCLASS()
class GUADUATION_ARPG_API AARPGMinions_Down : public AEnemyBase
{
	GENERATED_BODY()

public:
	virtual void Tick(float DeltaTime) override;

	AARPGMinions_Down();

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		class UBehaviorTree* BehaviorTree;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float ChaseSpeed = 500.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float PatrolSpeed = 250.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float PatrolRadius = 1000.0f;

	UFUNCTION(BlueprintCallable)
		void UpdateSpeed(float speed);

};
