// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Camera/CameraComponent.h"
#include "Engine/DataTable.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/Character.h"
#include "EnemyBase.h"
#include "ARPGCharacter.generated.h"

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
		float HP = 1000.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Character attribute")
		float MaxHP = 1000.0f;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Character attribute")
		float UnrealHP = 0.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Character attribute")
		float AttackPower = 10.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Character attribute")
		float Defense = 10.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Character attribute")
		float AttackSpeed = 0.8f;

	///End


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

	///End

	//Bind FastAttack Action
	void OnFastAttack();

	///Character Attack

	UPROPERTY(EditAnywhere)
		bool IsAttacking = false;

	UPROPERTY(EditAnywhere)
		bool SaveAttack = false;

	int FastAttackCount = 0;

	//Record Walk speed before attack
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Attack Montage")
	float MyWalkSpeed = 0.0f;

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

	bool LineOfSightCheck(AActor* OtherActor);

	bool GetAllEnemys();

	//Bind action
	void LockEnemy();

	//Begin Lock
	void LockOn(AEnemyBase* Target);

	//Remove Lock
	void LockOff();

	void SetCameraRotation(float DeltaTime);
	///End
};
