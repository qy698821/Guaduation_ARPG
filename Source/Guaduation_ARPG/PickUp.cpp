// Fill out your copyright notice in the Description page of Project Settings.


#include "PickUp.h"
#include "ARPGPlayerController.h"

void APickUp::ObjectInteract(APlayerController* Controller) 
{
	AARPGPlayerController* Ptr = Cast<AARPGPlayerController>(Controller);
	if (Ptr) 
	{
		Ptr->AddInventoryByID(ID);
		Extra();
		Ptr->LoadWidget();
		this->Destroy();
	}
}

