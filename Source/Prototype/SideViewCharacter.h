// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Character.h"
#include "SideViewCharacter.generated.h"

UCLASS()
class PROTOTYPE_API ASideViewCharacter : public ACharacter
{
	GENERATED_BODY()

private:
	FObjectInitializer MouseDragLineObjectInitializer;
	ULineBatchComponent MouseDragLine;

public:
	// Sets default values for this character's properties
	ASideViewCharacter();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void Tick( float DeltaSeconds ) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* InputComponent) override;

	UFUNCTION()
	void MoveCommand_MouseDown();
	
	UFUNCTION()
	void MoveCommand_MouseUp();
};
