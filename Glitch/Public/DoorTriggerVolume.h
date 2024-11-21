// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/TriggerVolume.h"
#include "DoorTriggerVolume.generated.h"

/**
 * 
 */
UCLASS()
class CAPSTONE_API ADoorTriggerVolume : public ATriggerVolume
{
	GENERATED_BODY()
	
public:
	ADoorTriggerVolume();
	virtual void BeginPlay() override;

	UFUNCTION()
	void OnOverlapBegin(class AActor* OverlappedActor, class AActor* OtherActor);

	UFUNCTION()
	void OnOverlapEnd(class AActor* OverlappedActor, class AActor* OtherActor);

};
