// Fill out your copyright notice in the Description page of Project Settings.


#include "TOSettingWidget.h"
#include "UMG.h"
#include "TOPlayerController.h"

/*
* 기본 생성자
*/
void UTOSettingWidget::NativeConstruct()
{
	Super::NativeConstruct();

	TOPlayerController = Cast<ATOPlayerController>(GetWorld()->GetFirstPlayerController());

	Button_Return = Cast<UButton>(GetWidgetFromName(TEXT("BT_Return")));
	Button_Setting = Cast<UButton>(GetWidgetFromName(TEXT("BT_Setting")));
	Button_Exit = Cast<UButton>(GetWidgetFromName(TEXT("BT_Exit")));

	BindButtonClickEvents();
}

void UTOSettingWidget::BindButtonClickEvents()
{
	Button_Return->OnClicked.Clear();
	Button_Setting->OnClicked.Clear();
	Button_Exit->OnClicked.Clear();

	Button_Return->OnClicked.AddDynamic(this, &UTOSettingWidget::ButtonClicked_Return);
	Button_Setting->OnClicked.AddDynamic(this, &UTOSettingWidget::ButtonClicked_Setting);
	Button_Exit->OnClicked.AddDynamic(this, &UTOSettingWidget::ButtonClicked_Exit);
}

void UTOSettingWidget::ButtonClicked_Return()
{
	TOPlayerController->RemoveSettingUI();
}

void UTOSettingWidget::ButtonClicked_Setting()
{

}

void UTOSettingWidget::ButtonClicked_Exit()
{
	FGenericPlatformMisc::RequestExit(true);
}