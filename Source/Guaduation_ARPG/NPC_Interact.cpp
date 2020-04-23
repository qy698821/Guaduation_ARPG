// Fill out your copyright notice in the Description page of Project Settings.


#include "NPC_Interact.h"
#include "ARPGPlayerController.h"
#include "ARPGGameMode.h"
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
	ObjectInteractBlueprint(Controller);
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
		ShopItem.Add(*ItemToAdd2);

		for (int i = 2; i < ShopNum; ++i)
		{
			ShopItem.Add(*ItemToAdd);
		}

	}
}