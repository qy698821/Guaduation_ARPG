// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/SphereComponent.h"
#include "ARPGCharacter.h"
#include "Components/StaticMeshComponent.h"
#include "GameFramework/Actor.h"
#include "Interact.generated.h"

UCLASS()
class GUADUATION_ARPG_API AInteract : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AInteract();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditDefaultsOnly)
	FString Name;

	UPROPERTY(EditDefaultsOnly)
	FString Action;

	//Get the object's name and action
	UFUNCTION(BlueprintCallable)
	FString GetText() const
	{
		return FString::Printf(TEXT(". %s : 按E键%s"), *Name, *Action);
	}

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		USphereComponent* CollisionComponent;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		UStaticMeshComponent* ActorVisual;


	//Event CollisionComponent overlap
	UFUNCTION()
	void BeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int OtherBodyIndex, bool FromSweep,const FHitResult& SweepResult);
	UFUNCTION()
	void EndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int OtherBodyIndex);

	//Event Interact
	virtual void ObjectInteract(APlayerController* Controller);



};
