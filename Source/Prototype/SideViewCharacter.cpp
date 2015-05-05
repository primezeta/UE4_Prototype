// Fill out your copyright notice in the Description page of Project Settings.

#include "Prototype.h"
#include "SideViewCharacter.h"

static bool bPreviousMouseDragIsActive = false;
static bool bMouseDragIsActive = false;
static APlayerController* PlayerController = nullptr;

// Sets default values
ASideViewCharacter::ASideViewCharacter() : MouseDragLine(MouseDragLineObjectInitializer)
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	bMouseDragIsActive = false;
	MouseDragLine.bHiddenInGame = true;
	PlayerController = Cast<APlayerController>(GetController());
	check(PlayerController != nullptr);
}

// Called when the game starts or when spawned
void ASideViewCharacter::BeginPlay()
{
	Super::BeginPlay();
	PlayerController->bShowMouseCursor = true;
}

// Called every frame
void ASideViewCharacter::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );

	if (bMouseDragIsActive != bPreviousMouseDragIsActive)
	{
		if (bMouseDragIsActive)
		{
			//Draw a line from the player to the mouse location
			APlayerController* PlayerController = Cast<APlayerController>(GetController());
			check(PlayerController != nullptr);
			FVector PlayerLocation = this->GetActorLocation();
			float mx, my;
			PlayerController->GetMousePosition(mx, my);
			FLinearColor LineColor(FColor::Green);

			//Not sure the best value for these right now
			uint8 LineDepthPriority = 0;
			float LineThickness = 1.0f;
			float LineLifeTime = 0.0f;

			//Draw the line from the player location to the mouse X,Y where the world Y is the mouse X and world Z is the mouse Y. Always use player X for the World X.
			MouseDragLine.DrawLine(PlayerLocation, FVector(PlayerLocation.X, mx, my), LineColor, LineDepthPriority, LineThickness, LineLifeTime);
			MouseDragLine.bHiddenInGame = false;
		}
		else
		{
			//Hide the line
			MouseDragLine.Deactivate();
		}
	}
}

// Called to bind functionality to input
void ASideViewCharacter::SetupPlayerInputComponent(class UInputComponent* InputComponent)
{
	Super::SetupPlayerInputComponent(InputComponent);
	InputComponent->BindAction("MouseButtonRight", IE_Pressed, this, &ASideViewCharacter::MoveCommand_MouseDown);
	InputComponent->BindAction("MouseButtonRight", IE_Released, this, &ASideViewCharacter::MoveCommand_MouseUp);
}

void ASideViewCharacter::MoveCommand_MouseDown()
{
	static const bool bTraceComplex = false;

	float mx = 0.0f;
	float my = 0.0f;
	PlayerController->GetMousePosition(mx, my);

	// Do a trace and see if there the position intersects something in the world  
	FVector2D MousePosition(mx, my);
	FHitResult HitResult;	
	if (PlayerController->GetHitResultAtScreenPosition(MousePosition, ECC_Visibility, bTraceComplex, HitResult) == true)
	{
		APawn* ClickedPawn = Cast<ACharacter>(HitResult.GetActor());
		if (ClickedPawn == this)
		{
			//The player character was clicked!
			GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::Red, "Yay!");

			bPreviousMouseDragIsActive = bMouseDragIsActive;
			bMouseDragIsActive = true;
		}
		else
		{
			GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::Red, "noooo");

			//Is this necessary? Don't know yet
			bPreviousMouseDragIsActive = bMouseDragIsActive;
			bMouseDragIsActive = false;
		}
	}
}

void ASideViewCharacter::MoveCommand_MouseUp()
{
	bMouseDragIsActive = false;
	bPreviousMouseDragIsActive = false;
}