// Fill out your copyright notice in the Description page of Project Settings.


#include "DoorTriggerVolume.h"
#include "Door.h"
#include "EngineUtils.h"

ADoorTriggerVolume::ADoorTriggerVolume()
{
	OnActorBeginOverlap.AddDynamic(this, &ADoorTriggerVolume::OnOverlapBegin);
	OnActorEndOverlap.AddDynamic(this, &ADoorTriggerVolume::OnOverlapEnd);
}

void ADoorTriggerVolume::BeginPlay()
{
	Super::BeginPlay();

}

void ADoorTriggerVolume::OnOverlapBegin(class AActor* OverlappedActor, class AActor* OtherActor)
{
	if (OtherActor && (OtherActor != this)) {
		//UE_LOG(LogTemp, Warning, TEXT("Overlap Begin"));
	}

	for (ADoor* Door : TActorRange<ADoor>(GetWorld()))
	{
		if ((GetActorLocation() - Door->GetActorLocation()).Size() <= 1200 && Door->CanOpenDoor)
		{
			Door->CloseDoor();
		}
	}
}

void ADoorTriggerVolume::OnOverlapEnd(class AActor* OverlappedActor, class AActor* OtherActor)
{
	if (OtherActor && (OtherActor != this)) {
		//UE_LOG(LogTemp, Warning, TEXT("Overlap End"));
	}

}
