// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "CapstoneController.generated.h"

/**
 * 
 */
UCLASS()
class CAPSTONE_API ACapstoneController : public APlayerController
{
	GENERATED_BODY()
	ACapstoneController();
	virtual void BeginPlay() override;
	
	/*
	* Setting UI
	*/
public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = Setting)
	TSubclassOf<class UCapstoneSettingUI> SettingUIClass;

	void ShowSetting();
	void CloseSetting(); 
	void SettingUISetText(float value);
private:
	UPROPERTY()
	class UCapstoneSettingUI* SettingWidget;

	/*
	* Ending UI
	*/
public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = Setting)
	TSubclassOf<class UCapstoneEndingUI> EndingUIClass;

	void ShowTrueEndingUI();
	void ShowFalseEndingUI();

private:
	UPROPERTY()
	class UCapstoneEndingUI* EndingWidget;

	/*
	* HUD
	*/
public:
	class UCapstoneHUDWidget* GetHUDWidget() const;

protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = UI)
	TSubclassOf<class UCapstoneHUDWidget> HUDWidgetClass;

	UPROPERTY(BlueprintReadWrite, Category = UI)
	class UCapstoneHUDWidget* HUDWidget;

	/*
	* ESC UI
	*/
public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = Setting)
	TSubclassOf<class UCapstoneESCUI> ESCUIClass;

	void ShowESC();
	void CloseESC();

private:
	UPROPERTY()
	class UCapstoneESCUI* ESCWidget;
};
