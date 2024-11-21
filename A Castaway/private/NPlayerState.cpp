// Fill out your copyright notice in the Description page of Project Settings.


#include "NPlayerState.h"
#include "NSaveGame.h"
#include "NCharacter.h"
#include "NCharacterStatComponent.h"

ANPlayerState::ANPlayerState()
{
	SaveDataName = FString(TEXT("ProjectNSaveData"));

	ProgressStatus.Init(0, SCRIPT_LEN);

	Happy = 100;
	Sad = 100;
	Anger = 100;
	Bored = 100;

	Survival_time = 0;
	// 물 공포증
	Aquaphobia = 100;

	// 상태이상
	Status_Effect0 = false;
	Status_Effect1 = false;
	Status_Effect2 = false;
	Status_Effect3 = false;
}

void ANPlayerState::InitPlayerData()
{
	auto NSaveGame = Cast<UNSaveGame>(UGameplayStatics::LoadGameFromSlot(SaveDataName, 0));
	if (nullptr == NSaveGame)
	{
		NSaveGame = GetMutableDefault<UNSaveGame>();

		NLOG(Warning, TEXT("FIRST PLAYER DATA GENERATED"));
	}

	for (int i = 0; i < SCRIPT_LEN; i++)
	{
		ProgressStatus[i] = NSaveGame->ProgressStatus[i];
	}

	Happy = NSaveGame->Happy;
	Sad = NSaveGame->Sad;
	Anger = NSaveGame->Anger;
	Bored = NSaveGame->Bored;

	Survival_time = NSaveGame->Survival_time;
	Aquaphobia = NSaveGame->Aquaphobia;
	Status_Effect0 = NSaveGame->Status_Effect0;
	Status_Effect1 = NSaveGame->Status_Effect1;
	Status_Effect2 = NSaveGame->Status_Effect2;
	Status_Effect3 = NSaveGame->Status_Effect3;

	// 캐릭터에게 Emotion값 설정
	auto NCharacter = Cast<ANCharacter>(GetWorld()->GetFirstPlayerController()->GetPawn());

	for (int i = 0; i < SCRIPT_LEN; i++)
	{
		NCharacter->CharacterStat->SetProgress(ProgressStatus[i], i);
	}

	NCharacter->CharacterStat->SetEmotion(Happy, 0);
	NCharacter->CharacterStat->SetEmotion(Sad, 1);
	NCharacter->CharacterStat->SetEmotion(Anger, 2);
	NCharacter->CharacterStat->SetEmotion(Bored, 3);

	// 생존일수, 물 공포증, 상태이상 설정
	NCharacter->CharacterStat->SetSurvivalDays(Survival_time);
	NCharacter->CharacterStat->SetAquaphobia(Aquaphobia);
	NCharacter->CharacterStat->SetStatusEffect(Status_Effect0, 0);
	NCharacter->CharacterStat->SetStatusEffect(Status_Effect1, 1);
	NCharacter->CharacterStat->SetStatusEffect(Status_Effect2, 2);
	NCharacter->CharacterStat->SetStatusEffect(Status_Effect3, 3);

	for (int i = 0; i < SCRIPT_LEN; i++)
	{
		NLOG(Warning, TEXT("%d - %d"), i, ProgressStatus[i]);
	}

	SavePlayerData();

	NLOG(Warning, TEXT("INIT PLAYER DATA COMPLETE!"));
}

void ANPlayerState::BeginPlay()
{
	Super::BeginPlay();

	
}

void ANPlayerState::SavePlayerData()
{
	UNSaveGame* NewPlayerData = NewObject<UNSaveGame>();

	auto NCharacter = Cast<ANCharacter>(GetWorld()->GetFirstPlayerController()->GetPawn());

	for (int i = 0; i < SCRIPT_LEN; i++)
	{
		NewPlayerData->ProgressStatus[i] = NCharacter->CharacterStat->GetProgress(i);
	}

	NewPlayerData->Happy = NCharacter->CharacterStat->GetEmotion(0);
	NewPlayerData->Sad = NCharacter->CharacterStat->GetEmotion(1);
	NewPlayerData->Anger = NCharacter->CharacterStat->GetEmotion(2);
	NewPlayerData->Bored = NCharacter->CharacterStat->GetEmotion(3);

	NewPlayerData->Survival_time = NCharacter->CharacterStat->GetSurvivalDays();
	NewPlayerData->Aquaphobia = NCharacter->CharacterStat->GetAquaphobia();
	NewPlayerData->Status_Effect0 = NCharacter->CharacterStat->GetStatusEffect(0);
	NewPlayerData->Status_Effect1 = NCharacter->CharacterStat->GetStatusEffect(1);
	NewPlayerData->Status_Effect2 = NCharacter->CharacterStat->GetStatusEffect(2);
	NewPlayerData->Status_Effect3 = NCharacter->CharacterStat->GetStatusEffect(3);

	if (!UGameplayStatics::SaveGameToSlot(NewPlayerData, SaveDataName, 0))
	{
		NLOG(Error, TEXT("SaveGame Error!"));
	}
}
