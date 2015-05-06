// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Components/SceneComponent.h"
#include "ActorInteractionSceneComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class PROTOTYPE_API UActorInteractionSceneComponent : public USceneComponent
{
	GENERATED_BODY()

private:
	FObjectInitializer MouseDragLineObjectInitializer;
	ULineBatchComponent MouseDragLine;

public:	
	// Sets default values for this component's properties
	UActorInteractionSceneComponent();

	// Called when the game starts
	virtual void InitializeComponent() override;
	
	// Called every frame
	virtual void TickComponent( float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction ) override;

	void DrawMoveCommandLine(FVector StartPoint, FVector EndPoint);
	void EraseMoveCommandLine();

	UPROPERTY(EditAnywhere)
		FLinearColor MoveCommandLineColor;

	UPROPERTY(EditAnywhere)
		uint8 MoveCommandLineDepthPriority;

	UPROPERTY(EditAnywhere)
		float MoveCommandLineThickness;

	UPROPERTY(EditAnywhere)
		float MoveCommandLineLifeTime;
};
