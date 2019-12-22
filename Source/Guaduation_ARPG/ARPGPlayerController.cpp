// Fill out your copyright notice in the Description page of Project Settings.


#include "ARPGPlayerController.h"
#include "ARPGGameMode.h"
#include "Engine.h"

void AARPGPlayerController::BeginPlay() 
{
	Super::BeginPlay();
	InitInventory();
}

void AARPGPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();
	//Bind actions and axis
	InputComponent->BindAxis("LookUp", this, &AARPGPlayerController::AddPitchInput);
	InputComponent->BindAxis("Turn", this, &AARPGPlayerController::AddYawInput);
	InputComponent->BindAxis("MoveForward", this, &AARPGPlayerController::MoveForward);
	InputComponent->BindAxis("MoveRight", this, &AARPGPlayerController::MoveRight);
	InputComponent->BindAction("Interact", IE_Pressed, this, &AARPGPlayerController::ObjectInteract);
}

void AARPGPlayerController::MoveForward(float Value) 
{
	FVector Direction = FRotationMatrix(this->GetControlRotation()).GetScaledAxis(EAxis::X);
	this->GetCharacter()->AddMovementInput(Direction, Value);
}

void AARPGPlayerController::MoveRight(float Value) 
{
	FVector Direction = FRotationMatrix(this->GetControlRotation()).GetScaledAxis(EAxis::Y);
	this->GetCharacter()->AddMovementInput(Direction, Value);
}

void AARPGPlayerController::SetCurrentInteract(AInteract* Interact) 
{
	CurrentInteract = Interact;
}

void AARPGPlayerController::ReleaseCurrentInteract() 
{
	CurrentInteract = nullptr;
}

void AARPGPlayerController::ObjectInteract() 
{
	if (CurrentInteract) 
	{
		CurrentInteract->ObjectInteract(this);
	}
}

void AARPGPlayerController::InitInventory() 
{
	if (Inventory.Num() == 0) 
	{
		AARPGGameMode* GameMode = Cast<AARPGGameMode>(GetWorld()->GetAuthGameMode());
		UDataTable* ItemTable = GameMode->GetInventoryTable();
		FInventoryItem* ItemToAdd = ItemTable->FindRow<FInventoryItem>("0", "");
		for (int i = 0; i < Num_Inventory; ++i) 
		{
			Inventory.Add(*ItemToAdd);
		}


	}
}

bool AARPGPlayerController::CheckIDHave(FName ID) 
{
	for (auto& n : Inventory) 
	{
		if (n.ItemID == ID) 
		{
			n.Number++;
			return true;
		}
	}
	return false;
}

void AARPGPlayerController::AddInventoryObjeck(FInventoryItem* Item)
{
	for (int i = 0; i < Inventory.Num(); ++i) 
	{
		if (Inventory[i].ItemID == "0") 
		{
			Inventory.RemoveAt(i);
			Inventory.Insert(*Item, i);
			return;
		}
	}
}

void AARPGPlayerController::AddInventoryByID(FName ID) 
{
	if (CheckIDHave(ID)) 
	{
		return;
	}
	AARPGGameMode* GameMode = Cast<AARPGGameMode>(GetWorld()->GetAuthGameMode());
	UDataTable* ItemTable = GameMode->GetInventoryTable();
	FInventoryItem* ItemToAdd = ItemTable->FindRow<FInventoryItem>(ID, "");
	if (ItemToAdd) 
	{
		AddInventoryObjeck(ItemToAdd);
	}
}