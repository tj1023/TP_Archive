// Fill out your copyright notice in the Description page of Project Settings.


#include "NESCWidget.h"
#include "UMG.h"
#include "NPlayerController.h"

/*
* 기본 생성자
*/
void UNESCWidget::NativeConstruct()
{
	Super::NativeConstruct();

	NPlayerController = Cast<ANPlayerController>(GetWorld()->GetFirstPlayerController());

	Button_Continue = Cast<UButton>(GetWidgetFromName(TEXT("BT_Continue")));
	Button_MainMenu = Cast<UButton>(GetWidgetFromName(TEXT("BT_MainMenu")));

	BindButtonClickEvents();
}

void UNESCWidget::BindButtonClickEvents()
{
	Button_Continue->OnClicked.Clear();
	Button_MainMenu->OnClicked.Clear();

	Button_Continue->OnClicked.AddDynamic(this, &UNESCWidget::ButtonClicked_Continue);
	Button_MainMenu->OnClicked.AddDynamic(this, &UNESCWidget::ButtonClicked_MainMenu);
}

void UNESCWidget::ButtonClicked_Continue()
{
	NPlayerController->RemoveESCUI();
}

void UNESCWidget::ButtonClicked_MainMenu()
{
	UGameplayStatics::OpenLevel(GetWorld(), TEXT("StartMap"));
}