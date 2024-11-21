// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Tellours.h"
#include "GameFramework/SaveGame.h"
#include "TOSaveGame.generated.h"

/**
 * 
 */
UCLASS()
class TELLOURS_API UTOSaveGame : public USaveGame
{
	GENERATED_BODY()
	
public:
	UTOSaveGame();

	UPROPERTY()
		FName MapName;

	UPROPERTY()
		int32 Progress;

	UPROPERTY()
		FVector PlayerLocation;

	UPROPERTY()
		int32 HP;

	UPROPERTY()
		int32 Level;

	UPROPERTY()
		TArray<int32> InventoryItemCount;
};
