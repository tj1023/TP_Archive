// Fill out your copyright notice in the Description page of Project Settings.


#include "CapstoneESCUI.h"
#include "CapstoneController.h"
#include "Components/Button.h"

void UCapstoneESCUI::NativeConstruct()
{
	Super::NativeConstruct();

	Controller = Cast<ACapstoneController>(GetWorld()->GetFirstPlayerController());

	Button_Setting = Cast<UButton>(GetWidgetFromName(TEXT("setting")));
	Button_Continue = Cast<UButton>(GetWidgetFromName(TEXT("continue")));
	Button_Setting->OnClicked.AddDynamic(this, &UCapstoneESCUI::ButtonClicked_Setting);
	Button_Continue->OnClicked.AddDynamic(this, &UCapstoneESCUI::ButtonClicked_Continue);
}

void UCapstoneESCUI::ButtonClicked_Setting()
{
	Controller->ShowSetting();
}

void UCapstoneESCUI::ButtonClicked_Continue()
{
	Controller->CloseESC();
}
