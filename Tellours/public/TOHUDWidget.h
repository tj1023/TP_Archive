// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Tellours.h"
#include "Blueprint/UserWidget.h"
#include "TOHUDWidget.generated.h"

/**
 * 
 */
UCLASS()
class TELLOURS_API UTOHUDWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
	void BindCharacterStat(class UTOCharacterStatComponent* NewCharacterStat);

protected:
	virtual void NativeConstruct() override;
	void UpdateCharacterStat();

private:
	TWeakObjectPtr<class UTOCharacterStatComponent> CurrentCharacterStat;

	UPROPERTY()
		class UProgressBar* HPBar;

	UPROPERTY()
		class UProgressBar* MPBar;

	UPROPERTY()
		class UProgressBar* EPBar;
};