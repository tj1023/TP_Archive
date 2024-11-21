// Fill out your copyright notice in the Description page of Project Settings.


#include "TOHUDWidget.h"
#include "Components/ProgressBar.h"
#include "TOCharacterStatComponent.h"

void UTOHUDWidget::BindCharacterStat(UTOCharacterStatComponent* NewCharacterStat)
{
	ABCHECK(nullptr != NewCharacterStat);
	CurrentCharacterStat = NewCharacterStat;
	NewCharacterStat->OnHPChanged.AddUObject(this, &UTOHUDWidget::UpdateCharacterStat);
	NewCharacterStat->OnMPChanged.AddUObject(this, &UTOHUDWidget::UpdateCharacterStat);
	NewCharacterStat->OnEPChanged.AddUObject(this, &UTOHUDWidget::UpdateCharacterStat);

	UpdateCharacterStat();
}

void UTOHUDWidget::NativeConstruct()
{
	Super::NativeConstruct();
	HPBar = Cast<UProgressBar>(GetWidgetFromName(TEXT("pbHP")));
	ABCHECK(nullptr != HPBar);

	MPBar = Cast<UProgressBar>(GetWidgetFromName(TEXT("pbMP")));
	ABCHECK(nullptr != MPBar);

	EPBar = Cast<UProgressBar>(GetWidgetFromName(TEXT("pbEP")));
	ABCHECK(nullptr != EPBar);
}

void UTOHUDWidget::UpdateCharacterStat()
{
	ABCHECK(CurrentCharacterStat.IsValid());

	HPBar->SetPercent(CurrentCharacterStat->GetHPRatio());
	MPBar->SetPercent(CurrentCharacterStat->GetMPRatio());
	EPBar->SetPercent(CurrentCharacterStat->GetEPRatio());
}
