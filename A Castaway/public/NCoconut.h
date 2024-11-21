// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "ProjectN.h"
#include "GameFramework/Actor.h"
#include "NCoconut.generated.h"

UCLASS()
class PROJECTN_API ANCoconut : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ANCoconut();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:
	UPROPERTY(VisibleAnywhere, Category = Mesh)
		UStaticMeshComponent* Coconut;
};
