// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "CharacterBase.generated.h"

UCLASS()
class GUADUATION_ARPG_API ACharacterBase : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ACharacterBase();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;


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

	UFUNCTION(BlueprintCallable)
		void ReduceHp(float Damage);

	FTimerHandle UnrealReduceTier;

	void ReduceHpByTimer();

	///End

};
