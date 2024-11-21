// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CapstoneObject.h"
#include "Door.h"
#include "EngineUtils.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "CapstoneSubsystem.generated.h"

/**
 * 
 */
UCLASS()
class CAPSTONE_API UCapstoneSubsystem : public UGameInstanceSubsystem
{
	GENERATED_BODY()
	
	UCapstoneSubsystem();

public:
	virtual void Initialize(FSubsystemCollectionBase& Collection) override;
	virtual void Deinitialize() override;

	void GetAppartionState(bool ApparitionMode);

	bool CheckIsCleared();

	ADoor* GetTPDoor();

	void SetCorLoc(TArray<FVector> CorridersLocation);
	TArray<FVector> GetCorLoc();

private:
	TArray<FVector> CorLoc;
};
