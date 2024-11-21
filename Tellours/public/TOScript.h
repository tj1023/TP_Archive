// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Tellours.h"
#include "Blueprint/UserWidget.h"
#include "TOScript.generated.h"

/**
 * 
 */
UCLASS()
class TELLOURS_API UTOScript : public UUserWidget
{
	GENERATED_BODY()
	
public:
	virtual void NativeConstruct() override;
	
public:
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	class UTextBlock* TitleText;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	class UButton* SkipButton;

	//UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	//class UImage* ScriptImage;

	UFUNCTION(BlueprintCallable)
	void SkipButtonCliked();
	
private:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	class ATOPlayerController* TOPlayerController;
	
};
