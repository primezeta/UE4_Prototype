// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/GameMode.h"
#include "LevelGenGameMode.generated.h"

/*
Step 1: Just create a function to spawn basic tiles from a static 2d array
Step 2: Create procedural generation of the 2d array of tiles
Step 3: Make it awesomer!

Maybe the data structure for the array should be a (x,y) origin followed by the 2d array of tiles
*/

/**
 * 
 */
UCLASS()
class PROTOTYPE_API ALevelGenGameMode : public AGameMode
{
	GENERATED_BODY()

		/* The blueprint class for the basic tile */
		//UPROPERTY(EditAnywhere, Category=LevelComponents)
		//UBlueprint * BasicTileBlueprint;

		UClass * BasicTileBlueprintClass;
public:
	ALevelGenGameMode(const FObjectInitializer& ObjectInitializer);
	virtual void InitGame(const FString& MapName, const FString& Options, FString& ErrorMessage);
};
