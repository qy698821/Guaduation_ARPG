// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameMode.h"
#include "Engine/DataTable.h"
#include "ARPGGameMode.generated.h"

/**
 * 
 */
UCLASS()
class GUADUATION_ARPG_API AARPGGameMode : public AGameMode
{
	GENERATED_BODY()
public:
	UDataTable* GetInventoryTable() { return InventoryTable; }

protected:
	UPROPERTY(EditDefaultsOnly)
	UDataTable* InventoryTable;
	
};
