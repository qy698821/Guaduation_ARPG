// Fill out your copyright notice in the Description page of Project Settings.


#include "ARPGPlayerController.h"
#include "ARPGGameMode.h"
#include "Runtime/Engine/Classes/Kismet/KismetMathLibrary.h"
#include "Engine.h"

void AARPGPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();
	//Bind actions and axis
	InputComponent->BindAxis("LookUp", this, &AARPGPlayerController::LookUp);
	InputComponent->BindAxis("Turn", this, &AARPGPlayerController::Turn);
	InputComponent->BindAxis("MoveForward", this, &AARPGPlayerController::MoveForward);
	InputComponent->BindAxis("MoveRight", this, &AARPGPlayerController::MoveRight);
	InputComponent->BindAction("Interact", IE_Pressed, this, &AARPGPlayerController::ObjectInteract);
	InputComponent->BindAction("Dodge", IE_Pressed, this, &AARPGPlayerController::StartDodge);
	InputComponent->BindAction("Jump", IE_Pressed, this, &AARPGPlayerController::StartJump);
	InputComponent->BindAction("Jump", IE_Released, this, &AARPGPlayerController::StopJump);
	InputComponent->BindAction("FastAttack", IE_Pressed, this, &AARPGPlayerController::OnFastAttack);
	InputComponent->BindAction("LockEnemy", IE_Pressed, this, &AARPGPlayerController::LockEnemy);
	InputComponent->BindAction("SwitchLeft", IE_Pressed, this, &AARPGPlayerController::SwitchLeft);
	InputComponent->BindAction("SwitchRight", IE_Pressed, this, &AARPGPlayerController::SwitchRight);
}

void AARPGPlayerController::MoveForward(float Value) 
{
	AARPGCharacter* CharacterPtr = Cast<AARPGCharacter>(this->GetCharacter());
	if (CharacterPtr) 
	{
		CharacterPtr->DodgeDirection[0] = Value;
		if (CharacterPtr->IsStartDodge || CharacterPtr->IsDamaged)
		{
			return;
		}
		float Delta = GetWorld()->DeltaTimeSeconds;
		//Change direction when character is attacking
		if (CharacterPtr->IsAttacking) 
		{
			FRotator NewRotation = CharacterPtr->GetActorRotation();
			if (Value > 0.5f) 
			{
				NewRotation.Yaw = this->GetControlRotation().Yaw;
				CharacterPtr->SetActorRelativeRotation(UKismetMathLibrary::RInterpTo(CharacterPtr->GetActorRotation(), NewRotation, Delta, CharacterPtr->AttackTurnSpeed));
			}
			else if (Value < -0.5f) 
			{
				NewRotation.Yaw = this->GetControlRotation().Yaw + 180.0f;
				CharacterPtr->SetActorRelativeRotation(UKismetMathLibrary::RInterpTo(CharacterPtr->GetActorRotation(), NewRotation, Delta, CharacterPtr->AttackTurnSpeed));
			}
		}
		else 
		{
			const FRotator Rotation = this->GetControlRotation();
			const FRotator YawRotation(0, Rotation.Yaw, 0);
			const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
			this->GetCharacter()->AddMovementInput(Direction, Value);
		}
	}
}

void AARPGPlayerController::MoveRight(float Value) 
{

	AARPGCharacter* CharacterPtr = Cast<AARPGCharacter>(this->GetCharacter());
	if (CharacterPtr)
	{
		CharacterPtr->DodgeDirection[1] = Value;//»ñÈ¡×óÓÒÖµ
		if (CharacterPtr->IsStartDodge || CharacterPtr->IsDamaged)
		{
			return;
		}
		if (CharacterPtr->IsAttacking)
		{
			float Delta = GetWorld()->DeltaTimeSeconds;
			FRotator NewRotation = CharacterPtr->GetActorRotation();
			if (Value > 0.5f)
			{
				NewRotation.Yaw = this->GetControlRotation().Yaw + 90.0f;
				CharacterPtr->SetActorRelativeRotation(UKismetMathLibrary::RInterpTo(CharacterPtr->GetActorRotation(), NewRotation, Delta, CharacterPtr->AttackTurnSpeed));
			}
			else if (Value < -0.5f)
			{
				NewRotation.Yaw = this->GetControlRotation().Yaw + 270.0f;
				CharacterPtr->SetActorRelativeRotation(UKismetMathLibrary::RInterpTo(CharacterPtr->GetActorRotation(), NewRotation, Delta, CharacterPtr->AttackTurnSpeed));
			}
		}
		else
		{
			const FRotator Rotation = this->GetControlRotation();
			const FRotator YawRotation(0, Rotation.Yaw, 0);
			const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);
			this->GetCharacter()->AddMovementInput(Direction, Value);
		}
	}
}

void AARPGPlayerController::Turn(float Value)
{
	AARPGCharacter* CharacterPtr = Cast<AARPGCharacter>(this->GetCharacter());
	if (CharacterPtr)
	{
		if (!CharacterPtr->IsLocked) 
		{
			AddYawInput(Value);
		}
	}
}

void AARPGPlayerController::LookUp(float Value)
{
	AARPGCharacter* CharacterPtr = Cast<AARPGCharacter>(this->GetCharacter());
	if (CharacterPtr)
	{
		if (!CharacterPtr->IsLocked)
		{
			AddPitchInput(Value);
		}
	}
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
			if (n.Number < MaxHpPotion) 
			{
				n.Number++;
			}
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

void AARPGPlayerController::StartDodge()
{
	AARPGCharacter* CharacterPtr = Cast<AARPGCharacter>(this->GetCharacter());
	if (CharacterPtr) 
	{
		CharacterPtr->StartDodge();
	}
}

void AARPGPlayerController::StartJump()
{
	this->GetCharacter()->bPressedJump = true;
}

void AARPGPlayerController::StopJump()
{
	this->GetCharacter()->bPressedJump = false;
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

void AARPGPlayerController::InventoryOnUse(int Num, int index) 
{
	if (Inventory[index].Number > 1) 
	{
		Inventory[index].Number--;
	}
	else if (Inventory[index].Number == 1) 
	{
		AARPGGameMode* GameMode = Cast<AARPGGameMode>(GetWorld()->GetAuthGameMode());
		UDataTable* ItemTable = GameMode->GetInventoryTable();
		FInventoryItem* ItemToAdd = ItemTable->FindRow<FInventoryItem>("0", "");
		Inventory.RemoveAt(index);
		Inventory.Insert(*ItemToAdd, index);
	}
}

void AARPGPlayerController::ExchangeByIndex(int Index1, int Index2, FInventoryItem Inventory1, FInventoryItem Inventory2) 
{
	Inventory.RemoveAt(Index1);
	Inventory.Insert(Inventory2, Index1);
	Inventory.RemoveAt(Index2);
	Inventory.Insert(Inventory1, Index2);
}

void AARPGPlayerController::OnFastAttack()
{
	AARPGCharacter* CharacterPtr = Cast<AARPGCharacter>(this->GetCharacter());
	if (CharacterPtr) 
	{
		if (CharacterPtr->IsDamaged) 
		{
			return;
		}
		CharacterPtr->OnFastAttack();
	}
}

void AARPGPlayerController::LockEnemy()
{
	AARPGCharacter* CharacterPtr = Cast<AARPGCharacter>(this->GetCharacter());
	if (CharacterPtr)
	{
		CharacterPtr->LockEnemy();
	}
}

void AARPGPlayerController::SwitchLeft()
{
	AARPGCharacter* CharacterPtr = Cast<AARPGCharacter>(this->GetCharacter());
	if (CharacterPtr)
	{
		CharacterPtr->Switch(0);
	}
}

void AARPGPlayerController::SwitchRight()
{
	AARPGCharacter* CharacterPtr = Cast<AARPGCharacter>(this->GetCharacter());
	if (CharacterPtr)
	{
		CharacterPtr->Switch(1);
	}
}
