// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ARPGCharacter.h"
#include "Interact.h"
#include "GameFramework/PlayerController.h"
#include "ARPGPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class GUADUATION_ARPG_API AARPGPlayerController : public APlayerController
{
	GENERATED_BODY()
protected:
	virtual void SetupInputComponent() override;

public:
	//Move function
	UFUNCTION()
	void MoveForward(float Value);
	UFUNCTION()
	void MoveRight(float Value);

	UFUNCTION()
		void Turn(float Value);

	UFUNCTION()
		void LookUp(float Value);

	//Inventory save
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<FInventoryItem> Inventory;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	AInteract* CurrentInteract;

	//Set and release CurrentInterct
	void SetCurrentInteract(AInteract* Interact);

	void ReleaseCurrentInteract();

	//Press E to do something
	UFUNCTION()
	void ObjectInteract();

	//Init Inventory
	UFUNCTION(BlueprintCallable)
	void InitInventory();

	//Inventory num
	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	int Num_Inventory = 40;

	//Add Invemtory By ID
	void AddInventoryByID(FName ID);

	//Check if The IDInventory have
	bool CheckIDHave(FName ID);

	//Add Inventory Objeck
	void AddInventoryObjeck(FInventoryItem* Item);

	//Jump
	void StartJump();

	void StopJump();

	//Reduce Num of Inventory
	UFUNCTION(BlueprintCallable)
		void InventoryOnUse(int Num, int index);

	//Exchange Item By Index
	UFUNCTION(BlueprintCallable)
		void ExchangeByIndex(int Index1, int Index2, FInventoryItem Inventory1, FInventoryItem Inventory2);

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
		void LoadWidget();

	//Bind FastAttack Action
	void OnFastAttack();

	//Bind LockEnemy Action
	void LockEnemy();

	//Bind SwitchLeft Action
	void SwitchLeft();

	//Bind SwitchRight Action
	void SwitchRight();

	
};
