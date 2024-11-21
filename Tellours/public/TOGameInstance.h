// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Tellours.h"
#include "Engine/DataTable.h"
#include "Engine/GameInstance.h"
#include "TOGameInstance.generated.h"



/*
* 데이터 테이블 선언
*/
USTRUCT(BlueprintType)
struct FTOCharacterData : public FTableRowBase
{
	GENERATED_BODY()


public:
	FTOCharacterData() : Level(1), MaxHP(100.0f), MaxMP(100.0f), MaxEP(100.0f), Attack(10.0f) {}

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
		int32 Level;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
		float MaxHP;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
		float MaxMP;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
		float MaxEP;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
		float Attack;
};



USTRUCT(BlueprintType)
struct FTOEnemyData : public FTableRowBase
{
	GENERATED_BODY()


public:
	FTOEnemyData() : Level(1), MaxHP(100.0f), Attack(10.0f), DropExp(10) {}

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
		int32 Level;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
		float MaxHP;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
		float Attack;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
		int32 DropExp;
};

USTRUCT(BlueprintType)
struct FTOBossData : public FTableRowBase
{
	GENERATED_BODY()


public:
	FTOBossData() : Level(1), MaxHP(100.0f), Attack(10.0f), DropExp(10) {}

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
		int32 Level;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
		float MaxHP;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
		float Attack;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
		int32 DropExp;
};


/**
 * 
 */
UCLASS()
class TELLOURS_API UTOGameInstance : public UGameInstance
{
	GENERATED_BODY()
	

public:
	UTOGameInstance();

public:
	FTOCharacterData* GetTOCharacterData(int32 Level);
	FTOEnemyData* GetTOEnemyData(int32 Level);
	FTOBossData* GetTOBossData(int32 Level);

private:
	UPROPERTY()
		class UDataTable* TOCharacterTable;

	UPROPERTY()
		class UDataTable* TOEnemyTable;

	UPROPERTY()
		class UDataTable* TOBossTable;
};
