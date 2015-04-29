// Fill out your copyright notice in the Description page of Project Settings.

#include "Prototype.h"
#include "SideViewCharacter.h"

// Sets default values
ASideViewCharacter::ASideViewCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void ASideViewCharacter::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void ASideViewCharacter::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );
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
	APlayerController* PlayerController = Cast<APlayerController>(GetController());
	check(PlayerController != nullptr);

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
			//We clicked ourself!
			GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::Red, "Yay!");
		}
		else
		{
			GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::Red, "noooo");
		}
	}
}

void ASideViewCharacter::MoveCommand_MouseUp()
{
}