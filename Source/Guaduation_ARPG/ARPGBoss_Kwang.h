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
UCLASS()
class GUADUATION_ARPG_API AARPGBoss_Kwang : public AEnemyBase
{
	GENERATED_BODY()

public:
	AARPGBoss_Kwang();

	virtual void Locked(ACharacter* CharacterPtr) override;

	virtual void LockOff() override;

	virtual void LockTick() override;

	virtual void Tick(float DeltaTime) override;

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

	AActor* CurrentPlayer = nullptr;

	//AI attribute
	bool IsDied = false;
	bool IsAttack = false;
	bool IsDamaged = false;
	bool IsSuperArmor = false;
	bool IsStep2 = false;

	//////////////Skill 1 Fast attack
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "FastAttack")
		UAnimMontage* FastAttack1 = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "FastAttack")
		UAnimMontage* FastAttack2 = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "FastAttack")
		UAnimMontage* FastAttack3 = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "FastAttack")
		UAnimMontage* FastAttack4 = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "DistanceJudgement")
		float DistanceJudX = 800.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "DistanceJudgement")
		float DistanceJudY = 200.0f;
	//Combo System
	UFUNCTION(BlueprintCallable)
		void ResetCombo();

	UFUNCTION(BlueprintCallable)
		void ComboAttackSave();
	int FastAttackCount = 0;

	
	void OnFastAttack();

	//////////////Skill 2 Sweep attack

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "SweepAttack")
		UAnimMontage* SweepAttack = nullptr;
	
	void OnSweepAttack();

	
};
