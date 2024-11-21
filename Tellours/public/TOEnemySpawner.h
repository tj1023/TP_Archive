// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Tellours.h"
#include "GameFramework/Actor.h"
#include "TOEnemy.h"
#include "TONPC.h"
#include "TOEnemySpawner.generated.h"


DECLARE_MULTICAST_DELEGATE(AllKillDelegate);


UCLASS()
class TELLOURS_API ATOEnemySpawner : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ATOEnemySpawner();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;



	/*
	* 스폰 구현
	*/
public:
	UPROPERTY()
	UStaticMeshComponent* EnemySpawner;

	void EnemySpawn();
	void SetSpawnType(EnemyType Type);
	void SetNumberOfSpawn(int32 Num);
	void SetSpawnNum(int32 Num);

private:
	UPROPERTY(EditAnywhere, Category = Spawn, Meta = (AllowPrivateAccess = true))
	EnemyType NewEnemyType;

	UPROPERTY(EditAnywhere, Category = Spawn, Meta = (AllowPrivateAccess = true))
	float SpawnRadius;

	UPROPERTY(EditAnywhere, Category = Spawn, Meta = (AllowPrivateAccess = true))
	int32 NumberOfSpawn;

	UPROPERTY(EditAnywhere, Category = Spawn, Meta = (AllowPrivateAccess = true))
	int32 NumberOfWave;

	UPROPERTY(EditAnywhere, Category = Spawn, Meta = (AllowPrivateAccess = true))
	float WaveIntervalTime;
	
	int32 WaveCount;

	FTimerHandle EnemySpawnDelay = { };

	// 퀘스트
public:
	AllKillDelegate AllKill;

	int32 KillCount;

	void SetMotherNPC(ATONPC* TONPC);

private:
	ATONPC* MotherNPC;

};
