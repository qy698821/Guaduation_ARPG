// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CharacterBase.h"
#include "Components/StaticMeshComponent.h"
#include "Components/WidgetComponent.h"
#include "EnemyBase.generated.h"

/**
 * 
 */
UCLASS()
class GUADUATION_ARPG_API AEnemyBase : public ACharacterBase
{
	GENERATED_BODY()

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	AEnemyBase();

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		UStaticMeshComponent* LockTarget;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		UWidgetComponent* HpWidget;
	
	ACharacter* LocalCharacter = nullptr;

	bool IsLocked = false;

	//lock function
	virtual void Locked(ACharacter* CharacterPtr);

	virtual void LockOff();

	virtual void LockTick();
	
};
