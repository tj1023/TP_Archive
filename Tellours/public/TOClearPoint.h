// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Tellours.h"
#include "GameFramework/Actor.h"
#include "TOClearPoint.generated.h"

UCLASS()
class TELLOURS_API ATOClearPoint : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ATOClearPoint();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;


public:
	UPROPERTY(VisibleAnywhere, Category = ClearPoint)
		UStaticMeshComponent* ClearPoint;

	void CheckPointCondition();
private:
	TArray<int32> InventoryItem;


/*
* ��ȣ�ۿ�
*/
public:
	UPROPERTY(VisibleAnywhere, Category = UI)
		class UWidgetComponent* InteractionWidget;

	void SetInteractionUIVisible(bool NewBool);
};
