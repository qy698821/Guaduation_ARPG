﻿// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Camera/CameraComponent.h"
#include "Engine/DataTable.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/Character.h"
#include "EnemyBase.h"
#include "Task_1Actor.h"
#include "ARPGCharacter.generated.h"

//Inventory item attribute
USTRUCT(BlueprintType)
struct FInventoryItem : public FTableRowBase 
{
	GENERATED_BODY()

public:
	FInventoryItem() 
	{
		ItemID = TEXT("请输入ID");
		Description = TEXT("请描述该物品");
		Number = 1;
	}

	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	FName ItemID;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString Name;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString Action;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<class APickUp> PickUpClass;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UTexture2D* Thumbnail;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float Value;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int Number;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float Cost;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString Description;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool CanBeUse;

};


UCLASS()
class GUADUATION_ARPG_API AARPGCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AARPGCharacter();


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	//AddCameraComponent
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		UCameraComponent* ARPGCamera;

	//AddCameraSpringArm
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		USpringArmComponent* ARPGSpringArm;

	///Character attribute
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Character attribute")
		float HP = 100.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Character attribute")
		float MaxHP = 100.0f;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Character attribute")
		float UnrealHP = 0.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Character attribute")
		float AttackPower = 10.0f;

	UPROPERTY(BlueprintReadWrite, Category = "Character attribute")
		float AttackValue = 0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Character attribute")
		float Defense = 10.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Character attribute")
		float Money = 0.0f;

	UPROPERTY(BlueprintReadWrite, Category = "Character attribute")
		float Exp = 0.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Character attribute")
		float AttackSpeed = 0.8f;

	///End

	///////Damaged////////

	UPROPERTY(BlueprintReadWrite)
		bool IsDamaged = false;

	UFUNCTION(BlueprintCallable)
		void Damaged(AActor* Attacker, float Damage);

	float GetAttackAngle(AActor* Attacker);

	void PlayDamageMontage(float angle);

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Attack Montage")
		UAnimMontage* DeathMontage = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Damaged Montage")
		UAnimMontage* HitReactBwd = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Damaged Montage")
		UAnimMontage* HitReactFwd = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Damaged Montage")
		UAnimMontage* HitReactLeft = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Damaged Montage")
		UAnimMontage* HitReactRight = nullptr;

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
		void OpenDeathWidget();
	/////end/////
	///HpBar

	  //The Increment Of HP
	float IncrementOfHp = 0.0f;

	UFUNCTION(BlueprintCallable)
		void ReduceHp(float Damage);

	UFUNCTION(BlueprintCallable)
		void AddHp(float Value);

	FTimerHandle UnrealReduceTier;

	void ReduceHpByTimer();

	FTimerHandle HpAddTimer;

	void AddHpByTimer();

	///End


	///Attack Montage

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Attack Montage")
		UAnimMontage* FastAttack1 = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Attack Montage")
		UAnimMontage* FastAttack2 = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Attack Montage")
		UAnimMontage* FastAttack3 = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Attack Montage")
		UAnimMontage* StrongAttack1 = nullptr;

	//Turn speed when attack
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Attack Montage")
		float AttackTurnSpeed = 8.0f;
	///End

	///Cost Function
	UFUNCTION(BlueprintCallable)
		bool BuyObject(float Cost);

	///Attack Sound

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Attack Sound")
		USoundWave* FastAttackSound1 = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Attack Sound")
		USoundWave* FastAttackSound2 = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Attack Sound")
		USoundWave* FastAttackSound3 = nullptr;

	///End

	//Bind FastAttack Action
	void OnFastAttack();

	///Character Attack

	UPROPERTY(EditAnywhere)
		bool IsAttacking = false;

	UPROPERTY(EditAnywhere)
		bool SaveAttack = false;

	int FastAttackCount = 0;

	

	//Combo System
	UFUNCTION(BlueprintCallable)
		void ResetCombo();

	UFUNCTION(BlueprintCallable)
		void ComboAttackSave();

	

	///End

	/// Lock enemy system

	TMap<AEnemyBase*, float> Enemies;

	//The abs of defference value
	TArray<float> CenterRotation;

	AEnemyBase* CurrentEnemy;

	bool IsLocked = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Lock System")
		TArray<TEnumAsByte<EObjectTypeQuery> > ObjectTypes;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Lock System")
		float MaxLockDistance = 1500.0f;

	//Camera turn speed when Lock
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Lock System")
		float LockTurnSpeed = 15.0f;

	bool LineOfSightCheck(AActor* OtherActor);

	bool GetAllEnemys();

	//Bind action
	void LockEnemy();

	//Begin Lock
	void LockOn(AEnemyBase* Target);

	//Remove Lock
	void LockOff();

	void SetCameraRotation(float DeltaTime);

	//Bind Switch Action
	void Switch(int value);
	///End

	//////Task System//////

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "TaskSystem")
		ATask_1Actor* Task1;

	//////END//////

	/////skill/////
	UPROPERTY(BlueprintReadWrite, Category = "Skill")
		bool StudyDodge = false;

	UPROPERTY(BlueprintReadWrite, Category = "Skill")
		bool StudySuckingBlood = false;

	UPROPERTY(BlueprintReadWrite, Category = "Skill")
		bool StudyMaxHP = false;

	UPROPERTY(BlueprintReadWrite, Category = "Skill")
		bool OpenSuckingBlood = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "SuckingBlood")
		float SuckingBloodCD = 7.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "SuckingBlood")
		float StayTime = 5.0f;

	UPROPERTY(BlueprintReadWrite, Category = "SuckingBlood")
		bool CDOver = true;
	/////END///////

	//////// Dodge  ///////

	UPROPERTY(BlueprintReadWrite, Category = "Dodge")
		bool IsStartDodge = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Dodge")
		UAnimMontage* DodgeMontage = nullptr;

	UFUNCTION(BlueprintCallable)
		void StartDodge();

	void Dodge(float forward, float right);

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Dodge")
		float DodgeCD = 2.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Dodge")
		float DodgeSpeed = 2.0f;

	float CurrentDodgeCD = 0.0f;

	FTimerHandle ResetDodgeCDByTimer;

	void ResetDodgeCD();

	TArray<float > DodgeDirection;

	FRotator DodgeRotation;
	FVector DodgeLocation;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Dodge")
		float DodgeTime = 0.5f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Dodge")
		float DodgeLength = 30.0f;

	float CurrentDodgeTime = 0.0f;

	void DodgeMove();

	FTimerHandle DodgeMoveTimer;

	/////// END //////////
};
