// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Tellours.h"
#include "GameFramework/Actor.h"
#include "TOLevel2_Fight.generated.h"

UCLASS()
class TELLOURS_API ATOLevel2_Fight : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ATOLevel2_Fight();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;


public:
	void StartPhase();
	void SetInteractionUIVisible(bool NewBool);

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Setting)
		int32 TotalKill;

private:
	UPROPERTY(VisibleAnywhere, Category = Item)
		UStaticMeshComponent* Statue;

	UPROPERTY(VisibleAnywhere, Category = UI)
		class UWidgetComponent* InteractionWidget;
	


};
