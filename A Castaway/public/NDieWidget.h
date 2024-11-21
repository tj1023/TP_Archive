// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "ProjectN.h"
#include "Blueprint/UserWidget.h"
#include "NDieWidget.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTN_API UNDieWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
	virtual void NativeConstruct() override;
	void SetDieText(int32 emotion);
	void BindButtonClickEvents();
private:
	UPROPERTY()
	class UTextBlock* Text1;

	UPROPERTY()
	class UTextBlock* Text2;

	UPROPERTY()
	class UTextBlock* Text3;

	UPROPERTY()
	class UTextBlock* Text4;

	UPROPERTY()
	class UTextBlock* Text5;

	UPROPERTY()
	class UTextBlock* Text6;

	UPROPERTY()
	class UTextBlock* Text7;

	UPROPERTY()
	class UTextBlock* Text8;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	class UButton* Button_MainMenu;

	UFUNCTION(BlueprintCallable)
	void ButtonClicked_MainMenu();

};
