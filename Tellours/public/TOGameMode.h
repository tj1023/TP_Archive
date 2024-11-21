// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Tellours.h"
#include "GameFramework/GameModeBase.h"
#include "TOGameMode.generated.h"

/**
 * 
 */
UCLASS()
class TELLOURS_API ATOGameMode : public AGameModeBase
{
	GENERATED_BODY()

	ATOGameMode();

	/*virtual void PostInitializeComponents() override;*/
	virtual void PostLogin(APlayerController* NewPlayer) override;
};
