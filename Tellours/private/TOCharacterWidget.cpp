// Fill out your copyright notice in the Description page of Project Settings.


#include "TOCharacterWidget.h"
#include "TOCharacterStatComponent.h"
#include "TOEnemyStatComponent.h"
#include "TOBossStatComponent.h"
#include "Components/ProgressBar.h"


/*
*  HP바 연동
*/
void UTOCharacterWidget::NativeConstruct()
{
	Super::NativeConstruct();
	HPProgressBar = Cast<UProgressBar>(GetWidgetFromName(TEXT("PB_HPBar")));
	ABCHECK(nullptr != HPProgressBar);
	UpdateHPWidget();
}



/*
*  캐릭터 및 Enemy HP 매핑
*/
void UTOCharacterWidget::BindCharacterStat(UTOCharacterStatComponent* NewCharacterStat)
{
	ABCHECK(nullptr != NewCharacterStat);

	CurrentCharacterStat = NewCharacterStat;
	NewCharacterStat->OnHPChanged.AddUObject(this, &UTOCharacterWidget::UpdateHPWidget);
}

void UTOCharacterWidget::BindEnemyStat(UTOEnemyStatComponent* NewEnemyStat)
{
	ABCHECK(nullptr != NewEnemyStat);

	CurrentEnemyStat = NewEnemyStat;
	NewEnemyStat->OnHPChanged.AddUObject(this, &UTOCharacterWidget::UpdateHPWidget);
}

void UTOCharacterWidget::BindBossStat(UTOBossStatComponent* NewBossStat)
{
	ABCHECK(nullptr != NewBossStat);

	CurrentBossStat = NewBossStat;
	NewBossStat->OnHPChanged.AddUObject(this, &UTOCharacterWidget::UpdateHPWidget);
}



/*
* HP바 갱신
*/
void UTOCharacterWidget::UpdateHPWidget()
{
	if (CurrentCharacterStat.IsValid())
	{
		if (nullptr != HPProgressBar)
		{
			HPProgressBar->SetPercent(CurrentCharacterStat->GetHPRatio());
		}
	}

	else if (CurrentEnemyStat.IsValid())
	{
		if (nullptr != HPProgressBar)
		{
			HPProgressBar->SetPercent(CurrentEnemyStat->GetHPRatio());
		}
	}
	else if (CurrentBossStat.IsValid())
	{
		if (nullptr != HPProgressBar)
		{
			HPProgressBar->SetPercent(CurrentBossStat->GetHPRatio());
		}
	}
}
