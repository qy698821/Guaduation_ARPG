// Fill out your copyright notice in the Description page of Project Settings.


#include "ARPGBoss_Kwang.h"
#include "ARPGCharacter.h"
#include "Boss_KwangAIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "UObject/ConstructorHelpers.h" 
#include "Runtime/Engine/Classes/Kismet/GameplayStatics.h"
#include "Engine.h"
#include "Runtime/Engine/Classes/Kismet/KismetMathLibrary.h"

AARPGBoss_Kwang::AARPGBoss_Kwang() 
{
	PrimaryActorTick.bCanEverTick = true;

	AIControllerClass = ABoss_KwangAIController::StaticClass();

	//Distribute Behavior Tree
	static ConstructorHelpers::FObjectFinder<UBehaviorTree> BehaviorTreeAssert(TEXT("/Game/Blueprints/Enemy/BOSS_Kwang/BT_Boss.BT_Boss"));
	if (BehaviorTreeAssert.Succeeded())
	{
		BehaviorTree = BehaviorTreeAssert.Object;
	}

}

void AARPGBoss_Kwang::Locked(ACharacter* CharacterPtr)
{
	IsLocked = true;
	LocalCharacter = CharacterPtr;
	//HpWidget->SetVisibility(true, false);
	//HpWidget->SetHiddenInGame(false, false);
	LockTarget->SetVisibility(true, false);
}

void AARPGBoss_Kwang::LockOff()
{
	IsLocked = false;
	//HpWidget->SetVisibility(false, false);
	//HpWidget->SetHiddenInGame(true, false);
	LockTarget->SetVisibility(false, false);
	LocalCharacter = nullptr;
}

void AARPGBoss_Kwang::LockTick()
{
	//GEngine->AddOnScreenDebugMessage(-1, 3.0f, FColor::Blue, FString::Printf(TEXT("11111")));
}

void AARPGBoss_Kwang::Tick(float DeltaTime)
{

}

void AARPGBoss_Kwang::DestoryByTimer()
{
	BOSSHpBarWidget->RemoveFromParent();
	this->Destroy();
}

void AARPGBoss_Kwang::Start_Boss_Battle() 
{
	ABoss_KwangAIController* Ptr = Cast<ABoss_KwangAIController>(this->GetController());
	if (Ptr) 
	{
		FName IsStart = "IsStart";
		Ptr->BBComponent->SetValueAsBool(IsStart, true);
		Ptr->BBComponent->SetValueAsObject(FName("Player"), UGameplayStatics::GetPlayerController(GWorld, 0)->GetCharacter());
	}
}