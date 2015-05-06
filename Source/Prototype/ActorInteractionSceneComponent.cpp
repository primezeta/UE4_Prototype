// Fill out your copyright notice in the Description page of Project Settings.

#include "Prototype.h"
#include "ActorInteractionSceneComponent.h"

static FVector MoveCommandLineBegin;
static FVector MoveCommandLineEnd;
static bool IsMoveCommandLineDrawing;

// Sets default values for this component's properties
UActorInteractionSceneComponent::UActorInteractionSceneComponent() :
	MouseDragLine(MouseDragLineObjectInitializer),
	MoveCommandLineColor(FColor::Green),
	MoveCommandLineDepthPriority(0),
	MoveCommandLineThickness(0.0f),
	MoveCommandLineLifeTime(1.0f)
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	bWantsInitializeComponent = true;
	PrimaryComponentTick.bCanEverTick = true;
}


// Called when the game starts
void UActorInteractionSceneComponent::InitializeComponent()
{
	Super::InitializeComponent();
}

// Called every frame
void UActorInteractionSceneComponent::TickComponent( float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction )
{
	Super::TickComponent( DeltaTime, TickType, ThisTickFunction );
	
	static float AccumTime = 0.0f;
	static bool WasMoveCommandLineDrawing;
	if (IsMoveCommandLineDrawing)
	{
		WasMoveCommandLineDrawing = true;
		AccumTime += DeltaTime;
		if (AccumTime > MoveCommandLineLifeTime)
		{
			AccumTime = 0.0f;
			MouseDragLine.DrawLine(MoveCommandLineBegin, MoveCommandLineEnd, MoveCommandLineColor, MoveCommandLineDepthPriority, MoveCommandLineThickness, MoveCommandLineLifeTime);
		}
	}
	else if (WasMoveCommandLineDrawing)
	{
		WasMoveCommandLineDrawing = false;
		AccumTime = 0.0f;
	}
}

void UActorInteractionSceneComponent::DrawMoveCommandLine(FVector StartPoint, FVector EndPoint)
{
	IsMoveCommandLineDrawing = true;
	MoveCommandLineBegin = StartPoint;
	MoveCommandLineEnd = EndPoint;
}

void UActorInteractionSceneComponent::EraseMoveCommandLine()
{
	IsMoveCommandLineDrawing = false;
}