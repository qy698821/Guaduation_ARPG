// Fill out your copyright notice in the Description page of Project Settings.


#include "ARPGPlayerController.h"

void AARPGPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();
	InputComponent->BindAxis("LookUp", this, &AARPGPlayerController::AddPitchInput);
	InputComponent->BindAxis("Turn", this, &AARPGPlayerController::AddYawInput);
	InputComponent->BindAxis("MoveForward", this, &AARPGPlayerController::MoveForward);
	InputComponent->BindAxis("MoveRight", this, &AARPGPlayerController::MoveRight);
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
