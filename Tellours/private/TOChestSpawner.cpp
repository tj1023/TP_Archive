// Fill out your copyright notice in the Description page of Project Settings.


#include "TOChestSpawner.h"
#include "TOItem.h"
#include "TOChest.h"

// Sets default values
ATOChestSpawner::ATOChestSpawner()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	ChestSpawner = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("CHESTSPAWNER"));
}

// Called when the game starts or when spawned
void ATOChestSpawner::BeginPlay()
{
	Super::BeginPlay();
	
	ChestSpawn();
	ChestSpawn();
}

// Called every frame
void ATOChestSpawner::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}



/*
* 스폰 구현
*/
void ATOChestSpawner::ChestSpawn()
{
	FBox Box = FBox(Point1, Point2);
	FVector ChestLoc = FMath::RandPointInBox(Box);
	ATOChest* Chest = (ATOChest*)GetWorld()->SpawnActor<ATOChest>(ChestLoc, FRotator::ZeroRotator);
	Chest->SetMotherSpawner(this);
}
