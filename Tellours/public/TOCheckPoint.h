// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Tellours.h"
#include "GameFramework/Actor.h"
#include "Components/RectLightComponent.h"
#include "TOCheckPoint.generated.h"


UCLASS()
class TELLOURS_API ATOCheckPoint : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ATOCheckPoint();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;



public:
	UPROPERTY(VisibleAnywhere, Category = CheckPoint)
		UStaticMeshComponent* CheckPoint;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Lighting")
		URectLightComponent* RectLightComponent1;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Lighting")
		URectLightComponent* RectLightComponent2;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Lighting")
		URectLightComponent* RectLightComponent3;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Lighting")
		URectLightComponent* RectLightComponent4;

	UFUNCTION()
		void SavedGame();

	void SetLight(URectLightComponent* Light, int32 LightNum);
	URectLightComponent* SetLight(int32 LightNum);

private:
	bool IsSaved;

// 상호작용
public:
	UPROPERTY(VisibleAnywhere, Category = UI)
		class UWidgetComponent* InteractionWidget;

	void SetInteractionUIVisible(bool NewBool);
};
