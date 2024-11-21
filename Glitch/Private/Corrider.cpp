// Fill out your copyright notice in the Description page of Project Settings.


#include "Corrider.h"

ACorrider::ACorrider()
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

	static ConstructorHelpers::FObjectFinder<UClass> CorriderBlueprint_1(TEXT("Blueprint'/Game/SICKA_mansion/Rooms/BP_2Way_Corrider.BP_2Way_Corrider_C'"));
	if (CorriderBlueprint_1.Object)
	{
		BP_Corrider_2Way = CorriderBlueprint_1.Object;
	}

	static ConstructorHelpers::FObjectFinder<UClass> CorriderBlueprint_2(TEXT("Blueprint'/Game/SICKA_mansion/Rooms/BP_2Way_Vertical_Corrider.BP_2Way_Vertical_Corrider_C'"));
	if (CorriderBlueprint_2.Object)
	{
		BP_Corrider_Vertical_2Way = CorriderBlueprint_2.Object;
	}

	static ConstructorHelpers::FObjectFinder<UClass> CorriderBlueprint_3(TEXT("Blueprint'/Game/SICKA_mansion/Rooms/BP_3Way_Corrider.BP_3Way_Corrider_C'"));
	if (CorriderBlueprint_3.Object)
	{
		BP_Corrider_3Way = CorriderBlueprint_3.Object;
	}

	static ConstructorHelpers::FObjectFinder<UClass> CorriderBlueprint_4(TEXT("Blueprint'/Game/SICKA_mansion/Rooms/BP_4Way_Corrider.BP_4Way_Corrider_C'"));
	if (CorriderBlueprint_4.Object)
	{
		BP_Corrider_4Way = CorriderBlueprint_4.Object;
	}

	chunkType = CORRIDER;
}

void ACorrider::BeginPlay()
{
	Super::BeginPlay();

	SetActorScale3D(FVector(20.0f, 20.0f, 1.0f));
}

void ACorrider::SpawnTypeActor()
{
	Super::SpawnTypeActor();

	if (up && right && down && left)
		GetWorld()->SpawnActor<AActor>(BP_Corrider_4Way, GetActorLocation(), GetActorRotation());
	else if (up && right && down)
	{
		SetActorRotation(FRotator(0.0f, 90.0f, 0.0f));
		GetWorld()->SpawnActor<AActor>(BP_Corrider_3Way, GetActorLocation(), GetActorRotation());
	}
	else if (right && down && left)
	{
		SetActorRotation(FRotator(0.0f, 180.0f, 0.0f));
		GetWorld()->SpawnActor<AActor>(BP_Corrider_3Way, GetActorLocation(), GetActorRotation());
	}
	else if (down && left && up)
	{
		SetActorRotation(FRotator(0.0f, -90.0f, 0.0f));
		GetWorld()->SpawnActor<AActor>(BP_Corrider_3Way, GetActorLocation(), GetActorRotation());
	}
	else if (left && up && right)
	{
		GetWorld()->SpawnActor<AActor>(BP_Corrider_3Way, GetActorLocation(), GetActorRotation());
	}
	else if (up && right)
	{
		SetActorRotation(FRotator(0.0f, 90.0f, 0.0f));
		GetWorld()->SpawnActor<AActor>(BP_Corrider_Vertical_2Way, GetActorLocation(), GetActorRotation());
	}
	else if (right && down)
	{
		SetActorRotation(FRotator(0.0f, 180.0f, 0.0f));
		GetWorld()->SpawnActor<AActor>(BP_Corrider_Vertical_2Way, GetActorLocation(), GetActorRotation());
	}
	else if (down && left)
	{
		SetActorRotation(FRotator(0.0f, -90.0f, 0.0f));
		GetWorld()->SpawnActor<AActor>(BP_Corrider_Vertical_2Way, GetActorLocation(), GetActorRotation());
	}
	else if (left && up)
	{
		GetWorld()->SpawnActor<AActor>(BP_Corrider_Vertical_2Way, GetActorLocation(), GetActorRotation());
	}
	else if (up && down)
	{
		SetActorRotation(FRotator(0.0f, 90.0f, 0.0f));

		GetWorld()->SpawnActor<AActor>(BP_Corrider_2Way, GetActorLocation(), GetActorRotation());
	}
	else if (right && left)
	{
		GetWorld()->SpawnActor<AActor>(BP_Corrider_2Way, GetActorLocation(), GetActorRotation());
	}

	//Destroy();
}