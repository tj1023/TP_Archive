// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "ProjectN.h"
#include "Components/ActorComponent.h"
#include "NBottle.h"
#include "NPlayerState.h"
#include "NGameSystemComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class PROJECTN_API UNGameSystemComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UNGameSystemComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;


// Bottle Spawn
public:
	UFUNCTION()
		void StartSystem(UNCharacterStatComponent* CharacterStat);

	void SpawnBottle();
	void SpawnTutorialBottle(int32 location);
	ANBottle* GetBottle1();
	ANBottle* GetBottle2();
		
private:
	ANBottle* Bottle1;
	ANBottle* Bottle2;

// ��ũ��Ʈ ����
public:
	void FixValue(int32 n);
	void DestroyOtherBottle();

private:
	int32 FixedValue = 0;
	bool DestroyOtherBottleOn = false;
};
