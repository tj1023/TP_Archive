// Fill out your copyright notice in the Description page of Project Settings.


#include "NSaveGame.h"

UNSaveGame::UNSaveGame()
{
	ProgressStatus.Init(0, SCRIPT_LEN);
	
	Happy = 50;
	Sad = 50;
	Anger = 50;
	Bored = 50;

	Survival_time = 0;
	Aquaphobia = 100;

	Status_Effect0 = false;
	Status_Effect1 = false;
	Status_Effect2 = false;
	Status_Effect3 = false;
}
