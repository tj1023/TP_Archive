// Fill out your copyright notice in the Description page of Project Settings.


#include "NWhistle.h"

// Sets default values
ANWhistle::ANWhistle()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	WhistleMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("EXERCISE"));
}

// Called when the game starts or when spawned
void ANWhistle::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ANWhistle::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

