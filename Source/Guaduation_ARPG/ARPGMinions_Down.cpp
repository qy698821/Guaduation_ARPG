// Fill out your copyright notice in the Description page of Project Settings.


#include "ARPGMinions_Down.h"
#include "Down_Minions_Controller.h"
#include "Runtime/Engine/Classes/Kismet/GameplayStatics.h"
#include "Engine.h"
#include "ARPGCharacter.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Runtime/Engine/Classes/Kismet/KismetMathLibrary.h"
#include "BehaviorTree/BlackboardComponent.h"

AARPGMinions_Down::AARPGMinions_Down() 
{
	PrimaryActorTick.bCanEverTick = true;

	//AIControllerClass = ADown_Minions_Controller::StaticClass();

	//Distribute Behavior Tree
	static ConstructorHelpers::FObjectFinder<UBehaviorTree> BehaviorTreeAssert(TEXT("/Game/Blueprints/Enemy/Minions_Down/BT_Minions_Down.BT_Minions_Down"));
	if (BehaviorTreeAssert.Succeeded())
	{
		BehaviorTree = BehaviorTreeAssert.Object;
	}
}

void AARPGMinions_Down::UpdateSpeed(float speed)
{
	this->GetCharacterMovement()->MaxWalkSpeed = speed;
}

void AARPGMinions_Down::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}
