// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "EnemyBase.h"
#include "BehaviorTree/BehaviorTree.h"
#include "Blueprint/UserWidget.h"
#include "ARPGBoss_Kwang.generated.h"

/**
 * 
 */
enum AtributeCD 
{
	FASTATTACK,
	SWEEPATTACK,
	REMOTEATTACT,
	CHANGEDSTEP,
	SUPPERSWEEP
};
UCLASS()
class GUADUATION_ARPG_API AARPGBoss_Kwang : public AEnemyBase
{
	GENERATED_BODY()

protected:
	virtual void BeginPlay() override;

public:
	AARPGBoss_Kwang();

	virtual void Locked(ACharacter* CharacterPtr) override;

	virtual void LockOff() override;

	virtual void LockTick() override;

	virtual void Tick(float DeltaTime) override;

	virtual	void Damaged(AActor* Attacker, float Damage) override;

	//Boss Hp ui
	UPROPERTY(BlueprintReadWrite)
		UUserWidget* BOSSHpBarWidget = nullptr;

	virtual void DestoryByTimer() override;

	//Behavior tree
	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	class UBehaviorTree* BehaviorTree;

	//set black board isstart?
	UFUNCTION(BlueprintCallable)
		void Start_Boss_Battle();

	void ChangeMoveStatus();

	AActor* CurrentPlayer = nullptr;

	//AI attribute
	bool IsDied = false;
	bool IsAttack = false;
	bool IsDamaged = false;
	bool IsSuperArmor = false;
	bool IsStep2 = false;
	bool IsChanged = false;

	//////////////Skill 1 Fast attack
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "FastAttack")
		UAnimMontage* FastAttack1 = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "FastAttack")
		UAnimMontage* FastAttack2 = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "FastAttack")
		UAnimMontage* FastAttack3 = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "FastAttack")
		UAnimMontage* FastAttack3Step2 = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "FastAttack")
		UAnimMontage* FastAttack4 = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "DistanceJudgement")
		float DistanceJudX = 800.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "DistanceJudgement")
		float DistanceJudY = 200.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "FastAttack")
		float FastAttackValue = 20.0f;

	//Combo System
	UFUNCTION(BlueprintCallable)
		void ResetCombo();

	UFUNCTION(BlueprintCallable)
		void ComboAttackSave();
	int FastAttackCount = 0;

	
	void OnFastAttack();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "FastAttack")
		float MaxFastAttackCD = 6.0f;

	float FastAttackCD = 6.0f;

	FTimerHandle ResetFastAttackCDByTimer;

	void ResetFastAttackCD();

	//////////////Skill 2 Sweep attack

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "SweepAttack")
		UAnimMontage* SweepAttack = nullptr;
	
	void OnSweepAttack();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "SweepAttack")
		float MaxSweepAttackCD = 6.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "SweepAttack")
		float SweepAttackValue = 20.0f;

	float SweepAttackCD = 6.0f;

	FTimerHandle ResetSweepAttackCDByTimer;

	void ResetCD(AtributeCD CDName);

	void ResetSweepAttackCD();

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FVector SprintDeltaVector;

	UFUNCTION(BlueprintCallable)
		void SprintToPlayer();

	//////////////Skill 3 Remote attack
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "RemoteAttack")
		UAnimMontage* RemoteAttack = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "RemoteAttack")
		UAnimMontage* RemoteAttack2 = nullptr;

	void OnRemoteAttack();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "RemoteAttack")
		float MaxRemoteAttackCD = 6.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "RemoteAttack")
		float RemoteAttackValue = 20.0f;

	float RemoteAttackCD = 6.0f;

	FTimerHandle ResetRemoteAttackCDByTimer;

	void ResetRemoteAttackCD();

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FVector RemoteTargetVector;

	//////////////Skill 4 ChangedStep

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ChangedStep")
		UAnimMontage* ChangedStep = nullptr;

	void OnChangedStep();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ChangedStep")
		float MaxChangedStepCD = 6.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ChangedStep")
		float ChangeStepValue = 20.0f;

	float ChangedStepCD = 6.0f;

	FTimerHandle ResetChangedStepCDByTimer;

	void ResetChangedStepCD();

	//////////////Skill 5 SupperSweep

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "SupperSweep")
		UAnimMontage* SupperSweep = nullptr;

	void OnSupperSweep();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "SupperSweep")
		float MaxSupperSweepCD = 6.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "SupperSweep")
		float SupperSweepValue = 6.0f;

	float SupperSweepCD = 6.0f;

	FTimerHandle ResetSupperSweepCDByTimer;

	void ResetSupperSweepCD();

};
