// Fill out your copyright notice in the Description page of Project Settings.


#include "CapstoneHUDWidget.h"
#include "Kismet/GameplayStatics.h"
#include "Components/Image.h"
#include "Components/ProgressBar.h"
#include "Components/ListView.h"
#include "CapstoneSubObject.h"
#include "EngineUtils.h"
#include "GameFramework/Actor.h"
#include "Components/TextBlock.h"

UCapstoneHUDWidget::UCapstoneHUDWidget(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	static ConstructorHelpers::FClassFinder<UCapstoneDialog> DialogWidgetClass(TEXT("WidgetBlueprint'/Game/UI/UI_Dialog.UI_Dialog_C'"));
	if (DialogWidgetClass.Succeeded())
	{
		DialogClass = DialogWidgetClass.Class;
	}
}

void UCapstoneHUDWidget::NativeConstruct()
{
	Super::NativeConstruct();

	SPBar = Cast<UProgressBar>(GetWidgetFromName(TEXT("pbSP")));
	ImageInteraction = Cast<UImage>(GetWidgetFromName(TEXT("Image_Interaction")));
	ImageApparition = Cast<UImage>(GetWidgetFromName(TEXT("Image_Apparition")));
	DialogList = Cast<UListView>(GetWidgetFromName(TEXT("Dialog")));

	WhiteImage = Cast<UImage>(GetWidgetFromName(TEXT("Image_white")));
	ImageInteraction->SetVisibility(ESlateVisibility::Collapsed);
	WhiteImage->SetVisibility(ESlateVisibility::Visible);
	WhiteImage->SetColorAndOpacity(FLinearColor(1.0f, 1.0f, 1.0f, 0.0f));

	ImageInteraction->SetVisibility(ESlateVisibility::Collapsed);

	RamainItem = Cast<UTextBlock>(GetWidgetFromName(TEXT("T_Remain")));

	SPPercent = 100.0f;

	int32 Count = 0;
	for (TActorIterator<ACapstoneSubObject> It(GetWorld()); It; ++It)
	{
		ACapstoneSubObject* SubObject = *It;
		if (SubObject)
		{
			Count++;
		}
	}

	FString strText;
	strText = FString::Printf(TEXT("Total Item : %d"), Count);
	RamainItem->SetText(FText::FromString(strText));
}

void UCapstoneHUDWidget::SetSPBarPercent(float n)
{
	SPPercent = n / 100;
	SPBar->SetPercent(SPPercent);
}

float UCapstoneHUDWidget::GetSPBarPercent(void)
{
	return SPPercent;
}

void UCapstoneHUDWidget::SetInteractionUI(bool tf)
{
	if (tf) {
		ImageInteraction->SetVisibility(ESlateVisibility::Visible);
	}
	else {
		ImageInteraction->SetVisibility(ESlateVisibility::Collapsed);
	}
}

void UCapstoneHUDWidget::SetApparitionUI(bool tf)
{
	if (tf) {
		ImageApparition->SetVisibility(ESlateVisibility::Visible);
	}
	else {
		ImageApparition->SetVisibility(ESlateVisibility::Collapsed);
	}
}

void UCapstoneHUDWidget::ShowDialog(FString contentText)
{
	if (DialogList->GetNumItems() >= 3)
	{
		DialogList->RemoveItem(DialogList->GetItemAt(0));
	}

	UCapstoneDialog* NewDialog = CreateWidget<UCapstoneDialog>(this, DialogClass);
	DialogText = contentText;

	if (NewDialog)
	{
		DialogList->AddItem(NewDialog);

		FTimerHandle myTimerHandle;
		GetWorld()->GetTimerManager().SetTimer(myTimerHandle, FTimerDelegate::CreateLambda([&]()
			{
				DialogList->RemoveItem(DialogList->GetItemAt(0));

				GetWorld()->GetTimerManager().ClearTimer(myTimerHandle);
			}), 3.0f, false);
	}
}

FString UCapstoneHUDWidget::GetDialogText()
{
	return DialogText;
}


void UCapstoneHUDWidget::Clear()
{
	static float alpha = 0.0f;

	GetWorld()->GetTimerManager().SetTimer(AlphaTimerHandle, FTimerDelegate::CreateLambda([&]()
		{
			alpha += 0.03;
			WhiteImage->SetColorAndOpacity(FLinearColor(1.0f, 1.0f, 1.0f, alpha));

			if (alpha >= 1.0f)
			{
				GetWorld()->GetTimerManager().ClearTimer(AlphaTimerHandle);
				UGameplayStatics::OpenLevel(GetWorld(), TEXT("HappyEnding"));
			}

		}), 0.05f, true);
}
