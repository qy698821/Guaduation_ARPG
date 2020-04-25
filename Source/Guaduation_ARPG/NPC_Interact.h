// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Interact.h"
#include "NPC_Interact.generated.h"

/**
 * 
 */
UCLASS()
class GUADUATION_ARPG_API ANPC_Interact : public AInteract
{
	GENERATED_BODY()
public:
	ANPC_Interact();

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		USkeletalMeshComponent* Mesh;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		UCharacterMovementComponent* NPCCharacterMovement;

	virtual void ObjectInteract(APlayerController* Controller) override;

	UFUNCTION(BlueprintImplementableEvent)
		void ObjectInteractBlueprint(APlayerController* Controller);

	//Shop Item
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		TArray<FInventoryItem> ShopItem;

	UFUNCTION(BlueprintCallable)
		void InitShop();

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		int ShopNum = 12;
	
};
