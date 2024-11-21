// Fill out your copyright notice in the Description page of Project Settings.


#include "Room.h"

ARoom::ARoom()
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

	static ConstructorHelpers::FObjectFinder<UClass> BathRoom(TEXT("Blueprint'/Game/SICKA_mansion/Rooms/BP_Hard_BathRoom.BP_Hard_BathRoom_C'"));
	if (BathRoom.Object)
	{
		BP_BathRoom = BathRoom.Object;
	}

	static ConstructorHelpers::FObjectFinder<UClass> LibraryRoom(TEXT("Blueprint'/Game/SICKA_mansion/Rooms/BP_Hard_LibraryRoom.BP_Hard_LibraryRoom_C'"));
	if (LibraryRoom.Object)
	{
		BP_LibraryRoom = LibraryRoom.Object;
	}

	static ConstructorHelpers::FObjectFinder<UClass> RestaurantRoom(TEXT("Blueprint'/Game/SICKA_mansion/Rooms/BP_Hard_RestaurantRoom.BP_Hard_RestaurantRoom_C'"));
	if (RestaurantRoom.Object)
	{
		BP_RestaurantRoom = RestaurantRoom.Object;
	}

	static ConstructorHelpers::FObjectFinder<UClass> StorageRoom(TEXT("Blueprint'/Game/SICKA_mansion/Rooms/BP_Hard_StorageRoom.BP_Hard_StorageRoom_C'"));
	if (StorageRoom.Object)
	{
		BP_StorageRoom = StorageRoom.Object;
	}

	static ConstructorHelpers::FObjectFinder<UClass> Room1(TEXT("Blueprint'/Game/SICKA_mansion/Rooms/BP_Hard_Room1.BP_Hard_Room1_C'"));
	if (Room1.Object)
	{
		BP_Room1 = Room1.Object;
	}

	static ConstructorHelpers::FObjectFinder<UClass> Room2(TEXT("Blueprint'/Game/SICKA_mansion/Rooms/BP_Hard_Room2.BP_Hard_Room2_C'"));
	if (Room2.Object)
	{
		BP_Room2 = Room2.Object;
	}

	static ConstructorHelpers::FObjectFinder<UClass> Room3(TEXT("Blueprint'/Game/SICKA_mansion/Rooms/BP_Hard_Room3.BP_Hard_Room3_C'"));
	if (Room3.Object)
	{
		BP_Room3 = Room3.Object;
	}

	static ConstructorHelpers::FObjectFinder<UClass> Room4(TEXT("Blueprint'/Game/SICKA_mansion/Rooms/BP_Hard_Room4.BP_Hard_Room4_C'"));
	if (Room4.Object)
	{
		BP_Room4 = Room4.Object;
	}

	chunkType = ROOM;
}

void ARoom::BeginPlay()
{
	Super::BeginPlay();

	SetActorScale3D(FVector(15.0f, 15.0f, 1.0f));
}

void ARoom::SpawnTypeActor()
{
	Super::SpawnTypeActor();

	if (up)
		SetActorRotation(FRotator(0.0f, -90.0f, 0.0f));
	else if (down)
		SetActorRotation(FRotator(0.0f, 90.0f, 0.0f));
	else if (left)
		SetActorRotation(FRotator(0.0f, 180.0f, 0.0f));

	switch (FMath::RandRange(0, 7))
	{
		case 0:
			GetWorld()->SpawnActor<AActor>(BP_BathRoom, GetActorLocation(), GetActorRotation());
			break;
		case 1:
			GetWorld()->SpawnActor<AActor>(BP_LibraryRoom, GetActorLocation(), GetActorRotation());
			break;
		case 2:
			GetWorld()->SpawnActor<AActor>(BP_RestaurantRoom, GetActorLocation(), GetActorRotation());
			break;
		case 3:
			GetWorld()->SpawnActor<AActor>(BP_StorageRoom, GetActorLocation(), GetActorRotation());
			break;
		case 4:
			GetWorld()->SpawnActor<AActor>(BP_Room1, GetActorLocation(), GetActorRotation());
			break;
		case 5:
			GetWorld()->SpawnActor<AActor>(BP_Room2, GetActorLocation(), GetActorRotation());
			break;
		case 6:
			GetWorld()->SpawnActor<AActor>(BP_Room3, GetActorLocation(), GetActorRotation());
			break;
		case 7:
			GetWorld()->SpawnActor<AActor>(BP_Room4, GetActorLocation(), GetActorRotation());
			break;
		default:
			break;
	}

	Destroy();
}