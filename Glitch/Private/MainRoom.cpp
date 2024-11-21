// Fill out your copyright notice in the Description page of Project Settings.


#include "MainRoom.h"

AMainRoom::AMainRoom()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	MainMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MainMesh"));
	SetRootComponent(MainMesh);

	static ConstructorHelpers::FObjectFinder<UStaticMesh> DefaultMesh(TEXT("/Game/Geometry/Meshes/1M_Cube.1M_Cube"));

	if (DefaultMesh.Succeeded())
	{
		MainMesh->SetStaticMesh(DefaultMesh.Object);
	}
	
	static ConstructorHelpers::FObjectFinder<UClass> MainRoom(TEXT("Blueprint'/Game/SICKA_mansion/Rooms/BP_Hard_MainRoom.BP_Hard_MainRoom_C'"));
	if (MainRoom.Object)
	{
		BP_MainRoom = MainRoom.Object;
	}


	chunkType = MAIN;

	down = false;
	up = true;
	left = true;
	right = true;
}

void AMainRoom::BeginPlay()
{
	Super::BeginPlay();

	SetActorScale3D(FVector(20.0f, 40.0f, 1.0f));
}

void AMainRoom::SpawnTypeActor()
{
	Super::SpawnTypeActor();

	SetActorRotation(FRotator(0.0f, 90.0f, 0.0f));
	GetWorld()->SpawnActor<AActor>(BP_MainRoom, GetActorLocation(), GetActorRotation());

	Destroy();
}