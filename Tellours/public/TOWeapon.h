// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Tellours.h"
#include "GameFramework/Actor.h"
#include "TOWeapon.generated.h"

UCLASS()
class TELLOURS_API ATOWeapon : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ATOWeapon();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;



	/*
	* 무기 관련 
	*/
public:
	UPROPERTY(VisibleAnywhere, Category = Weapon)
	UStaticMeshComponent* Weapon;

};
