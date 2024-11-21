// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Chunk.h"
#include "Room.generated.h"

/**
 * 
 */
UCLASS()
class CAPSTONE_API ARoom : public AChunk
{
	GENERATED_BODY()
	
public:
	// Sets default values for this actor's properties
	ARoom();

	virtual void SpawnTypeActor() override;

	UPROPERTY(EditAnywhere)
	TSubclassOf<class AActor> BP_BathRoom;

	UPROPERTY(EditAnywhere)
	TSubclassOf<class AActor> BP_LibraryRoom;

	UPROPERTY(EditAnywhere)
	TSubclassOf<class AActor> BP_RestaurantRoom;

	UPROPERTY(EditAnywhere)
	TSubclassOf<class AActor> BP_StorageRoom;

	UPROPERTY(EditAnywhere)
	TSubclassOf<class AActor> BP_Room1;

	UPROPERTY(EditAnywhere)
	TSubclassOf<class AActor> BP_Room2;

	UPROPERTY(EditAnywhere)
	TSubclassOf<class AActor> BP_Room3;

	UPROPERTY(EditAnywhere)
	TSubclassOf<class AActor> BP_Room4;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:
	UPROPERTY(EditAnywhere, Category = "Components")
	UStaticMeshComponent* MainMesh;

};

