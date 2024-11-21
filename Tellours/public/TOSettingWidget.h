// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Tellours.h"
#include "Blueprint/UserWidget.h"
#include "TOSettingWidget.generated.h"

/**
 * 
 */
UCLASS()
class TELLOURS_API UTOSettingWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
	// ��������Ʈ ���ε� �ʱ�ȭ �Լ�.
	void BindButtonClickEvents();

	virtual void NativeConstruct() override;

private:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
		class ATOPlayerController* TOPlayerController;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
		class UButton* Button_Return;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
		class UButton* Button_Setting;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
		class UButton* Button_Exit;

	UFUNCTION(BlueprintCallable)
		void ButtonClicked_Return();

	UFUNCTION(BlueprintCallable)
		void ButtonClicked_Setting();

	UFUNCTION(BlueprintCallable)
		void ButtonClicked_Exit();
};
