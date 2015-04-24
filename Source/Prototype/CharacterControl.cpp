// Fill out your copyright notice in the Description page of Project Settings.

#include "Prototype.h"
#include "CharacterControl.h"


// Sets default values
ACharacterControl::ACharacterControl()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ACharacterControl::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ACharacterControl::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );

}

// Called to bind functionality to input
void ACharacterControl::SetupPlayerInputComponent(class UInputComponent* InputComponent)
{
	Super::SetupPlayerInputComponent(InputComponent);

}

