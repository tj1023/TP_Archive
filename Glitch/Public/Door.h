// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Door.generated.h"

UCLASS()
class CAPSTONE_API ADoor : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ADoor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool CanOpenDoor;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	UStaticMeshComponent* MeshComponent;

	UPROPERTY(VisibleAnywhere, Category = UI)
	class UWidgetComponent* InteractionWidget;

	void SetInteractionUIVisible(bool NewBool);
	void Interaction();

	UFUNCTION(BlueprintImplementableEvent, Category = "Door")
	void OpenDoor();

	UFUNCTION(BlueprintImplementableEvent, Category = "Door")
	void CloseDoor();

	bool GetCanOpenDoor();
	bool IsOpened;
};
