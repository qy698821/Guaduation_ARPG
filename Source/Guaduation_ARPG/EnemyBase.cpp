// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyBase.h"
#include "UObject/ConstructorHelpers.h" 
#include "Components/CapsuleComponent.h"

AEnemyBase::AEnemyBase() 
{
	LockTarget = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("LockTarget"));
	LockTarget->SetupAttachment(RootComponent);

	static ConstructorHelpers::FObjectFinder<UStaticMesh> ObjectFinder(TEXT("StaticMesh'/Engine/BasicShapes/Cone.Cone'"));
	if (ObjectFinder.Succeeded()) 
	{
		LockTarget->SetStaticMesh(ObjectFinder.Object);
	}

	LockTarget->SetRelativeLocation(FVector(0.0f, 0.0f, 120.0f));
	LockTarget->SetRelativeRotation(FRotator(0.0f, 0.0f, 180.0f));
	LockTarget->SetRelativeScale3D(FVector(0.3f, 0.3f, 0.3f));
	LockTarget->bVisible = false;

	UCapsuleComponent* Ptr = Cast<UCapsuleComponent>(RootComponent);
	if (Ptr) 
	{
		Ptr->SetCollisionProfileName(TEXT("Enemy"));
	}
}