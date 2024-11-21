// Fill out your copyright notice in the Description page of Project Settings.


#include "CapstoneController.h"
#include "CapstoneSettingUI.h"
#include "CapstoneEndingUI.h"
#include "CapstoneESCUI.h"
#include "Kismet/GameplayStatics.h"
#include "CapstoneHUDWidget.h"
#include "Components/TextBlock.h"

ACapstoneController::ACapstoneController()
{
	// Setting UI
	static ConstructorHelpers::FClassFinder<UUserWidget> Setting(TEXT("/Game/UI/UI_Setting.UI_Setting_C"));
	if (Setting.Succeeded()) {
		SettingUIClass = Setting.Class;
	}

	// Ending UI
	static ConstructorHelpers::FClassFinder<UUserWidget> Ending(TEXT("/Game/UI/UI_End.UI_End_C"));
	if (Ending.Succeeded()) {
		EndingUIClass = Ending.Class;
	}

	// ESC UI
	static ConstructorHelpers::FClassFinder<UUserWidget> ESC(TEXT("/Game/UI/UI_ESC.UI_ESC_C"));
	if (ESC.Succeeded()) {
		ESCUIClass = ESC.Class;
	}

	// HUD
	static ConstructorHelpers::FClassFinder<UCapstoneHUDWidget> UI_HUD_C(TEXT("/Game/UI/UI_HUD.UI_HUD_C"));
	if (UI_HUD_C.Succeeded()) {
		HUDWidgetClass = UI_HUD_C.Class;
	}
}


void ACapstoneController::BeginPlay()
{
	Super::BeginPlay();

	// Setting UI
	SettingWidget = CreateWidget<UCapstoneSettingUI>(this, SettingUIClass);
	SettingWidget->AddToViewport();
	SettingWidget->SetVisibility(ESlateVisibility::Collapsed);

	// Ending UI
	EndingWidget = CreateWidget<UCapstoneEndingUI>(this, EndingUIClass);
	EndingWidget->AddToViewport();
	EndingWidget->SetVisibility(ESlateVisibility::Collapsed);

	// ESC UI
	ESCWidget = CreateWidget<UCapstoneESCUI>(this, ESCUIClass);
	ESCWidget->AddToViewport();
	ESCWidget->SetVisibility(ESlateVisibility::Collapsed);

	// HUD
	HUDWidget = CreateWidget<UCapstoneHUDWidget>(this, HUDWidgetClass);
	HUDWidget->AddToViewport();
	HUDWidget->SetVisibility(ESlateVisibility::Collapsed);
}


/*
* SettingUI
*/
void ACapstoneController::ShowSetting()
{
	SetPause(true);
	HUDWidget->SetVisibility(ESlateVisibility::Collapsed);
	GetWorld()->GetFirstPlayerController()->SetShowMouseCursor(true);
	ESCWidget->SetVisibility(ESlateVisibility::Collapsed);
	SettingWidget->SetVisibility(ESlateVisibility::Visible);
	SetInputMode(FInputModeUIOnly());
}

void ACapstoneController::CloseSetting()
{
	SetPause(false);
	HUDWidget->SetVisibility(ESlateVisibility::Visible);
	GetWorld()->GetFirstPlayerController()->SetShowMouseCursor(false);
	SettingWidget->SetVisibility(ESlateVisibility::Collapsed);
	SetInputMode(FInputModeGameOnly());
}


void ACapstoneController::SettingUISetText(float value)
{
	if (value < 0.1f)
		value = 0.0f;
	FString VolumeString = FString::Printf(TEXT("%.1f"), value * 100.0f);
	SettingWidget->SoundVolume1->SetText(FText::FromString(VolumeString));
}

/*
* Ending UI
*/
void ACapstoneController::ShowTrueEndingUI()
{
	HUDWidget->Clear();
	GetWorld()->GetFirstPlayerController()->SetShowMouseCursor(true);
	SetInputMode(FInputModeUIOnly());
	//EndingWidget->SetVisibility(ESlateVisibility::Visible);
}
void ACapstoneController::ShowFalseEndingUI()
{
	SetPause(true);
	HUDWidget->SetVisibility(ESlateVisibility::Hidden);
	GetWorld()->GetFirstPlayerController()->SetShowMouseCursor(true);
	UGameplayStatics::OpenLevel(GetWorld(), TEXT("BadEnding"));
	SetInputMode(FInputModeUIOnly());
	EndingWidget->SetVisibility(ESlateVisibility::Visible);
}

// HUD
UCapstoneHUDWidget* ACapstoneController::GetHUDWidget() const
{
	return HUDWidget;
}

/*
* ESC UI
*/
void ACapstoneController::ShowESC()
{
	SetPause(true);
	HUDWidget->SetVisibility(ESlateVisibility::Collapsed);
	GetWorld()->GetFirstPlayerController()->SetShowMouseCursor(true);
	ESCWidget->SetVisibility(ESlateVisibility::Visible);
	SetInputMode(FInputModeUIOnly());
}

void ACapstoneController::CloseESC()
{
	SetPause(false);
	HUDWidget->SetVisibility(ESlateVisibility::Visible);
	GetWorld()->GetFirstPlayerController()->SetShowMouseCursor(false);
	ESCWidget->SetVisibility(ESlateVisibility::Collapsed);
	SetInputMode(FInputModeGameOnly());
}
