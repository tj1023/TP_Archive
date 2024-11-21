// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "ProjectN.h"
#include "GameFramework/PlayerController.h"
#include "NPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTN_API ANPlayerController : public APlayerController
{
	GENERATED_BODY()
	
public:
	ANPlayerController();

	virtual void BeginPlay() override;
	virtual void OnPossess(APawn* aPawn) override;

/*
* 스크립트
*/
public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = Script)
		TSubclassOf<class UNScript> ScriptClass;

	void ShowScript();
	void CloseScript();
	void SetScript(FString ScriptName);
	UNScript* GetScriptWidget();

private:
	UPROPERTY()
		class UNScript* ScriptWidget;

/*
* HUD
*/
public:
	class UNHUDWidget* GetHUDWidget() const;
	void UpdateUI(void);
protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = UI)
	TSubclassOf<class UNHUDWidget> HUDWidgetClass;

private:
	UPROPERTY()
	class UNHUDWidget* HUDWidget;

/*
* Tab
*/
public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = Tab)
	TSubclassOf<class UNTabUI> TabClass;

	void ShowTab();
	void CloseTab();

private:
	UPROPERTY()
	class UNTabUI* TabWidget;

/*
* ESC
*/
public:
	void ShowESCUI();
	void RemoveESCUI();

protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = UI)
		TSubclassOf<class UNESCWidget> ESCWidgetClass;

private:
	UPROPERTY()
		class UNESCWidget* ESCWidget;

/*
* End UI
*/
public:
	void ShowEndUI();
	void RemoveEndUI();

protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = UI)
	TSubclassOf<class UNEndUI> EndWidgetClass;

private:
	UPROPERTY()
	class UNEndUI* EndWidget;

/*
* Die UI
*/
public:
	void ShowDieUI(int32 emotion);
	void RemoveDieUI();

protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = UI)
	TSubclassOf<class UNDieWidget> DieWidgetClass;

private:
	UPROPERTY()
	class UNDieWidget* DieWidget;
};
