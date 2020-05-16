// Fill out your copyright notice in the Description page of Project Settings.


#include "Task_1Actor.h"
#include "Runtime/Engine/Classes/Kismet/GameplayStatics.h"
#include "Engine.h"

// Sets default values
ATask_1Actor::ATask_1Actor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

}

// Called when the game starts or when spawned
void ATask_1Actor::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ATask_1Actor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ATask_1Actor::ChangeStep(int number)
{
	//play shound
	if (CompleteTaskSound)
	{
		UGameplayStatics::PlaySound2D(GetWorld(), CompleteTaskSound);
	}
	StepNum = number;
	//change tips
	if (StepNum < TaskTips.Num())
	{
		CurrentTips = TaskTips[StepNum];
	}
}

