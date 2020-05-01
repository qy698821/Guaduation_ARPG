// Fill out your copyright notice in the Description page of Project Settings.


#include "TransportInteract.h"

ATransportInteract::ATransportInteract() 
{

}

void ATransportInteract::Tick(float DeltaTime)
{
	FVector NewLocation = GetActorLocation();
	FRotator NewRotation = GetActorRotation();
	float RunningTime = GetGameTimeSinceCreation();
	float DeltaHeight = (FMath::Sin(RunningTime + DeltaTime) - FMath::Sin(RunningTime));
	NewLocation.Z += DeltaHeight * 20.0f;       //Scale our height by a factor of 20
	float DeltaRotation = DeltaTime * 20.0f;    //Rotate by 20 degrees per second
	NewRotation.Yaw += DeltaRotation;
	SetActorLocationAndRotation(NewLocation, NewRotation);
}

void ATransportInteract::ObjectInteract(APlayerController * Controller)
{
	OpenLevelInBP();
}
