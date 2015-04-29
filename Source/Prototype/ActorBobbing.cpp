// Copyright 1998-2015 Epic Games, Inc. All Rights Reserved.

#include "Prototype.h"
#include "ActorBobbing.h"

// Sets default values
AActorBobbing::AActorBobbing()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AActorBobbing::BeginPlay()
{
	Super::BeginPlay();

}

// Called every frame
void AActorBobbing::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	FVector NewLocation = GetActorLocation();
	float DeltaHeight = (FMath::Sin(RunningTime + DeltaTime) - FMath::Sin(RunningTime));
	NewLocation.Z += DeltaHeight * 20.0f;       //Scale our height by a factor of 20
	RunningTime += DeltaTime;
	SetActorLocation(NewLocation);
}