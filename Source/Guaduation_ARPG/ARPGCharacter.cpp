// Fill out your copyright notice in the Description page of Project Settings.

#include "ARPGCharacter.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Engine.h"
#include "Runtime/Engine/Classes/Kismet/GameplayStatics.h"
#include "Runtime/Engine/Classes/Kismet/KismetMathLibrary.h"
#include "Kismet/KismetSystemLibrary.h"

// Sets default values
AARPGCharacter::AARPGCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	ARPGCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("ARPGCamera"));
	ARPGSpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("ARPGSpringArm"));

	ARPGSpringArm->SetupAttachment(RootComponent);
	ARPGCamera->SetupAttachment(ARPGSpringArm, USpringArmComponent::SocketName);

	ObjectTypes.Add(ObjectTypeQuery1);
	ObjectTypes.Add(ObjectTypeQuery2);
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
	if (IsLocked) 
	{
		SetCameraRotation(DeltaTime);
	}

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

	if (HP + IncrementOfHp > MaxHP)
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

bool AARPGCharacter::BuyObject(float Cost)
{
	if (Money >= Cost) 
	{
		Money -= Cost;
		return true;
	}
	return false;
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
			UGameplayStatics::PlaySound2D(GetWorld(), FastAttackSound1);
		}
		else if (FastAttackCount == 1) 
		{
			FastAttackCount = 2;
			this->PlayAnimMontage(FastAttack2, AttackSpeed);
			UGameplayStatics::PlaySound2D(GetWorld(), FastAttackSound2);
		}
		else if (FastAttackCount == 2)
		{
			FastAttackCount = 0;
			this->PlayAnimMontage(FastAttack3, AttackSpeed);
			UGameplayStatics::PlaySound2D(GetWorld(), FastAttackSound3);
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
			UGameplayStatics::PlaySound2D(GetWorld(), FastAttackSound1);
		}
		else if (FastAttackCount == 1)
		{
			FastAttackCount = 2;
			this->PlayAnimMontage(FastAttack2, AttackSpeed);
			UGameplayStatics::PlaySound2D(GetWorld(), FastAttackSound2);
		}
		else if (FastAttackCount == 2)
		{
			FastAttackCount = 0;
			this->PlayAnimMontage(FastAttack3, AttackSpeed);
			UGameplayStatics::PlaySound2D(GetWorld(), FastAttackSound3);
		}

	}
}

bool AARPGCharacter::LineOfSightCheck(AActor * OtherActor)
{
	TArray<AActor*> ActorsToIgnore;
	FHitResult Hit;
	return !UKismetSystemLibrary::LineTraceSingleForObjects(GetWorld(), ARPGCamera->GetComponentLocation(), OtherActor->GetActorLocation(), ObjectTypes, false, ActorsToIgnore, EDrawDebugTrace::None, Hit, true, FLinearColor::Red, FLinearColor::Green, 3.0f);
}

bool AARPGCharacter::GetAllEnemys()
{
	//clear all
	Enemies.Empty();
	CenterRotation.Empty();

	TArray<AActor*> OutArray;
	TMap<AEnemyBase*, float> LocalEnemies;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AEnemyBase::StaticClass(), OutArray);
	for (auto& n : OutArray) 
	{
		//Check if in the range of distace and if blocked
		if (GetDistanceTo(n) <= MaxLockDistance && LineOfSightCheck(n))
		{
			//Get the difference value of target and self
			FRotator FromTarget = UKismetMathLibrary::FindLookAtRotation(ARPGCamera->GetComponentLocation(), n->GetActorLocation());
			FRotator FromSelf = UKismetMathLibrary::FindLookAtRotation(ARPGCamera->GetComponentLocation(), this->GetActorLocation());

			//GEngine->AddOnScreenDebugMessage(-1, 3.0f, FColor::Blue, FString::Printf(TEXT("%f"), FromTarget.Yaw - FromSelf.Yaw));
			AEnemyBase* Ptr = Cast<AEnemyBase>(n);
			if (Ptr && (fabs(FromTarget.Yaw - FromSelf.Yaw) <= 50.0f || fabs(FromTarget.Yaw - FromSelf.Yaw) >= 310.0f))
			{
				LocalEnemies.Add(Ptr, FromTarget.Yaw - FromSelf.Yaw);
			}
		}
	}
	TArray<float> LocalEnemiesValues;
	TArray<AEnemyBase*> LocalEnemiseKey;
	//Sort
	while (LocalEnemies.Num() > 0) 
	{
		LocalEnemies.GenerateValueArray(LocalEnemiesValues);
		LocalEnemies.GenerateKeyArray(LocalEnemiseKey);
		int MinIndex = 0;
		float MinValue = 0.0f;
		UKismetMathLibrary::MinOfFloatArray(LocalEnemiesValues, MinIndex, MinValue);

		Enemies.Add(LocalEnemiseKey[MinIndex], LocalEnemiesValues[MinIndex]);
		CenterRotation.Add(GetDistanceTo(LocalEnemiseKey[MinIndex]));

		LocalEnemies.Remove(LocalEnemiseKey[MinIndex]);

	}
	if (Enemies.Num() > 0) 
	{
		return true;
	}
	else 
	{
		return false;
	}
}

void AARPGCharacter::LockEnemy()
{
	if (!IsLocked) 
	{
		//Prepare for Lock
		if (GetAllEnemys()) 
		{
			int MinIndex = 0;
			float MinValue = 0.0f;
			TArray<AEnemyBase* > EnemiesKeyArray;
			TArray<TEnumAsByte<EObjectTypeQuery> > ObjectTypesSelf;
			ObjectTypesSelf.Add(ObjectTypeQuery7);
			TArray<AActor*> ActorsToIgnore;
			FHitResult Hit;

			UKismetMathLibrary::MinOfFloatArray(CenterRotation, MinIndex, MinValue);
			Enemies.GenerateKeyArray(EnemiesKeyArray);
			ActorsToIgnore.Add(EnemiesKeyArray[MinIndex]);
			if (UKismetSystemLibrary::SphereTraceSingleForObjects(GetWorld(), this->GetActorLocation(), EnemiesKeyArray[MinIndex]->GetActorLocation(), 20.0f, ObjectTypesSelf, false, ActorsToIgnore, EDrawDebugTrace::None, Hit, true, FLinearColor::Red, FLinearColor::Green, 3.0f)) 
			{
				AEnemyBase* Ptr = Cast<AEnemyBase>(Hit.Actor);
				if (Ptr) 
				{
					LockOn(Ptr);
				}
			}
			else 
			{
				LockOn(EnemiesKeyArray[MinIndex]);
			}
		}
	}
	else 
	{
		//Remove Lock
		LockOff();
	}
}

//Lock Enemy
void AARPGCharacter::LockOn(AEnemyBase * Target)
{
	IsLocked = true;
	CurrentEnemy = Target;
	CurrentEnemy->Locked(this);
}

//Release Lock
void AARPGCharacter::LockOff()
{
	IsLocked = false;
	if (CurrentEnemy) 
	{
		CurrentEnemy->LockOff();
	}
}

void AARPGCharacter::SetCameraRotation(float DeltaTime)
{
	FRotator Start = this->GetController()->GetControlRotation();
	FRotator End;
	End.Roll = Start.Roll;
	End.Pitch = UKismetMathLibrary::FindLookAtRotation(ARPGCamera->GetComponentLocation(), CurrentEnemy->GetActorLocation()).Pitch;
	End.Yaw = UKismetMathLibrary::FindLookAtRotation(ARPGCamera->GetComponentLocation(), CurrentEnemy->GetActorLocation()).Yaw;
	this->GetController()->SetControlRotation(UKismetMathLibrary::RInterpTo(Start, End, DeltaTime, LockTurnSpeed));

	if (!(GetDistanceTo(CurrentEnemy) <= MaxLockDistance && LineOfSightCheck(CurrentEnemy)))
	{
		LockOff();
	}
}

void AARPGCharacter::Switch(int value)
{
	if (IsLocked) 
	{
		if (GetAllEnemys() && Enemies.Num() > 1) 
		{
			int CurrentIndex = 0;
			TArray<AEnemyBase*> LocalEnemiseKey;
			Enemies.GenerateKeyArray(LocalEnemiseKey);
			LocalEnemiseKey.Find(CurrentEnemy, CurrentIndex);
			//Switch Left
			if (value == 0) 
			{
				if (CurrentIndex == 0) 
				{
					CurrentIndex = LocalEnemiseKey.Num() - 1;
				}
				else 
				{
					CurrentIndex -= 1;
				}
			}
			//Switch Right
			else 
			{
				if (CurrentIndex == LocalEnemiseKey.Num() - 1) 
				{
					CurrentIndex = 0;
				}
				else 
				{
					CurrentIndex += 1;
				}
			}
			LockOff();
			LockOn(LocalEnemiseKey[CurrentIndex]);
		}
	}
}
