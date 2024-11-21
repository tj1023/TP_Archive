// Fill out your copyright notice in the Description page of Project Settings.


#include "NCoconut.h"

// Sets default values
ANCoconut::ANCoconut()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	Coconut = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("COCONUT"));
	UStaticMesh* SM_Coconut = Cast<UStaticMesh>(StaticLoadObject(UStaticMesh::StaticClass(), NULL, TEXT("/Game/Assets/Palmtree/SM_Coconut.SM_Coconut")));
	if (SM_Coconut) Coconut->SetStaticMesh(SM_Coconut);
	
}

// Called when the game starts or when spawned
void ANCoconut::BeginPlay()
{
	Super::BeginPlay();
	
	Coconut->SetWorldScale3D(FVector(4.5f, 4.5f, 4.5f));
	Coconut->SetSimulatePhysics(true);
	Coconut->SetMassOverrideInKg("", 500);
}

// Called every frame
void ANCoconut::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

