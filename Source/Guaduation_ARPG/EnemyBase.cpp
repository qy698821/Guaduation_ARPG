// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyBase.h"
#include "UObject/ConstructorHelpers.h" 
#include "ARPGCharacter.h"
#include "Engine.h"
#include "Runtime/Engine/Classes/Kismet/KismetMathLibrary.h"
#include "Components/CapsuleComponent.h"

AEnemyBase::AEnemyBase() 
{
	PrimaryActorTick.bCanEverTick = true;
	LockTarget = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("LockTarget"));
	LockTarget->SetupAttachment(RootComponent);

	HpWidget = CreateDefaultSubobject<UWidgetComponent>(TEXT("HpWidget"));
	HpWidget->SetupAttachment(RootComponent);

	//LockTarget Attribute
	static ConstructorHelpers::FObjectFinder<UStaticMesh> ObjectFinder(TEXT("StaticMesh'/Engine/BasicShapes/Cone.Cone'"));
	if (ObjectFinder.Succeeded()) 
	{
		LockTarget->SetStaticMesh(ObjectFinder.Object);
	}

	LockTarget->SetRelativeLocation(FVector(0.0f, 0.0f, 130.0f));
	LockTarget->SetRelativeRotation(FRotator(0.0f, 0.0f, 180.0f));
	LockTarget->SetRelativeScale3D(FVector(0.3f, 0.3f, 0.3f));
	LockTarget->bVisible = false;
	LockTarget->SetCollisionProfileName(TEXT("NoCollision"));

	//HpWidget attribute
	HpWidget->SetCollisionProfileName(TEXT("NoCollision"));
	HpWidget->SetRelativeLocation(FVector(0.0f, 0.0f, 100.0f));
	HpWidget->bVisible = false;
	HpWidget->SetDrawSize(FVector2D(100,10));
	//HpWidget->bHiddenInGame = true;

	UCapsuleComponent* Ptr = Cast<UCapsuleComponent>(RootComponent);
	if (Ptr) 
	{
		Ptr->SetCollisionProfileName(TEXT("Enemy"));
	}
}

void AEnemyBase::Locked(ACharacter* CharacterPtr)
{
	IsLocked = true;
	LocalCharacter = CharacterPtr;
	HpWidget->SetVisibility(true, false);
	//HpWidget->SetHiddenInGame(false, false);
	LockTarget->SetVisibility(true, false);
}

void AEnemyBase::LockOff()
{
	IsLocked = false;
	HpWidget->SetVisibility(false, false);
	//HpWidget->SetHiddenInGame(true, false);
	LockTarget->SetVisibility(false, false);
	LocalCharacter = nullptr;
}

void AEnemyBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	//Set hp widget face to player
	if (IsLocked) 
	{
		AARPGCharacter* Ptr = Cast<AARPGCharacter>(LocalCharacter);
		if (Ptr) 
		{
			FRotator Start = HpWidget->GetComponentRotation();
			FRotator End;
			End.Roll = Start.Roll;
			End.Pitch = Start.Pitch;
			End.Yaw = UKismetMathLibrary::FindLookAtRotation(HpWidget->GetComponentLocation(), Ptr->ARPGCamera->GetComponentLocation()).Yaw;
			HpWidget->SetRelativeRotation(End);
		}
	}

}