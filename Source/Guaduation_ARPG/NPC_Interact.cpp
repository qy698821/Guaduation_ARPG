// Fill out your copyright notice in the Description page of Project Settings.


#include "NPC_Interact.h"
#include "ARPGPlayerController.h"
#include "ARPGGameMode.h"
#include "Runtime/Engine/Classes/Kismet/GameplayStatics.h"
#include "ARPGCharacter.h"
#include "Components/SkeletalMeshComponent.h"
#include "GameFramework/CharacterMovementComponent.h"

ANPC_Interact::ANPC_Interact() 
{
	Mesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Mesh"));
	Mesh->SetupAttachment(RootComponent);

	NPCCharacterMovement = CreateDefaultSubobject<UCharacterMovementComponent>(TEXT("NPCCharacterMovement"));
	
}

void ANPC_Interact::ObjectInteract(APlayerController * Controller)
{
	DialogThink(Controller);
}

void ANPC_Interact::EndOverlap(UPrimitiveComponent * OverlappedComponent, AActor * OtherActor, UPrimitiveComponent * OtherComp, int OtherBodyIndex)
{
	Super::EndOverlap(OverlappedComponent, OtherActor, OtherComp, OtherBodyIndex);
	CloseDialogWidget();
}

void ANPC_Interact::InitShop() 
{
	if (ShopItem.Num() == 0)
	{
		AARPGGameMode* GameMode = Cast<AARPGGameMode>(GetWorld()->GetAuthGameMode());
		UDataTable* ItemTable = GameMode->GetInventoryTable();
		FInventoryItem* ItemToAdd = ItemTable->FindRow<FInventoryItem>("0", "");
		FInventoryItem* ItemToAdd1 = ItemTable->FindRow<FInventoryItem>("1", "");
		FInventoryItem* ItemToAdd2 = ItemTable->FindRow<FInventoryItem>("2", "");
		ShopItem.Add(*ItemToAdd1);
		//!ShopItem.Add(*ItemToAdd2);

		for (int i = 1; i < ShopNum; ++i)
		{
			ShopItem.Add(*ItemToAdd);
		}

	}
}

void ANPC_Interact::SetCurrentDialog(FString String)
{
	CurrentDialog = String;
}

void ANPC_Interact::DialogThink(APlayerController* Controller)
{
	if (IsShopOpend) 
	{
		return;
	}
	if (IsEndOfDialog) 
	{
		CloseDialogWidget();
	}
	else 
	{
		OpenDialogWidget();
		//First dialog
		if (NumofFirstDialog <= FirstDialogArray.Num())
		{
			if (NumofFirstDialog == FirstDialogArray.Num())
			{
				CloseDialogWidget();
				ObjectInteractBlueprint(Controller);
				ACharacter* CharacterPtr = UGameplayStatics::GetPlayerCharacter(GetWorld(),0);
				AARPGCharacter* AARPGCharacterPtr = Cast<AARPGCharacter>(CharacterPtr);
				AARPGCharacterPtr->Task1->ChangeStep(1);
				DeleteBlockwall();
				NumofFirstDialog++;
			}
			else 
			{
				SetCurrentDialog(FirstDialogArray[NumofFirstDialog]);
				NumofFirstDialog++;
			}
		}
		//loop
		else
		{
			if (ShouldCloseWidget) 
			{
				CloseDialogWidget();
				ObjectInteractBlueprint(Controller);
			}
			else 
			{
				SetCurrentDialog(LoopDialog);
				ShouldCloseWidget = true;
			}
		}
	}
}
