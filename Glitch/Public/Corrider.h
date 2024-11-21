// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Chunk.h"
#include "Corrider.generated.h"

/**
 * 
 */
UCLASS()
class CAPSTONE_API ACorrider : public AChunk
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ACorrider();

	virtual void SpawnTypeActor() override;

	UPROPERTY(EditAnywhere)
	TSubclassOf<class AActor> BP_Corrider_2Way;

	UPROPERTY(EditAnywhere)
	TSubclassOf<class AActor> BP_Corrider_Vertical_2Way;

	UPROPERTY(EditAnywhere)
	TSubclassOf<class AActor> BP_Corrider_3Way;

	UPROPERTY(EditAnywhere)
	TSubclassOf<class AActor> BP_Corrider_4Way;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:
	UPROPERTY(EditAnywhere, Category = "Components")
	UStaticMeshComponent* MainMesh;
};