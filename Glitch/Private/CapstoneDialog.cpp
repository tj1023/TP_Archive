// Fill out your copyright notice in the Description page of Project Settings.


#include "CapstoneDialog.h"
#include "Components/TextBlock.h"
#include "CapstoneHUDWidget.h"
#include "CapstoneController.h"
#include <Kismet/GameplayStatics.h>

void UCapstoneDialog::NativeConstruct()
{
	Super::NativeConstruct();

	textBlock = Cast<UTextBlock>(GetWidgetFromName("DialogText"));
}

void UCapstoneDialog::NativeOnListItemObjectSet(UObject* ListItemObject)
{
	IUserObjectListEntry::NativeOnListItemObjectSet(ListItemObject);

	UCapstoneHUDWidget* HUDWidget = Cast<UCapstoneHUDWidget>(Cast<ACapstoneController>(UGameplayStatics::GetPlayerController(GetWorld(), 0))->GetHUDWidget());

	textBlock->SetText(FText::FromString(HUDWidget->GetDialogText()));

	PlayAnimation(FadeIn, false);
}