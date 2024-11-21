// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Tellours.h"
#include "Blueprint/UserWidget.h"
#include "TODeadWidget.generated.h"

/**
 * 
 */
UCLASS()
class TELLOURS_API UTODeadWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	virtual void NativeConstruct() override;

public:
	void PlayDeadWidgetAnimation();

private:
	UPROPERTY(EditAnywhere, meta = (BindWidgetAnim), Transient)
		class UWidgetAnimation* FadeIn;
};
