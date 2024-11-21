// Fill out your copyright notice in the Description page of Project Settings.


#include "TOGameInstance.h"

// 데이터 테이블 연결
UTOGameInstance::UTOGameInstance()
{
	// Character Data
	FString CharacterDataPath = TEXT("/Game/Tellours/Developer/GameData/TOCharacterData.TOCharacterData");
	static ConstructorHelpers::FObjectFinder<UDataTable> DT_TOCHARACTER(*CharacterDataPath);
	ABCHECK(DT_TOCHARACTER.Succeeded());
	TOCharacterTable = DT_TOCHARACTER.Object;
	// 데이터테이블 오류 체크
	ABCHECK(TOCharacterTable->GetRowMap().Num() > 0);

	// Enemy Data
	FString EnemyDataPath = TEXT("/Game/Tellours/Developer/GameData/TOEnemyData.TOEnemyData");
	static ConstructorHelpers::FObjectFinder<UDataTable> DT_TOENEMY(*EnemyDataPath);
	ABCHECK(DT_TOENEMY.Succeeded());
	TOEnemyTable = DT_TOENEMY.Object;
	// 데이터테이블 오류 체크
	ABCHECK(TOEnemyTable->GetRowMap().Num() > 0);

	// Enemy Data
	FString BossDataPath = TEXT("/Game/Tellours/Developer/GameData/TOBossData.TOBossData");
	static ConstructorHelpers::FObjectFinder<UDataTable> DT_TOBOSS(*BossDataPath);
	ABCHECK(DT_TOBOSS.Succeeded());
	TOBossTable = DT_TOBOSS.Object;
	// 데이터테이블 오류 체크
	ABCHECK(TOBossTable->GetRowMap().Num() > 0);
}

/*
* 데이터 반환 함수
*/ 
FTOCharacterData* UTOGameInstance::GetTOCharacterData(int32 Level)
{
	return TOCharacterTable->FindRow<FTOCharacterData>(*FString::FromInt(Level), TEXT(""));
}

FTOEnemyData* UTOGameInstance::GetTOEnemyData(int32 Level)
{
	return TOEnemyTable->FindRow<FTOEnemyData>(*FString::FromInt(Level), TEXT(""));
}

FTOBossData* UTOGameInstance::GetTOBossData(int32 Level)
{
	return TOBossTable->FindRow<FTOBossData>(*FString::FromInt(Level), TEXT(""));
}