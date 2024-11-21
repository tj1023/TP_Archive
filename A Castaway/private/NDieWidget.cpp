// Fill out your copyright notice in the Description page of Project Settings.


#include "NDieWidget.h"
#include "Components/TextBlock.h"
#include "UMG.h"

void UNDieWidget::NativeConstruct()
{
	Text1 = Cast<UTextBlock>(GetWidgetFromName(TEXT("TextBlock_dead0")));
	NCHECK(nullptr != Text1);
	Text2 = Cast<UTextBlock>(GetWidgetFromName(TEXT("TextBlock_dead1")));
	NCHECK(nullptr != Text2);
	Text3 = Cast<UTextBlock>(GetWidgetFromName(TEXT("TextBlock_dead2")));
	NCHECK(nullptr != Text3);
	Text4 = Cast<UTextBlock>(GetWidgetFromName(TEXT("TextBlock_dead3")));
	NCHECK(nullptr != Text4);
	Text5 = Cast<UTextBlock>(GetWidgetFromName(TEXT("TextBlock_dead4")));
	NCHECK(nullptr != Text5);
	Text6 = Cast<UTextBlock>(GetWidgetFromName(TEXT("TextBlock_dead5")));
	NCHECK(nullptr != Text6);
	Text7 = Cast<UTextBlock>(GetWidgetFromName(TEXT("TextBlock_dead6")));
	NCHECK(nullptr != Text7);
	Text8 = Cast<UTextBlock>(GetWidgetFromName(TEXT("TextBlock_dead7")));
	NCHECK(nullptr != Text8);


	Text1->SetVisibility(ESlateVisibility::Hidden);
	Text2->SetVisibility(ESlateVisibility::Hidden);
	Text3->SetVisibility(ESlateVisibility::Hidden);
	Text4->SetVisibility(ESlateVisibility::Hidden);
	Text5->SetVisibility(ESlateVisibility::Hidden);
	Text6->SetVisibility(ESlateVisibility::Hidden);
	Text7->SetVisibility(ESlateVisibility::Hidden);
	Text8->SetVisibility(ESlateVisibility::Hidden);

	Button_MainMenu = Cast<UButton>(GetWidgetFromName(TEXT("Button_dead")));

	BindButtonClickEvents();
}

void UNDieWidget::SetDieText(int32 emotion)
{
	switch (emotion)
	{
	case 0:	// 0번 감정 0
		Text1->SetVisibility(ESlateVisibility::Visible);
		break;
	case 1:	// 1번 감정 0
		Text2->SetVisibility(ESlateVisibility::Visible);
		break;
	case 2:	// 2번 감정 0
		Text3->SetVisibility(ESlateVisibility::Visible);
		break;
	case 3:	// 3번 감정 0
		Text4->SetVisibility(ESlateVisibility::Visible);
		break;
	case 4:	// 0번 감정 100
		Text5->SetVisibility(ESlateVisibility::Visible);
		break;
	case 5:	// 1번 감정 100
		Text6->SetVisibility(ESlateVisibility::Visible);
		break;
	case 6:	// 2번 감정 100
		Text7->SetVisibility(ESlateVisibility::Visible);
		break;
	case 7:	// 3번 감정 100
		Text8->SetVisibility(ESlateVisibility::Visible);
		break;
	}
}


void UNDieWidget::BindButtonClickEvents()
{
	Button_MainMenu->OnClicked.Clear();
	Button_MainMenu->OnClicked.AddDynamic(this, &UNDieWidget::ButtonClicked_MainMenu);
}

void UNDieWidget::ButtonClicked_MainMenu()
{
	UGameplayStatics::OpenLevel(GetWorld(), TEXT("StartMap"));
}