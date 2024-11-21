// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "CapstoneESCUI.generated.h"

/**
 * 
 */
UCLASS()
class CAPSTONE_API UCapstoneESCUI : public UUserWidget
{
	GENERATED_BODY()
	
public:
	virtual void NativeConstruct() override;

private:
	UPROPERTY()
	class ACapstoneController* Controller;

	UPROPERTY()
	class UButton* Button_Setting;

	UPROPERTY()
	class UButton* Button_Continue;

	UPROPERTY()
	class UButton* Button_Quit;

	UFUNCTION()
	void ButtonClicked_Setting();

	UFUNCTION()
	void ButtonClicked_Continue();
};
