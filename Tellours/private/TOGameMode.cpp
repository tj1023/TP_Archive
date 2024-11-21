// Fill out your copyright notice in the Description page of Project Settings.


#include "TOGameMode.h"
#include "TOCharacter.h"
#include "TOPlayerController.h"
#include "TOPlayerstate.h"

ATOGameMode::ATOGameMode()
{
	DefaultPawnClass = ATOCharacter::StaticClass();
	PlayerControllerClass = ATOPlayerController::StaticClass();
	PlayerStateClass = ATOPlayerState::StaticClass();
}

void ATOGameMode::PostLogin(APlayerController* NewPlayer)
{
	Super::PostLogin(NewPlayer);

	auto TOPlayerState = Cast<ATOPlayerState>(NewPlayer->PlayerState);
	TOPlayerState->InitPlayerData();
}