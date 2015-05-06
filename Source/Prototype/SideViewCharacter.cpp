// Fill out your copyright notice in the Description page of Project Settings.

#include "Prototype.h"
#include "SideViewCharacter.h"


// Sets default values
ASideViewCharacter::ASideViewCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	CharacterIsSelected = false;
}

// Called when the game starts or when spawned
void ASideViewCharacter::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void ASideViewCharacter::Tick( float DeltaTime )
{
	Super::Tick(DeltaTime);
	
	if (CharacterIsSelected)
	{
		ActorInteractor()->DrawMoveCommandLine(PlayerPosition(), MousePosition());
	}
}

// Called to bind functionality to input
void ASideViewCharacter::SetupPlayerInputComponent(class UInputComponent* InputComponent)
{
	Super::SetupPlayerInputComponent(InputComponent);
	InputComponent->BindAction("MouseButtonRight", IE_Pressed, this, &ASideViewCharacter::MoveCommand_MouseDown);
	InputComponent->BindAction("MouseButtonRight", IE_Released, this, &ASideViewCharacter::MoveCommand_MouseUp);
}

//MouseDragLine.DrawLine(PlayerLocation, FVector(PlayerLocation.X, mx, my), LineColor, LineDepthPriority, LineThickness, LineLifeTime);
void ASideViewCharacter::MoveCommand_MouseDown()
{
	static const bool bTraceComplex = false;
	FHitResult HitResult;
	if (PlayerController()->GetHitResultAtScreenPosition(ScreenMousePosition(), ECC_Visibility, bTraceComplex, HitResult) == true)
	{
		CharacterIsSelected = false; //First assume the player character was not clicked...
		APawn* ClickedPawn = Cast<APawn>(HitResult.GetActor());
		if (ClickedPawn == Cast<APawn>(this))
		{
			//The player character was clicked!
			GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::Red, "Yay!");
			CharacterIsSelected = true;
		}
	}
}

void ASideViewCharacter::MoveCommand_MouseUp()
{
	CharacterIsSelected = false;
}

APlayerController const * ASideViewCharacter::PlayerController()
{
	static APlayerController * ThePlayerController = nullptr;
	if (ThePlayerController == nullptr)
	{
		ThePlayerController = Cast<APlayerController>(GetController());
	}
	return ThePlayerController;
}

UActorInteractionSceneComponent * ASideViewCharacter::ActorInteractor()
{
	static UActorInteractionSceneComponent * TheActorInteractor = nullptr;
	if (TheActorInteractor == nullptr)
	{
		TheActorInteractor = nullptr;
	}
	return TheActorInteractor;
}

FVector ASideViewCharacter::MousePosition()
{
	static FVector Position;
	PlayerController()->GetMousePosition(Position.Y, Position.Z);
	Position.X = PlayerPosition().X;
	return Position;
}

FVector2D ASideViewCharacter::ScreenMousePosition()
{
	static FVector2D Position;
	PlayerController()->GetMousePosition(Position.X, Position.Y);
	return Position;
}

FVector ASideViewCharacter::PlayerPosition()
{
	static FVector Position;
	Position = this->GetActorLocation();
	return Position;
}