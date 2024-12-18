// Copyright Epic Games, Inc. All Rights Reserved.

#include "CapstoneGameMode.h"
#include "CapstoneHUD.h"
#include "CapstoneCharacter.h"
#include "CapstoneController.h"
#include "UObject/ConstructorHelpers.h"

ACapstoneGameMode::ACapstoneGameMode()
	: Super()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnClassFinder(TEXT("/Game/FirstPersonCPP/Blueprints/FirstPersonCharacter"));
	DefaultPawnClass = PlayerPawnClassFinder.Class;

	// use our custom HUD class
	HUDClass = ACapstoneHUD::StaticClass();
	// 컨트롤러 할당
	PlayerControllerClass = ACapstoneController::StaticClass();
}
