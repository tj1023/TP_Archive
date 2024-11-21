// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Tellours.h"
#include "GameFramework/Actor.h"
#include "TOArmor.generated.h"

UCLASS()
class TELLOURS_API ATOArmor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ATOArmor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;



// 장비 관련
public:
	UPROPERTY(VisibleAnywhere, Category = Weapon)
		UStaticMeshComponent* Helmet;
};
