// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Interact.h"
#include "PickUp.generated.h"

/**
 * 
 */
UCLASS()
class GUADUATION_ARPG_API APickUp : public AInteract
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	FName ID;

	UPROPERTY(BlueprintReadWrite)
		float Value = 0.0f;

	//Event Interact
	virtual void ObjectInteract(APlayerController* Controller) override;

	//Actor be used
	UFUNCTION(BlueprintImplementableEvent,BlueprintCallable)
		void OnUse();

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
		void Extra();

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FString GetInfo;
	
};
