// Fill out your copyright notice in the Description page of Project Settings.


#include "NPlayerController.h"
#include "NHUDWidget.h"
#include "NScript.h"
#include "NTabUI.h"
#include "NEndUI.h"
#include "NDieWidget.h"
#include "NESCWidget.h"

ANPlayerController::ANPlayerController()
{
	static ConstructorHelpers::FClassFinder<UNHUDWidget> UI_HUD_C(TEXT("/Game/UI/UI_HUD.UI_HUD_C"));
	if (UI_HUD_C.Succeeded())
	{
		HUDWidgetClass = UI_HUD_C.Class;
	}
	static ConstructorHelpers::FClassFinder<UUserWidget> Script(TEXT("/Game/UI/UI_Script.UI_Script_C"));
	if (Script.Succeeded()) {
		ScriptClass = Script.Class;
	}

	static ConstructorHelpers::FClassFinder<UUserWidget> Tab(TEXT("/Game/UI/UI_Tab.UI_Tab_C"));
	if (Tab.Succeeded()) {
		TabClass = Tab.Class;
	}

	static ConstructorHelpers::FClassFinder<UUserWidget> ESC(TEXT("/Game/UI/UI_ESC.UI_ESC_C"));
	if (ESC.Succeeded()) {
		ESCWidgetClass = ESC.Class;
	}

	static ConstructorHelpers::FClassFinder<UNEndUI> UI_END(TEXT("/Game/UI/UI_End.UI_End_C"));
	if (UI_END.Succeeded())
	{
		EndWidgetClass = UI_END.Class;
	}

	static ConstructorHelpers::FClassFinder<UNDieWidget> UI_DIE(TEXT("/Game/UI/UI_Die.UI_Die_C"));
	if (UI_DIE.Succeeded())
	{
		DieWidgetClass = UI_DIE.Class;
	}
}

void ANPlayerController::BeginPlay()
{
	Super::BeginPlay();

	/*HUDWidget = CreateWidget<UNHUDWidget>(this, HUDWidgetClass);
	HUDWidget->AddToViewport();*/
	FInputModeGameOnly InputMode;
	SetInputMode(InputMode);

	ScriptWidget = CreateWidget<UNScript>(this, ScriptClass);
	ScriptWidget->AddToViewport();
	ScriptWidget->SetVisibility(ESlateVisibility::Collapsed);

	TabWidget = CreateWidget<UNTabUI>(this, TabClass);
	TabWidget->AddToViewport();
	TabWidget->SetVisibility(ESlateVisibility::Collapsed);

	ESCWidget = CreateWidget<UNESCWidget>(this, ESCWidgetClass);
	ESCWidget->AddToViewport();
	ESCWidget->SetVisibility(ESlateVisibility::Collapsed);

	EndWidget = CreateWidget<UNEndUI>(this, EndWidgetClass);
	EndWidget->AddToViewport();
	EndWidget->SetVisibility(ESlateVisibility::Hidden);

	DieWidget = CreateWidget<UNDieWidget>(this, DieWidgetClass);
	DieWidget->AddToViewport();
	DieWidget->SetVisibility(ESlateVisibility::Hidden);
}

void ANPlayerController::OnPossess(APawn* aPawn)
{
	Super::OnPossess(aPawn);

	HUDWidget = CreateWidget<UNHUDWidget>(this, HUDWidgetClass);
	HUDWidget->AddToViewport();
}

UNHUDWidget* ANPlayerController::GetHUDWidget() const
{
	return HUDWidget;
}

/*
* 스크립트
*/
void ANPlayerController::ShowScript()
{
	ScriptWidget->SetVisibility(ESlateVisibility::Visible);
	ScriptWidget->StartVisibleAnimation();
}

void ANPlayerController::CloseScript()
{
	ScriptWidget->SetVisibility(ESlateVisibility::Collapsed);
}

void ANPlayerController::SetScript(FString ScriptName)
{
	ScriptWidget->SetScript(ScriptName);
}

UNScript* ANPlayerController::GetScriptWidget()
{
	return ScriptWidget;
}

/*
* Tab
*/
void ANPlayerController::ShowTab()
{
	HUDWidget->SetVisibility(ESlateVisibility::Collapsed);
	TabWidget->SetVisibility(ESlateVisibility::Visible);
}

void ANPlayerController::CloseTab()
{
	HUDWidget->SetVisibility(ESlateVisibility::Visible);
	TabWidget->SetVisibility(ESlateVisibility::Collapsed);
}

/*
* ESC
*/
void ANPlayerController::ShowESCUI()
{
	SetPause(true);
	GetWorld()->GetFirstPlayerController()->SetShowMouseCursor(true);
	SetInputMode(FInputModeGameAndUI());

	ESCWidget->SetVisibility(ESlateVisibility::Visible);
}

void ANPlayerController::RemoveESCUI()
{
	SetPause(false);
	GetWorld()->GetFirstPlayerController()->SetShowMouseCursor(false);
	SetInputMode(FInputModeGameOnly());

	ESCWidget->SetVisibility(ESlateVisibility::Collapsed);
}


/*
* EndUI
*/
void ANPlayerController::ShowEndUI()
{
	GetWorld()->GetFirstPlayerController()->SetShowMouseCursor(true);
	SetInputMode(FInputModeGameAndUI());

	EndWidget->SetVisibility(ESlateVisibility::Visible);
}

void ANPlayerController::RemoveEndUI()
{
	GetWorld()->GetFirstPlayerController()->SetShowMouseCursor(false);
	SetInputMode(FInputModeGameOnly());

	EndWidget->SetVisibility(ESlateVisibility::Hidden);
}


void ANPlayerController::ShowDieUI(int32 emotion)
{
	GetWorld()->GetFirstPlayerController()->SetShowMouseCursor(true);
	SetInputMode(FInputModeGameAndUI());
	DieWidget->SetDieText(emotion);
	DieWidget->SetVisibility(ESlateVisibility::Visible);
}

void ANPlayerController::RemoveDieUI()
{

}

void ANPlayerController::UpdateUI()
{
	HUDWidget->UpdateStatusEffect();
}
