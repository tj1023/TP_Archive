// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Tellours.h"
#include "GameFramework/Actor.h"
#include "TOChestSpawner.generated.h"

UCLASS()
class TELLOURS_API ATOChestSpawner : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ATOChestSpawner();

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
		UStaticMeshComponent* ChestSpawner;

	void ChestSpawn();

private:
	// 랜덤 생성 범위 지정
	UPROPERTY(EditAnywhere, Category = Spawn, Meta = (AllowPrivateAccess = true))
		FVector Point1;

	UPROPERTY(EditAnywhere, Category = Spawn, Meta = (AllowPrivateAccess = true))
		FVector Point2;
};
