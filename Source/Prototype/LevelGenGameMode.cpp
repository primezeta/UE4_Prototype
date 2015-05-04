// Fill out your copyright notice in the Description page of Project Settings.

#include "Prototype.h"
#include "LevelGenGameMode.h"
#include "Engine/TriggerBox.h"

ALevelGenGameMode::ALevelGenGameMode(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	//AGameMode
	ConstructorHelpers::FObjectFinder<UBlueprint> BasicTileClass(TEXT("Blueprint'/Game/SideScrollerBP/Blueprints/TriggerBox_BasicTile_Blueprint.TriggerBox_BasicTile_Blueprint'"));
	BasicTileBlueprintClass = BasicTileClass.Object->GeneratedClass;
}

void ALevelGenGameMode::InitGame(const FString& MapName, const FString& Options, FString& ErrorMessage)
{
	Super::InitGame(MapName, Options, ErrorMessage);
	//Generate the map prior to the EnteringMap state

	FVector SpawnLocation = FVector(1060.0f, 20.0f, 318.0f);
	FRotator InitialRotation = FRotator(0.0f, 0.0f, 0.0f);
	UWorld * World = GetWorld();
	FActorSpawnParameters SpawnInfo;
	SpawnInfo.Owner = this;
	ATriggerBox * BasicTile = static_cast<ATriggerBox*>(World->SpawnActor(BasicTileBlueprintClass, &SpawnLocation, &InitialRotation, SpawnInfo));

	//Testing placement
	//BasicTile->GetActorBounds(false, Origin, BoxExtent);
	//FVector NextSpawnLocationNoCollidingComponents = FVector(SpawnLocation.X, SpawnLocation.Y + (BoxExtent.Y / 2), SpawnLocation.Z);
	//BasicTile->GetActorBounds(true, Origin, BoxExtent);
	//FVector NextSpawnLocationYesCollidingComponents = FVector(SpawnLocation.X, SpawnLocation.Y + (BoxExtent.Y * 2), SpawnLocation.Z); <------ this one appears to place two of the tile components exactly side-by-side

	FVector Origin;
	FVector BoxExtent;
	BasicTile->GetActorBounds(true, Origin, BoxExtent);

	for (int i = 0; i < 5; i++)
	{
		SpawnLocation.Y -= BoxExtent.Y * 2;
		BasicTile = static_cast<ATriggerBox*>(World->SpawnActor(BasicTileBlueprintClass, &SpawnLocation, &InitialRotation, SpawnInfo));
	}
	SpawnLocation = FVector(1060.0f, 20.0f, 318.0f);
	for (int i = 0; i < 5; i++)
	{
		SpawnLocation.Y += BoxExtent.Y * 2;
		BasicTile = static_cast<ATriggerBox*>(World->SpawnActor(BasicTileBlueprintClass, &SpawnLocation, &InitialRotation, SpawnInfo));
	}
}