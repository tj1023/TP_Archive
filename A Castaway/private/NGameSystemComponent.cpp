// Fill out your copyright notice in the Description page of Project Settings.


#include "NGameSystemComponent.h"
#include "NCharacterStatComponent.h"
#include "EngineUtils.h"

// Sets default values for this component's properties
UNGameSystemComponent::UNGameSystemComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
	
}


// Called when the game starts
void UNGameSystemComponent::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void UNGameSystemComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UNGameSystemComponent::StartSystem(UNCharacterStatComponent* CharacterStat)
{
	NLOG(Warning, TEXT("START"));

	//Trigger박스 삭제를 위한 코드.
	/*for (TActorIterator<AActor> Actor(GetWorld()); Actor; ++Actor)
	{
		if (Actor->ActorHasTag("blockingBox"))
		{
			Actor->Destroy();
		}
	}*/

	if (CharacterStat->GetProgress(0) < 4)
	{
		if (CharacterStat->GetProgress(0) % 2 == 0)
		{
			SpawnTutorialBottle(0);
		}
		else
		{
			SpawnTutorialBottle(1);
		}
	}
	else
	{
		SpawnBottle();
	}
}

void UNGameSystemComponent::SpawnTutorialBottle(int32 location)
{
	// RIGHT
	if (location == 0)
	{
		Bottle1 = (ANBottle*)GetWorld()->SpawnActor<ANBottle>(FVector(740, 1750, 50), FRotator(0, -90, 0));
		Bottle1->SetValue(0);
		Bottle1->SetStart();
	}
	// LEFT
	else
	{
		Bottle2 = (ANBottle*)GetWorld()->SpawnActor<ANBottle>(FVector(740, -1770, 50), FRotator(0, 90, 0));
		Bottle2->SetValue(0);
		Bottle2->SetStart();
	}
}

void UNGameSystemComponent::SpawnBottle()
{
	Bottle1 = (ANBottle*)GetWorld()->SpawnActor<ANBottle>(FVector(740, 1750, 50), FRotator(0, -90, 0));
	Bottle2 = (ANBottle*)GetWorld()->SpawnActor<ANBottle>(FVector(740, -1770, 50), FRotator(0, 90, 0));

	if (FixedValue!=0)
		Bottle1->FixValue(FixedValue);
	Bottle1->SetValue(-1);
	Bottle2->SetValue(Bottle1->GetValue());
	FixedValue = 0;

	Bottle1->SetStart();
	Bottle2->SetStart();

	if (DestroyOtherBottleOn) {
		Bottle2->Destroy();
		DestroyOtherBottleOn = false;
	}
}

ANBottle* UNGameSystemComponent::GetBottle1()
{
	return Bottle1;
}

ANBottle* UNGameSystemComponent::GetBottle2()
{
	return Bottle2;
}

void UNGameSystemComponent::FixValue(int32 n)
{
	FixedValue = n;
}

void UNGameSystemComponent::DestroyOtherBottle()
{
	DestroyOtherBottleOn = true;
}