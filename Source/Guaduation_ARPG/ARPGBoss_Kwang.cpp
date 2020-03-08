// Fill out your copyright notice in the Description page of Project Settings.


#include "ARPGBoss_Kwang.h"
#include "ARPGCharacter.h"
#include "Engine.h"
#include "Runtime/Engine/Classes/Kismet/KismetMathLibrary.h"

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
