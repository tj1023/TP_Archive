// Fill out your copyright notice in the Description page of Project Settings.


#include "TOArmor.h"

// Sets default values
ATOArmor::ATOArmor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	// 规绢备 包访 积己磊
	Helmet = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("HELM"));
	RootComponent = Helmet;

	//static ConstructorHelpers::FObjectFinder<UStaticMesh> SM_HELM(TEXT("/Game/Ramia/Meshes/SM_Ramia_Helm.SM_Ramia_Helm"));
	/*if (SM_HELM.Succeeded())
	{
		Helmet->SetStaticMesh(SM_HELM.Object);
	}

	Helmet->SetCollisionProfileName(TEXT("NoCollision"));*/
}

// Called when the game starts or when spawned
void ATOArmor::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ATOArmor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

