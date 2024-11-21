// Fill out your copyright notice in the Description page of Project Settings.


#include "NScript.h"
#include "UMG.h"
#include "NGameInstance.h"

void UNScript::NativeConstruct()
{
	Super::NativeConstruct();

	LetterTB = Cast<UTextBlock>(GetWidgetFromName(TEXT("Letter")));
	Answer1TB = Cast<UTextBlock>(GetWidgetFromName(TEXT("Answer1")));
	Answer2TB = Cast<UTextBlock>(GetWidgetFromName(TEXT("Answer2")));
	HappyValue_1 = Cast<UImage>(GetWidgetFromName(TEXT("Happy_1")));
	SadValue_1 = Cast<UImage>(GetWidgetFromName(TEXT("Sad_1")));
	AngerValue_1 = Cast<UImage>(GetWidgetFromName(TEXT("Anger_1")));
	FearValue_1 = Cast<UImage>(GetWidgetFromName(TEXT("Fear_1")));
	HappyValue_2 = Cast<UImage>(GetWidgetFromName(TEXT("Happy_2")));
	SadValue_2 = Cast<UImage>(GetWidgetFromName(TEXT("Sad_2")));
	AngerValue_2 = Cast<UImage>(GetWidgetFromName(TEXT("Anger_2")));
	FearValue_2 = Cast<UImage>(GetWidgetFromName(TEXT("Fear_2")));

	HappyFull = FString("/Game/UI/Happy_full.Happy_full");
	HappyHalf = FString("/Game/UI/Happy_half.Happy_half");
	SadFull = FString("/Game/UI/Sad_full.Sad_full");
	SadHalf = FString("/Game/UI/Sad_half.Sad_half");
	AngerFull = FString("/Game/UI/Anger_full.Anger_full");
	AngerHalf = FString("/Game/UI/Anger_half.Anger_half");
	FearFull = FString("/Game/UI/Fear_full.Fear_full");
	FearHalf = FString("/Game/UI/Fear_half.Fear_half");
	NoChange = FString("/Game/UI/NoChange_img.NoChange_img");
}

void UNScript::SetScript(FString ScriptNum)
{
	auto NGameInstance = Cast<UNGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));
	NCHECK(nullptr != NGameInstance);
	CurrentScript = NGameInstance->GetScriptData(ScriptNum);

	LetterTB->SetText(FText::FromString(CurrentScript->Text));
	Answer1TB->SetText(FText::FromString(CurrentScript->A1));
	Answer2TB->SetText(FText::FromString(CurrentScript->A2));

	SetEmotionValue(1);
	SetEmotionValue(2);
}

void UNScript::SetEmotionValue(int32 ScriptNum)
{
	if (ScriptNum == 1)
	{
		//JOY
		if (CurrentScript->Joy1 > 0)
		{
			HappyValue_1->SetBrushFromTexture((CurrentScript->Joy1 == 25.0) ? Cast<UTexture2D>(StaticLoadObject(UTexture2D::StaticClass(), NULL, *HappyFull)) : Cast<UTexture2D>(StaticLoadObject(UTexture2D::StaticClass(), NULL, *HappyHalf)));
		}
		else if (CurrentScript->Joy1 < 0)
		{
			HappyValue_1->SetBrushFromTexture((CurrentScript->Joy1 == -25.0) ? Cast<UTexture2D>(StaticLoadObject(UTexture2D::StaticClass(), NULL, *HappyFull)) : Cast<UTexture2D>(StaticLoadObject(UTexture2D::StaticClass(), NULL, *HappyHalf)));
		}
		else
		{
			HappyValue_1->SetBrushFromTexture(Cast<UTexture2D>(StaticLoadObject(UTexture2D::StaticClass(), NULL, *NoChange)));
		}

		//SAD
		if (CurrentScript->Sad1 > 0)
		{
			SadValue_1->SetBrushFromTexture((CurrentScript->Sad1 == 25.0) ? Cast<UTexture2D>(StaticLoadObject(UTexture2D::StaticClass(), NULL, *SadFull)) : Cast<UTexture2D>(StaticLoadObject(UTexture2D::StaticClass(), NULL, *SadHalf)));
		}
		else if (CurrentScript->Sad1 < 0)
		{
			SadValue_1->SetBrushFromTexture((CurrentScript->Sad1 == -25.0) ? Cast<UTexture2D>(StaticLoadObject(UTexture2D::StaticClass(), NULL, *SadFull)) : Cast<UTexture2D>(StaticLoadObject(UTexture2D::StaticClass(), NULL, *SadHalf)));
		}
		else
		{
			SadValue_1->SetBrushFromTexture(Cast<UTexture2D>(StaticLoadObject(UTexture2D::StaticClass(), NULL, *NoChange)));
		}

		//ANGER
		if (CurrentScript->Anger1 > 0)
		{
			AngerValue_1->SetBrushFromTexture((CurrentScript->Anger1 == 25.0) ? Cast<UTexture2D>(StaticLoadObject(UTexture2D::StaticClass(), NULL, *AngerFull)) : Cast<UTexture2D>(StaticLoadObject(UTexture2D::StaticClass(), NULL, *AngerHalf)));
		}
		else if (CurrentScript->Anger1 < 0)
		{
			AngerValue_1->SetBrushFromTexture((CurrentScript->Anger1 == -25.0) ? Cast<UTexture2D>(StaticLoadObject(UTexture2D::StaticClass(), NULL, *AngerFull)) : Cast<UTexture2D>(StaticLoadObject(UTexture2D::StaticClass(), NULL, *AngerHalf)));
		}
		else
		{
			AngerValue_1->SetBrushFromTexture(Cast<UTexture2D>(StaticLoadObject(UTexture2D::StaticClass(), NULL, *NoChange)));
		}

		//FEAR
		if (CurrentScript->Fear1 > 0)
		{
			FearValue_1->SetBrushFromTexture((CurrentScript->Fear1 == 25.0) ? Cast<UTexture2D>(StaticLoadObject(UTexture2D::StaticClass(), NULL, *FearFull)) : Cast<UTexture2D>(StaticLoadObject(UTexture2D::StaticClass(), NULL, *FearHalf)));
		}
		else if (CurrentScript->Fear1 < 0)
		{
			FearValue_1->SetBrushFromTexture((CurrentScript->Fear1 == -25.0) ? Cast<UTexture2D>(StaticLoadObject(UTexture2D::StaticClass(), NULL, *FearFull)) : Cast<UTexture2D>(StaticLoadObject(UTexture2D::StaticClass(), NULL, *FearHalf)));
		}
		else
		{
			FearValue_1->SetBrushFromTexture(Cast<UTexture2D>(StaticLoadObject(UTexture2D::StaticClass(), NULL, *NoChange)));
		}
	}
	else if (ScriptNum == 2)
	{
		//JOY
		if (CurrentScript->Joy2 > 0)
		{
			HappyValue_2->SetBrushFromTexture((CurrentScript->Joy2 == 25.0) ? Cast<UTexture2D>(StaticLoadObject(UTexture2D::StaticClass(), NULL, *HappyFull)) : Cast<UTexture2D>(StaticLoadObject(UTexture2D::StaticClass(), NULL, *HappyHalf)));
		}
		else if (CurrentScript->Joy2 < 0)
		{
			HappyValue_2->SetBrushFromTexture((CurrentScript->Joy2 == -25.0) ? Cast<UTexture2D>(StaticLoadObject(UTexture2D::StaticClass(), NULL, *HappyFull)) : Cast<UTexture2D>(StaticLoadObject(UTexture2D::StaticClass(), NULL, *HappyHalf)));
		}
		else
		{
			HappyValue_2->SetBrushFromTexture(Cast<UTexture2D>(StaticLoadObject(UTexture2D::StaticClass(), NULL, *NoChange)));
		}

		//SAD
		if (CurrentScript->Sad2 > 0)
		{
			SadValue_2->SetBrushFromTexture((CurrentScript->Sad2 == 25.0) ? Cast<UTexture2D>(StaticLoadObject(UTexture2D::StaticClass(), NULL, *SadFull)) : Cast<UTexture2D>(StaticLoadObject(UTexture2D::StaticClass(), NULL, *SadHalf)));
		}
		else if (CurrentScript->Sad2 < 0)
		{
			SadValue_2->SetBrushFromTexture((CurrentScript->Sad2 == -25.0) ? Cast<UTexture2D>(StaticLoadObject(UTexture2D::StaticClass(), NULL, *SadFull)) : Cast<UTexture2D>(StaticLoadObject(UTexture2D::StaticClass(), NULL, *SadHalf)));
		}
		else
		{
			SadValue_2->SetBrushFromTexture(Cast<UTexture2D>(StaticLoadObject(UTexture2D::StaticClass(), NULL, *NoChange)));
		}

		//ANGER
		if (CurrentScript->Anger2 > 0)
		{
			AngerValue_2->SetBrushFromTexture((CurrentScript->Anger2 == 25.0) ? Cast<UTexture2D>(StaticLoadObject(UTexture2D::StaticClass(), NULL, *AngerFull)) : Cast<UTexture2D>(StaticLoadObject(UTexture2D::StaticClass(), NULL, *AngerHalf)));
		}
		else if (CurrentScript->Anger2 < 0)
		{
			AngerValue_2->SetBrushFromTexture((CurrentScript->Anger2 == -25.0) ? Cast<UTexture2D>(StaticLoadObject(UTexture2D::StaticClass(), NULL, *AngerFull)) : Cast<UTexture2D>(StaticLoadObject(UTexture2D::StaticClass(), NULL, *AngerHalf)));
		}
		else
		{
			AngerValue_2->SetBrushFromTexture(Cast<UTexture2D>(StaticLoadObject(UTexture2D::StaticClass(), NULL, *NoChange)));
		}

		//FEAR
		if (CurrentScript->Fear2 > 0)
		{
			FearValue_2->SetBrushFromTexture((CurrentScript->Fear2 == 25.0) ? Cast<UTexture2D>(StaticLoadObject(UTexture2D::StaticClass(), NULL, *FearFull)) : Cast<UTexture2D>(StaticLoadObject(UTexture2D::StaticClass(), NULL, *FearHalf)));
		}
		else if (CurrentScript->Fear2 < 0)
		{
			FearValue_2->SetBrushFromTexture((CurrentScript->Fear2 == -25.0) ? Cast<UTexture2D>(StaticLoadObject(UTexture2D::StaticClass(), NULL, *FearFull)) : Cast<UTexture2D>(StaticLoadObject(UTexture2D::StaticClass(), NULL, *FearHalf)));
		}
		else
		{
			FearValue_2->SetBrushFromTexture(Cast<UTexture2D>(StaticLoadObject(UTexture2D::StaticClass(), NULL, *NoChange)));
		}
	}
}

FScript* UNScript::GetCurrentScript()
{
	return CurrentScript;
}

void UNScript::StartVisibleAnimation()
{
	PlayAnimation(FadeIn);
}