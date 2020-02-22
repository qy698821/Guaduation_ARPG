// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CharacterBase.h"
#include "Components/StaticMeshComponent.h"
#include "EnemyBase.generated.h"

/**
 * 
 */
UCLASS()
class GUADUATION_ARPG_API AEnemyBase : public ACharacterBase
{
	GENERATED_BODY()

public:

	AEnemyBase();

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		UStaticMeshComponent* LockTarget;
	
};
