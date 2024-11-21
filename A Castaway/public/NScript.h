// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "ProjectN.h"
#include "Blueprint/UserWidget.h"
#include "NGameInstance.h"
#include "NScript.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTN_API UNScript : public UUserWidget
{
	GENERATED_BODY()
	
public:
	virtual void NativeConstruct() override;
	void SetScript(FString ScriptName);
	void SetEmotionValue(int32 ScriptNum);
	void StartVisibleAnimation();

	FScript* GetCurrentScript();

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
		class UTextBlock* LetterTB;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
		class UTextBlock* Answer1TB;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
		class UTextBlock* Answer2TB;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
		class UImage* HappyValue_1;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
		class UImage* SadValue_1;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
		class UImage* AngerValue_1;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
		class UImage* FearValue_1;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
		class UImage* HappyValue_2;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
		class UImage* SadValue_2;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
		class UImage* AngerValue_2;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
		class UImage* FearValue_2;

	UPROPERTY(Meta = (BindWidgetAnim), Transient)
		class UWidgetAnimation* FadeIn;


private:
	struct FScript* CurrentScript = nullptr;
	FString HappyFull;
	FString HappyHalf;
	FString SadFull;
	FString SadHalf;
	FString AngerFull;
	FString AngerHalf;
	FString FearFull;
	FString FearHalf;
	FString NoChange;
};
