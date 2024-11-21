// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "ProjectN.h"
#include "GameFramework/Actor.h"
#include "NBottle.generated.h"

UCLASS()
class PROJECTN_API ANBottle : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ANBottle();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;


//----------------------------------------------------------------------------------------------

public:
	void RemoveBottle();

public:
	void SetValue(int32 ExceptNum);
	void SetStart();
	void GoBack();
	void GoDown();
	void FixValue(int32 n);
	int32 GetValue();

private:
	UPROPERTY(VisibleAnywhere, Category = Mesh)
		UStaticMeshComponent* BottleMesh;

	UPROPERTY(VisibleAnywhere, Category = Mesh)
		UStaticMesh* Bottle_1;

	UPROPERTY(VisibleAnywhere, Category = Mesh)
		UStaticMesh* Bottle_2;

	UPROPERTY(VisibleAnywhere, Category = Mesh)
		UStaticMesh* Bottle_3;

	UPROPERTY(VisibleAnywhere, Category = Mesh)
		UStaticMesh* Bottle_4;

	UPROPERTY(VisibleAnywhere, Category = Mesh)
		UStaticMesh* Bottle_5;

	UPROPERTY(VisibleAnywhere, Category = Mesh)
		UStaticMesh* Bottle_6;

	UPROPERTY(VisibleAnywhere, Category = Mesh)
		UStaticMesh* Bottle_7;

	UPROPERTY(VisibleAnywhere, Category = Mesh)
		UStaticMesh* Bottle_8;

	UPROPERTY()
		int32 value;

private:
	bool IsMoving;
	bool IsGoBack = false;
	bool IsGoDown = false;
	float RunningTime;
	FVector StartLocation;
	FVector NewLocation;
	int32 FixedValue = 0;
};
