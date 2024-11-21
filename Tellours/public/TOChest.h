// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Tellours.h"
#include "GameFramework/Actor.h"
#include "TOChestSpawner.h"
#include "TOCharacter.h"
#include "TOChest.generated.h"

UCLASS()
class TELLOURS_API ATOChest : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ATOChest();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;



public:
	UPROPERTY(VisibleAnywhere, Category = Chest)
		UStaticMeshComponent* Chest;

	void ChestOpen(ATOCharacter* Character);
	bool GetIsOpened();



/*
* ���� ����
*/
public:
	FTimerHandle ChestDeadTimeHandle = { };
	FTimerHandle ChestSpawnTimeHandle = { };

	void SetMotherSpawner(ATOChestSpawner* NewSpawner);

private:
	ATOChestSpawner* MotherSpawner;



/*
* ���� ��ȣ�ۿ�
*/
public:
	UPROPERTY(VisibleAnywhere, Category = UI)
		class UWidgetComponent* InteractionWidget;

	void SetInteractionUIVisible(bool NewBool);

private:
	UPROPERTY(EditAnywhere, Category = Chest, Meta = (AllowPrivateAccess = true))
		bool RequiredKey;

	bool IsOpened;
};
