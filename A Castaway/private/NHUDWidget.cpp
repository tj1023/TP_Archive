// Fill out your copyright notice in the Description page of Project Settings.


#include "NHUDWidget.h"
#include "Components/ProgressBar.h"
#include "Components/TextBlock.h"
#include "Components/Image.h"
#include "NCharacterStatComponent.h"

void UNHUDWidget::BindCharacterStat(UNCharacterStatComponent* CharacterStat)
{
	NCHECK(nullptr != CharacterStat);
	CurrentCharacterStat = CharacterStat;
	CharacterStat->OnEmotionChanged.AddUObject(this, &UNHUDWidget::UpdateCharacterStat);
}

void UNHUDWidget::NativeConstruct()
{
	Super::NativeConstruct();

	// Progressbar
	E_bar0 = Cast<UProgressBar>(GetWidgetFromName(TEXT("ProgressBar0")));
	NCHECK(nullptr != E_bar0);
	E_bar1 = Cast<UProgressBar>(GetWidgetFromName(TEXT("ProgressBar1")));
	NCHECK(nullptr != E_bar1);
	E_bar2 = Cast<UProgressBar>(GetWidgetFromName(TEXT("ProgressBar2")));
	NCHECK(nullptr != E_bar2);
	E_bar3 = Cast<UProgressBar>(GetWidgetFromName(TEXT("ProgressBar3")));
	NCHECK(nullptr != E_bar3);

	// TextBlock
	Survival_time = Cast<UTextBlock>(GetWidgetFromName(TEXT("TSurvival_time")));
	NCHECK(nullptr != Survival_time);

	// Image
	Status_Effect0 = Cast<UImage>(GetWidgetFromName(TEXT("IStatus_Effect0")));
	NCHECK(nullptr != Status_Effect0);
	Status_Effect1 = Cast<UImage>(GetWidgetFromName(TEXT("IStatus_Effect1")));
	NCHECK(nullptr != Status_Effect1);
	Status_Effect2 = Cast<UImage>(GetWidgetFromName(TEXT("IStatus_Effect2")));
	NCHECK(nullptr != Status_Effect2);
	Status_Effect3 = Cast<UImage>(GetWidgetFromName(TEXT("IStatus_Effect3")));
	NCHECK(nullptr != Status_Effect3);

	CurrentCharacterStat = nullptr;
}

void UNHUDWidget::UpdateCharacterStat()
{
	NCHECK(CurrentCharacterStat.IsValid());

	E_bar0->SetPercent(CurrentCharacterStat->GetHPRatio(0));
	E_bar1->SetPercent(CurrentCharacterStat->GetHPRatio(1));
	E_bar2->SetPercent(CurrentCharacterStat->GetHPRatio(2));
	E_bar3->SetPercent(CurrentCharacterStat->GetHPRatio(3));
}

void UNHUDWidget::UpdateStatusEffect()
{
	CurrentCharacterStat->GetStatusEffect(0) ?
		Status_Effect0->SetVisibility(ESlateVisibility::Visible) : Status_Effect0->SetVisibility(ESlateVisibility::Hidden);
	CurrentCharacterStat->GetStatusEffect(1) ?
		Status_Effect1->SetVisibility(ESlateVisibility::Visible) : Status_Effect1->SetVisibility(ESlateVisibility::Hidden);
	CurrentCharacterStat->GetStatusEffect(2) ?
		Status_Effect2->SetVisibility(ESlateVisibility::Visible) : Status_Effect2->SetVisibility(ESlateVisibility::Hidden);
	CurrentCharacterStat->GetStatusEffect(3) ?
		Status_Effect3->SetVisibility(ESlateVisibility::Visible) : Status_Effect3->SetVisibility(ESlateVisibility::Hidden);
}


void UNHUDWidget::UpdateScriptCount(int32 count)
{
	FString text = FString::Format(TEXT("read {0}'s scripts"), { count });
	Survival_time->SetText(FText::FromString(text));
	Survival_time->SetVisibility(ESlateVisibility::Visible);
}