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

	virtual void EndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int OtherBodyIndex) override;

	//Shop Item
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		TArray<FInventoryItem> ShopItem;

	UFUNCTION(BlueprintCallable)
		void InitShop();

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		int ShopNum = 12;


	//////Dialog system
	UPROPERTY(BlueprintReadOnly, Category = "DialogSystem")
		FString CurrentDialog;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "DialogSystem")
		bool IsShopOpend = false;

	UFUNCTION(BlueprintCallable)
		void SetCurrentDialog(FString String);

	void DialogThink(APlayerController* Controller);

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
		void OpenDialogWidget();

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
		void CloseDialogWidget();

	UPROPERTY( BlueprintReadWrite, Category = "DialogSystem")
		bool IsDialogOpened = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "DialogSystem" )
		TArray<FString> FirstDialogArray;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "DialogSystem")
		FString LoopDialog;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "DialogSystem")
		FString EndDialog;
	
	int NumofFirstDialog = 0;

	UPROPERTY(BlueprintReadWrite, Category = "DialogSystem")
		bool ShouldCloseWidget = false;

	UPROPERTY(BlueprintReadWrite, Category = "DialogSystem")
		bool IsEndOfDialog = false;


};
