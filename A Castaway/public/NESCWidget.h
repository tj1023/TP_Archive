// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "ProjectN.h"
#include "Blueprint/UserWidget.h"
#include "NESCWidget.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTN_API UNESCWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
	virtual void NativeConstruct() override;

	void BindButtonClickEvents();

private:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
		class ANPlayerController* NPlayerController;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
		class UButton* Button_Continue;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
		class UButton* Button_MainMenu;

	UFUNCTION(BlueprintCallable)
		void ButtonClicked_Continue();

	UFUNCTION(BlueprintCallable)
		void ButtonClicked_MainMenu();
};
