// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "EnemyBase.h"
#include "Blueprint/UserWidget.h"
#include "ARPGBoss_Kwang.generated.h"

/**
 * 
 */
UCLASS()
class GUADUATION_ARPG_API AARPGBoss_Kwang : public AEnemyBase
{
	GENERATED_BODY()

public:
	virtual void Locked(ACharacter* CharacterPtr) override;

	virtual void LockOff() override;

	virtual void LockTick() override;

	virtual void Tick(float DeltaTime) override;

	//Boss Hp ui
	UPROPERTY(BlueprintReadWrite)
		UUserWidget* BOSSHpBarWidget = nullptr;

	UPROPERTY(BlueprintReadWrite)
		bool StartBoss = false;

	virtual void DestoryByTimer() override;
	
};
