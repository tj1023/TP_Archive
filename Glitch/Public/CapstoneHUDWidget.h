// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "CapstoneDialog.h"
#include "CapstoneHUDWidget.generated.h"

/**
 * 
 */
UCLASS()
class CAPSTONE_API UCapstoneHUDWidget : public UUserWidget
{
	GENERATED_BODY()

	FTimerHandle AlphaTimerHandle;

public:
	UCapstoneHUDWidget(const FObjectInitializer &ObjectInitializer);

	void SetSPBarPercent(float n);
	float GetSPBarPercent(void);
	void SetInteractionUI(bool tf);
	void SetApparitionUI(bool tf);
	void Clear();
	void ShowDialog(FString contentText);

	FString GetDialogText();

protected:
	virtual void NativeConstruct() override;

private:
	UPROPERTY()
	class UProgressBar* SPBar;

	UPROPERTY()
	class UImage* ImageInteraction;

	UPROPERTY()
	class UImage* ImageApparition;

	UPROPERTY()
	class UImage* WhiteImage;


	UPROPERTY()
	class UTextBlock* RamainItem;

	UPROPERTY()
	class UListView* DialogList;

	FString DialogText;

	TSubclassOf<class UCapstoneDialog> DialogClass;

	float SPPercent;
};
