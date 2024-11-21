// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Tellours.h"
#include "Blueprint/UserWidget.h"
#include "TOPrologueWidget.generated.h"

/**
 * 
 */
UCLASS()
class TELLOURS_API UTOPrologueWidget : public UUserWidget
{
	GENERATED_BODY()
	
protected:
	virtual void NativeConstruct() override;

	TWeakObjectPtr<USkeletalMeshComponent> TargetComponent;

	UPROPERTY()
		class UButton* StartButton;

private:
	UFUNCTION()
		void OnStartClicked();
};
