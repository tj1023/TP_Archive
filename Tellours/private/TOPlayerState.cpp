// Fill out your copyright notice in the Description page of Project Settings.


#include "TOPlayerState.h"
#include "TOCharacter.h"
#include "TOCharacterStatComponent.h"
#include "TOSaveGame.h"
#include <string>

ATOPlayerState::ATOPlayerState()
{
	SaveSlotName = TEXT("SaveDatafile_1");
}

void ATOPlayerState::InitPlayerData()
{
	auto TOSaveGame = Cast<UTOSaveGame>(UGameplayStatics::LoadGameFromSlot(SaveSlotName, 0));

	//SaveData가 존재하지 않을 시 실행됨.
	if (TOSaveGame == nullptr)
	{
		ABLOG(Warning, TEXT("FIRST INIT"));
		TOSaveGame = GetMutableDefault<UTOSaveGame>();
	}

	MapName = TOSaveGame->MapName;
	Progress = TOSaveGame->Progress;
	PlayerLocation = TOSaveGame->PlayerLocation;
	HP = TOSaveGame->HP;
	Level = TOSaveGame->Level;
	// inventory Save
	InventoryItemCount = TOSaveGame->InventoryItemCount;

	ABLOG(Warning, TEXT("INIT COMPLETE"));

	auto TOCharacter = Cast<ATOCharacter>(GetWorld()->GetFirstPlayerController()->GetPawn());

	TOCharacter->SetActorLocation(PlayerLocation);
	TOCharacter->CharacterStat->SetNewLevel(Level);
	TOCharacter->CharacterStat->SetHP(HP);
	TOCharacter->CharacterStat->SetProgress(Progress);
	// inventory Save
	TOCharacter->CharacterStat->SetInventoryItemCount(InventoryItemCount);

	UGameplayStatics::LoadStreamLevel(this, MapName, true, false, LatentActionInfo);
}

void ATOPlayerState::OnStreamLevelLoaded()
{
	/*auto TOCharacter = Cast<ATOCharacter>(GetWorld()->GetFirstPlayerController()->GetPawn());

	TOCharacter->SetActorLocation(PlayerLocation);*/
}

void ATOPlayerState::SavePlayerData(FString LevelName)
{
	UTOSaveGame* NewPlayerData = NewObject<UTOSaveGame>();

	auto TOCharacter = Cast<ATOCharacter>(GetWorld()->GetFirstPlayerController()->GetPawn());

	// 세이브 데이터 지정
	NewPlayerData->MapName = FName(LevelName);
	NewPlayerData->Progress = (int32)(TOCharacter->CharacterStat->GetProgress());
	NewPlayerData->PlayerLocation = TOCharacter->GetActorLocation();
	NewPlayerData->Level = (int32)(TOCharacter->CharacterStat->GetCurrentLevel());
	NewPlayerData->HP = (int32)(TOCharacter->CharacterStat->GetCurrentHP());
	// inventory Save
	NewPlayerData->InventoryItemCount = TOCharacter->CharacterStat->GetInventoryItemCount();
	ABLOG(Warning, TEXT("%d	/	%d	/	%d	/	%d"), NewPlayerData->InventoryItemCount[0], NewPlayerData->InventoryItemCount[1], NewPlayerData->InventoryItemCount[2], NewPlayerData->InventoryItemCount[3]);
	if (!UGameplayStatics::SaveGameToSlot(NewPlayerData, SaveSlotName, 0))
	{
		ABLOG(Error, TEXT("SaveGame Error!"));
	}
}

int32 ATOPlayerState::GetProgress()
{
	return Progress;
}