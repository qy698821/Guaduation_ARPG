// Fill out your copyright notice in the Description page of Project Settings.


#include "ARPGCharacter.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Engine.h"

// Sets default values
AARPGCharacter::AARPGCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	ARPGCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("ARPGCamera"));
	ARPGSpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("ARPGSpringArm"));

	MyWalkSpeed = GetCharacterMovement()->MaxWalkSpeed;
	ARPGSpringArm->SetupAttachment(RootComponent);
	ARPGCamera->SetupAttachment(ARPGSpringArm, USpringArmComponent::SocketName);
}

// Called when the game starts or when spawned
void AARPGCharacter::BeginPlay()
{
	Super::BeginPlay();
	UnrealHP = HP;
	
}

// Called every frame
void AARPGCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AARPGCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void AARPGCharacter::ReduceHp(float Damage)
{
	if (UnrealReduceTier.IsValid())
	{
		GetWorld()->GetTimerManager().ClearTimer(UnrealReduceTier);
	}
	UnrealHP = HP;
	if (HP - Damage >= 0.0f) 
	{
		HP -= Damage;
		GetWorld()->GetTimerManager().SetTimer(UnrealReduceTier, this, &AARPGCharacter::ReduceHpByTimer, 0.02f, true, -1.0f);
	}
	else 
	{
		HP = 0;
		GetWorld()->GetTimerManager().SetTimer(UnrealReduceTier, this, &AARPGCharacter::ReduceHpByTimer, 0.02f, true, -1.0f);
	}
}

void AARPGCharacter::ReduceHpByTimer()
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

void AARPGCharacter::AddHp(float Value)
{

	IncrementOfHp += Value;

	if (HP + Value > MaxHP) 
	{
		IncrementOfHp = MaxHP - HP;
	}
	if (!HpAddTimer.IsValid()) 
	{
		GetWorld()->GetTimerManager().SetTimer(HpAddTimer, this, &AARPGCharacter::AddHpByTimer, 0.02f, true, -1.0f);
	}
}


void AARPGCharacter::AddHpByTimer()
{
	if (IncrementOfHp <= 0.0f)
	{
		IncrementOfHp = 0.0f;
		if (HpAddTimer.IsValid())
		{
			GetWorld()->GetTimerManager().ClearTimer(HpAddTimer);
		}
	}
	else 
	{
		HP += MaxHP * 0.01f;
		IncrementOfHp -= MaxHP * 0.01f;
	}
}

void AARPGCharacter::OnFastAttack()
{
	if (IsAttacking) 
	{
		SaveAttack = true;
	}
	else 
	{
		IsAttacking = true;

		//stop move
		//GetCharacterMovement()->MaxWalkSpeed = 0.0f;

		if (FastAttackCount == 0) 
		{
			FastAttackCount = 1;
			this->PlayAnimMontage(FastAttack1, AttackSpeed);
		}
		else if (FastAttackCount == 1) 
		{
			FastAttackCount = 2;
			this->PlayAnimMontage(FastAttack2, AttackSpeed);
		}
		else if (FastAttackCount == 2)
		{
			FastAttackCount = 0;
			this->PlayAnimMontage(FastAttack3, AttackSpeed);
		}
	}
}

void AARPGCharacter::ResetCombo()
{
	//this->GetCharacterMovement()->MaxWalkSpeed = 600.0f;
	FastAttackCount = 0;
	IsAttacking = false;
	SaveAttack = false;
}

void AARPGCharacter::ComboAttackSave()
{
	if (SaveAttack) 
	{
		SaveAttack = false;
		//Exchange Combo
		if (FastAttackCount == 0)
		{
			FastAttackCount = 1;
			this->PlayAnimMontage(FastAttack1, AttackSpeed);
		}
		else if (FastAttackCount == 1)
		{
			FastAttackCount = 2;
			this->PlayAnimMontage(FastAttack2, AttackSpeed);
		}
		else if (FastAttackCount == 2)
		{
			FastAttackCount = 0;
			this->PlayAnimMontage(FastAttack3, AttackSpeed);
		}

	}
}

