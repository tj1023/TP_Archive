// Fill out your copyright notice in the Description page of Project Settings.


#include "TODeadWidget.h"
#include "Components/WidgetComponent.h"
#include "Blueprint/WidgetLayoutLibrary.h"

void UTODeadWidget::NativeConstruct()
{
	Super::NativeConstruct();

	
}

void UTODeadWidget::PlayDeadWidgetAnimation()
{
	/*UWidgetLayoutLibrary::RemoveAllWidgets(GetWorld());*/
	
	PlayAnimation(FadeIn);
}