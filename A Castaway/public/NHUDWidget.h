// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "ProjectN.h"
#include "Blueprint/UserWidget.h"
#include "NHUDWidget.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTN_API UNHUDWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
	void BindCharacterStat(class UNCharacterStatComponent* CharacterStat);
	void UpdateCharacterStat();
	void UpdateStatusEffect();
	void UpdateScriptCount(int32 count);
protected:
	virtual void NativeConstruct() override;

private:
	TWeakObjectPtr<class UNCharacterStatComponent> CurrentCharacterStat;

	// Progressbar
	UPROPERTY()
	class UProgressBar* E_bar0;

	UPROPERTY()
	class UProgressBar* E_bar1;

	UPROPERTY()
	class UProgressBar* E_bar2;

	UPROPERTY()
	class UProgressBar* E_bar3;

	UPROPERTY()
	class UTextBlock* Survival_time;

	UPROPERTY()
	class UImage* Status_Effect0;

	UPROPERTY()
	class UImage* Status_Effect1;

	UPROPERTY()
	class UImage* Status_Effect2;

	UPROPERTY()
	class UImage* Status_Effect3;
	
};
