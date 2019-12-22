// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Camera/CameraComponent.h"
#include "Engine/DataTable.h"
#include "GameFramework/Character.h"
#include "ARPGCharacter.generated.h"

USTRUCT(BlueprintType)
struct FInventoryItem : public FTableRowBase 
{
	GENERATED_BODY()

public:
	FInventoryItem() 
	{
		ItemID = TEXT("请输入ID");
		Description = TEXT("请描述该物品");
		Number = 1;
	}

	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	FName ItemID;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString Name;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString Action;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<class APickUp> PickUpClass;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UTexture2D* Thumbnail;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int Value;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int Number;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString Description;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool CanBeUse;

};


UCLASS()
class GUADUATION_ARPG_API AARPGCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AARPGCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	//AddCameraComponent
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		UCameraComponent* ARPGCamera;

};
