// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Tellours.h"
#include "GameFramework/PlayerController.h"
#include "TOUIPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class TELLOURS_API ATOUIPlayerController : public APlayerController
{
	GENERATED_BODY()
	
protected:
	virtual void BeginPlay() override;

	UPROPERTY(EditDefaultsOnly, BlueprintReadwrite, Category = UI)
		TSubclassOf<class UUserWidget> UIWidgetClass;

	UPROPERTY()
		class UUserWidget* UIWidgetInstance;
};
