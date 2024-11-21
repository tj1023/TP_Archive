// Fill out your copyright notice in the Description page of Project Settings.


#include "TOScript.h"
#include "UMG.h"
#include "TOPlayerController.h"

void UTOScript::NativeConstruct()
{
	Super::NativeConstruct();

	TitleText = Cast<UTextBlock>(GetWidgetFromName(TEXT("T_TitleText")));
	SkipButton = Cast<UButton>(GetWidgetFromName(TEXT("B_NextButton")));

	SkipButton->OnClicked.Clear();
	SkipButton->OnClicked.AddDynamic(this, &UTOScript::SkipButtonCliked);
	TitleText->SetText(FText::FromString(TEXT("First Script Title")));

	TOPlayerController = Cast<ATOPlayerController>(GetWorld()->GetFirstPlayerController());
}




void UTOScript::SkipButtonCliked()
{
	TOPlayerController->CloseScriptUI();
}