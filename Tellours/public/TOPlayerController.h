// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Tellours.h"
#include "GameFramework/PlayerController.h"
#include "TOPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class TELLOURS_API ATOPlayerController : public APlayerController
{
	GENERATED_BODY()

/*
* ���� �Լ���
*/
public:
	ATOPlayerController();

	virtual void BeginPlay() override;



/*
 * ��ų â ����
 */
public:
	void ShowSkillUI();
	void RemoveSkillUI();
	void SkillButton_Clicked();

protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = UI)
		TSubclassOf<class UTOSkillWidget> SkillWidgetClass;

private:
	UPROPERTY()
		class UTOSkillWidget* SkillWidget;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = UI, Meta = (AllowPrivateAccess))
		float IsSkillButtonClicked;
	
	bool UISkillVisible;


/*
* �κ��丮 
*/
public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = Item)
		TSubclassOf<class UTOInventory> InventoryClass;
	
	void OpenInventoryUI();
	void CloseInventoryUI();

private:
	UPROPERTY()
		class UTOInventory* InventoryWidget;

	bool UIInventoryVisible;


/*
* ��ũ��Ʈ
*/
public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = Script)
		TSubclassOf<class UTOScript> ScriptClass;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = Script)
		TSubclassOf<class UTOSaveScript> SaveScriptClass;

	void ShowScriptUI();
	void CloseScriptUI();
	void ShowSaveScriptUI();
private:
	UPROPERTY()
		class UTOScript* ScriptWidget;
	
	UPROPERTY()
		class UTOSaveScript* SaveScriptWidget;

	bool UIScriptVisible;
	bool UIChekPointScriptVisible;

/*
* Setting UI ����
*/
public:
	void ShowSettingUI();
	void RemoveSettingUI();

protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = UI)
		TSubclassOf<class UTOSettingWidget> SettingWidgetClass;

private:
	UPROPERTY()
		class UTOSettingWidget* SettingWidget;



/*
* HUD
*/
public:
	class UTOHUDWidget* GetHUDWidget() const;

protected:
	UPROPERTY(EditDefaultsOnly, BLueprintReadWrite, Category = UI)
		TSubclassOf<class UTOHUDWidget> HUDWidgetClass;

private:
	UPROPERTY()
		class UTOHUDWidget* HUDWidget;

};
