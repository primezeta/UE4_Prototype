// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Character.h"
#include "ActorInteractionSceneComponent.h"
#include "SideViewCharacter.generated.h"

UCLASS()
class PROTOTYPE_API ASideViewCharacter : public ACharacter
{
	GENERATED_BODY()

private:
	bool CharacterIsSelected;
	APlayerController const * PlayerController();
	UActorInteractionSceneComponent * ActorInteractor();
	FVector MousePosition();
	FVector2D ScreenMousePosition();
	FVector PlayerPosition();

public:
	// Sets default values for this character's properties
	ASideViewCharacter();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void Tick( float DeltaSeconds ) override;

	virtual void SetupPlayerInputComponent(class UInputComponent* InputComponent);

	UFUNCTION()
		void MoveCommand_MouseDown();

	UFUNCTION()
		void MoveCommand_MouseUp();
};
