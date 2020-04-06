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
	SweepAttackCD = MaxSweepAttackCD;

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
		FName CanMove = "CanMove";
		Ptr->BBComponent->SetValueAsBool(IsStart, true);
		Ptr->BBComponent->SetValueAsBool(CanMove, true);
		Ptr->BBComponent->SetValueAsObject(FName("Player"), UGameplayStatics::GetPlayerController(GWorld, 0)->GetCharacter());
		CurrentPlayer = UGameplayStatics::GetPlayerController(GWorld, 0)->GetCharacter();
	}
}

void AARPGBoss_Kwang::ChangeMoveStatus()
{
	ABoss_KwangAIController* Ptr = Cast<ABoss_KwangAIController>(this->GetController());
	if (Ptr) 
	{
		float Distance = GetDistanceTo(CurrentPlayer);
		FName CanMove = "CanMove";
		if (SweepAttackCD >= MaxSweepAttackCD && Distance > DistanceJudY && Distance <= DistanceJudX)
		{
			Ptr->BBComponent->SetValueAsBool(CanMove, false);
			return;
		}
	}
}

void AARPGBoss_Kwang::OnFastAttack()
{
	if (IsAttack) 
	{

	}
	else 
	{
		IsAttack = true;
		FastAttackCount = 1;
		this->PlayAnimMontage(FastAttack1, AttackSpeed);
	}

}

void AARPGBoss_Kwang::OnSweepAttack()
{
	if (IsStep2) 
	{

	}
	else 
	{
		if (IsAttack)
		{

		}
		else
		{
			IsSuperArmor = true;
			IsAttack = true;
			this->PlayAnimMontage(SweepAttack, AttackSpeed);
			SweepAttackCD = 0.0f;
			ResetCD(AtributeCD::SWEEPATTACK);

		}
	}
}

void AARPGBoss_Kwang::ResetCD(AtributeCD CDName)
{
	switch (CDName) 
	{
	case FASTATTACK:
		break;
	case SWEEPATTACK:
		GetWorld()->GetTimerManager().SetTimer(ResetSweepAttackCDByTimer, this, &AARPGBoss_Kwang::ResetSweepAttackCD, 0.1f, true, -1);
	}
}

void AARPGBoss_Kwang::ResetSweepAttackCD()
{
	if (SweepAttackCD < MaxSweepAttackCD) 
	{
		SweepAttackCD += 0.1f;
	}
	else 
	{
		SweepAttackCD = MaxSweepAttackCD;
		if (ResetSweepAttackCDByTimer.IsValid()) 
		{
			GetWorld()->GetTimerManager().ClearTimer(ResetSweepAttackCDByTimer);
		}
	}
}

void AARPGBoss_Kwang::SprintToPlayer()
{
	AddActorWorldOffset(SprintDeltaVector);
}

void AARPGBoss_Kwang::ResetCombo()
{
	//this->GetCharacterMovement()->MaxWalkSpeed = 600.0f;
	FastAttackCount = 0;

	//face to player
	float DeltaTime = GetWorld()->GetDeltaSeconds();
	FRotator Start = this->GetController()->GetControlRotation();
	FRotator End;
	End.Roll = Start.Roll;
	End.Pitch = UKismetMathLibrary::FindLookAtRotation(this->GetActorLocation(), CurrentPlayer->GetActorLocation()).Pitch;
	End.Yaw = UKismetMathLibrary::FindLookAtRotation(GetActorLocation(), CurrentPlayer->GetActorLocation()).Yaw;
	this->SetActorRelativeRotation(End);
	ABoss_KwangAIController* Ptr = Cast<ABoss_KwangAIController>(this->GetController());
	if (Ptr)
	{
		FName CanMove = "CanMove";
		Ptr->BBComponent->SetValueAsBool(CanMove, true);
	}
	IsAttack = false;
	IsSuperArmor = false;
}

void AARPGBoss_Kwang::ComboAttackSave()
{
	//Exchange Combo
	if (IsAttack) 
	{
		if (FastAttackCount == 0)
		{
			FastAttackCount = 1;
			this->PlayAnimMontage(FastAttack1, AttackSpeed);
			//UGameplayStatics::PlaySound2D(GetWorld(), FastAttackSound1);
		}
		else if (FastAttackCount == 1)
		{
			FastAttackCount = 2;
			this->PlayAnimMontage(FastAttack2, AttackSpeed);
			//UGameplayStatics::PlaySound2D(GetWorld(), FastAttackSound2);
		}
		else if (FastAttackCount == 2)
		{
			if (IsStep2)
			{
				FastAttackCount = 3;
				this->PlayAnimMontage(FastAttack3Step2, AttackSpeed);
				//UGameplayStatics::PlaySound2D(GetWorld(), FastAttackSound3);
			}
			else
			{
				FastAttackCount = 0;
				this->PlayAnimMontage(FastAttack3, AttackSpeed);
				//UGameplayStatics::PlaySound2D(GetWorld(), FastAttackSound3);
				//ResetCombo();
			}
		}
		else if (FastAttackCount == 3)
		{
			FastAttackCount = 0;
			this->PlayAnimMontage(FastAttack4, AttackSpeed);
			//UGameplayStatics::PlaySound2D(GetWorld(), FastAttackSound3);
			//ResetCombo();
		}
	}
}

void AARPGBoss_Kwang::Damaged(AActor* Attacker, float Damage) 
{
	PlayDamageMontage(GetAttackAngle(Attacker));
	ReduceHp(Damage);
	if (HP <= MaxHP / 2) 
	{
		IsStep2 = true;
	}
}

