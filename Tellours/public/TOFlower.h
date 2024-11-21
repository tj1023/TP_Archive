// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Tellours.h"
#include "GameFramework/Actor.h"
#include "Components/PointLightComponent.h"
#include "TOFlower.generated.h"

UCLASS()
class TELLOURS_API ATOFlower : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ATOFlower();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;



/*
* 기본 구성 요소
*/
public:
	UPROPERTY(VisibleAnywhere, Category = FieldObject)
		UStaticMeshComponent* ObjectMesh;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Lighting")
		TArray<UPointLightComponent*> PointLightArray;
	


/*
* 상호작용
*/	
public:
	UPROPERTY(VisibleAnywhere, Category = UI)
	class UWidgetComponent* InteractionWidget;

	void SetInteractionUIVisible(bool NewBool);

};
