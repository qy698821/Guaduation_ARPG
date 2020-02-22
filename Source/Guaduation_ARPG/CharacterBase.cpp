// Fill out your copyright notice in the Description page of Project Settings.


#include "CharacterBase.h"
#include "Engine.h"

// Sets default values
ACharacterBase::ACharacterBase()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ACharacterBase::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ACharacterBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ACharacterBase::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void ACharacterBase::ReduceHp(float Damage)
{
	if (UnrealReduceTier.IsValid())
	{
		GetWorld()->GetTimerManager().ClearTimer(UnrealReduceTier);
	}
	UnrealHP = HP;
	if (HP - Damage >= 0.0f)
	{
		HP -= Damage;
		GetWorld()->GetTimerManager().SetTimer(UnrealReduceTier, this, &ACharacterBase::ReduceHpByTimer, 0.02f, true, -1.0f);
	}
	else
	{
		HP = 0;
		GetWorld()->GetTimerManager().SetTimer(UnrealReduceTier, this, &ACharacterBase::ReduceHpByTimer, 0.02f, true, -1.0f);
	}
}

void ACharacterBase::ReduceHpByTimer()
{
	UnrealHP -= MaxHP * 0.01f;
	if (UnrealHP <= HP)
	{
		UnrealHP = HP;
		if (UnrealReduceTier.IsValid())
		{
			GetWorld()->GetTimerManager().ClearTimer(UnrealReduceTier);
		}
	}
}

