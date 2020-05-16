// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Sound/SoundWave.h"
#include "Task_1Actor.generated.h"

UCLASS()
class GUADUATION_ARPG_API ATask_1Actor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ATask_1Actor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	//Tips of task
	UPROPERTY(EditAnywhere, BlueprintReadWrite )
		TArray<FString> TaskTips;

	//The current tips that show on UI
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FString CurrentTips;

	UPROPERTY(BlueprintReadWrite)
		int StepNum = 0;

	//Change step when complete task
	UFUNCTION(BlueprintCallable)
		void ChangeStep(int number);


	UPROPERTY(EditAnywhere, BlueprintReadWrite )
		USoundWave* CompleteTaskSound = nullptr;



};
