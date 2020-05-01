// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Interact.h"
#include "TransportInteract.generated.h"

/**
 * 
 */
UCLASS()
class GUADUATION_ARPG_API ATransportInteract : public AInteract
{
	GENERATED_BODY()
public:
	ATransportInteract();

	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "LevelName")
		FName LevelName;

	virtual void ObjectInteract(APlayerController* Controller) override;

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
		void OpenLevelInBP();
};
