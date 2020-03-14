// Fill out your copyright notice in the Description page of Project Settings.


#include "CharacterBase.h"
#include "Runtime/Engine/Classes/Kismet/GameplayStatics.h"
#include "Runtime/Engine/Classes/Kismet/KismetMathLibrary.h"
#include "Engine.h"
#include "ARPGCharacter.h"

// Sets default values
ACharacterBase::ACharacterBase()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	//GEngine->AddOnScreenDebugMessage(-1, 3.0f, FColor::Blue, FString::Printf(TEXT("11111")));

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
	//Death
	else
	{
		HP = 0;
		GetWorld()->GetTimerManager().SetTimer(UnrealReduceTier, this, &ACharacterBase::ReduceHpByTimer, 0.02f, true, -1.0f);
		if (!DeathTimer.IsValid()) 
		{
			AARPGCharacter* Ptr = Cast<AARPGCharacter>(UGameplayStatics::GetPlayerController(GWorld, 0)->GetCharacter());
			//Reset lock
			if (Ptr) 
			{
				Ptr->LockOff();
			}
			this->PlayAnimMontage(DeathMontage, 1.0f);
			UGameplayStatics::PlaySound2D(GetWorld(), DeathSound);
			GetWorld()->GetTimerManager().SetTimer(DeathTimer, this, &ACharacterBase::DestoryByTimer, 2.0, false, 1.5f);
		}
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

void ACharacterBase::Damaged(AActor * Attacker, float Damage)
{
	PlayDamageMontage(GetAttackAngle(Attacker));
	ReduceHp(Damage);
}

float ACharacterBase::GetAttackAngle(AActor * Attacker)
{
	FRotator AtoB = UKismetMathLibrary::FindLookAtRotation(this->GetActorLocation(), Attacker->GetActorLocation());
	UKismetMathLibrary::NormalizedDeltaRotator(AtoB, this->GetActorRotation());
	return UKismetMathLibrary::NormalizedDeltaRotator(AtoB, this->GetActorRotation()).Yaw;
}

void ACharacterBase::PlayDamageMontage(float angle)
{
	if (angle < 0.0f) 
	{
		angle += 360.0f;
	}
	if (angle >= 315.0f || angle < 45.0f) 
	{
		PlayAnimMontage(HitReactFwd, 1.8f);
	}
	else if (angle >= 45.0f && angle < 135.0f) 
	{
		PlayAnimMontage(HitReactRight, 1.8f);
	}
	else if (angle >= 135.0f && angle < 225.0f) 
	{
		PlayAnimMontage(HitReactBwd, 1.8f);
	}
	else if (angle >= 225.0f && angle < 315.0f) 
	{
		PlayAnimMontage(HitReactLeft, 1.8f);
	}
	//GEngine->AddOnScreenDebugMessage(-1, 3.0f, FColor::Blue, FString::Printf(TEXT("%f"), angle));
}

void ACharacterBase::DestoryByTimer() 
{
	//this->Destroyed();
	this->Destroy();
}
