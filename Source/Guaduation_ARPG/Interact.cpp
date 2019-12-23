// Fill out your copyright notice in the Description page of Project Settings.


#include "Interact.h"
#include "Engine.h"
#include "ARPGPlayerController.h"

// Sets default values
AInteract::AInteract()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	ActorVisual = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ActorVisual"));
	CollisionComponent = CreateDefaultSubobject<USphereComponent>(TEXT("CollisionComponent"));
	RootComponent = CollisionComponent;
	ActorVisual->SetupAttachment(RootComponent);
	CollisionComponent->SetSphereRadius(80.0f);
	CollisionComponent->OnComponentBeginOverlap.AddDynamic(this, &AInteract::BeginOverlap);
	CollisionComponent->OnComponentEndOverlap.AddDynamic(this, &AInteract::EndOverlap);

}

// Called when the game starts or when spawned
void AInteract::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AInteract::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AInteract::BeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int OtherBodyIndex, bool FromSweep, const FHitResult& SweepResult) 
{
	if (AARPGCharacter* CharacterPtr = Cast<AARPGCharacter>(OtherActor)) 
	{
		if (AARPGPlayerController* Ptr = Cast<AARPGPlayerController>(CharacterPtr->GetController())) 
		{
			AInteract* InteractPtr = Cast<AInteract>(OverlappedComponent->GetOwner());
			Ptr->SetCurrentInteract(InteractPtr);
		}
	}
}

void AInteract::EndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int OtherBodyIndex) 
{
	if (AARPGCharacter* CharacterPtr = Cast<AARPGCharacter>(OtherActor))
	{
		if (AARPGPlayerController* Ptr = Cast<AARPGPlayerController>(CharacterPtr->GetController()))
		{
			Ptr->ReleaseCurrentInteract();
		}
	}
}

void AInteract::ObjectInteract(APlayerController* Controller) 
{

}