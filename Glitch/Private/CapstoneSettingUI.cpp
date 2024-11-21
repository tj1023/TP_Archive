// Fill out your copyright notice in the Description page of Project Settings.


#include "CapstoneSettingUI.h"
#include "CapstoneCharacter.h"
#include "Components/TextBlock.h"
#include "Kismet/GameplayStatics.h"
#include "Components/Button.h"
#include "CapstoneController.h"
#include "Engine/Engine.h"
#include "Sound/SoundClass.h"
#include "Sound/SoundMix.h"
#include "GameFramework/GameUserSettings.h"

void UCapstoneSettingUI::NativeConstruct()
{
	Super::NativeConstruct();

	GQ_L = Cast<UButton>(GetWidgetFromName(TEXT("Button_0_0")));
	GQ_M = Cast<UButton>(GetWidgetFromName(TEXT("Button_0_1")));
	GQ_H = Cast<UButton>(GetWidgetFromName(TEXT("Button_0_2")));
	GQ_L->OnClicked.AddDynamic(this, &UCapstoneSettingUI::FGQ_L);
	GQ_M->OnClicked.AddDynamic(this, &UCapstoneSettingUI::FGQ_M);
	GQ_H->OnClicked.AddDynamic(this, &UCapstoneSettingUI::FGQ_H);

	PP_L = Cast<UButton>(GetWidgetFromName(TEXT("Button_1_0")));
	PP_M = Cast<UButton>(GetWidgetFromName(TEXT("Button_1_1")));
	PP_H = Cast<UButton>(GetWidgetFromName(TEXT("Button_1_2")));
	PP_L->OnClicked.AddDynamic(this, &UCapstoneSettingUI::FPP_L);
	PP_M->OnClicked.AddDynamic(this, &UCapstoneSettingUI::FPP_M);
	PP_H->OnClicked.AddDynamic(this, &UCapstoneSettingUI::FPP_H);

	AA_L = Cast<UButton>(GetWidgetFromName(TEXT("Button_2_0")));
	AA_M = Cast<UButton>(GetWidgetFromName(TEXT("Button_2_1")));
	AA_H = Cast<UButton>(GetWidgetFromName(TEXT("Button_2_2")));
	AA_L->OnClicked.AddDynamic(this, &UCapstoneSettingUI::FAA_L);
	AA_M->OnClicked.AddDynamic(this, &UCapstoneSettingUI::FAA_M);
	AA_H->OnClicked.AddDynamic(this, &UCapstoneSettingUI::FAA_H);

	SQ_L = Cast<UButton>(GetWidgetFromName(TEXT("Button_3_0")));
	SQ_M = Cast<UButton>(GetWidgetFromName(TEXT("Button_3_1")));
	SQ_H = Cast<UButton>(GetWidgetFromName(TEXT("Button_3_2")));
	SQ_L->OnClicked.AddDynamic(this, &UCapstoneSettingUI::FSQ_L);
	SQ_M->OnClicked.AddDynamic(this, &UCapstoneSettingUI::FSQ_M);
	SQ_H->OnClicked.AddDynamic(this, &UCapstoneSettingUI::FSQ_H);

	FR_L = Cast<UButton>(GetWidgetFromName(TEXT("Button_4_0")));
	FR_M = Cast<UButton>(GetWidgetFromName(TEXT("Button_4_1")));
	FR_H = Cast<UButton>(GetWidgetFromName(TEXT("Button_4_2")));
	FR_L->OnClicked.AddDynamic(this, &UCapstoneSettingUI::FFR_L);
	FR_M->OnClicked.AddDynamic(this, &UCapstoneSettingUI::FFR_M);
	FR_H->OnClicked.AddDynamic(this, &UCapstoneSettingUI::FFR_H);

	SV_q = Cast<UButton>(GetWidgetFromName(TEXT("Button_sound_q")));
	SV_d = Cast<UButton>(GetWidgetFromName(TEXT("Button_sound_down")));
	SV_p = Cast<UButton>(GetWidgetFromName(TEXT("Button_sound_plus")));
	SV_q->OnClicked.AddDynamic(this, &UCapstoneSettingUI::FSV_q); 
	SV_d->OnClicked.AddDynamic(this, &UCapstoneSettingUI::FSV_d);
	SV_p->OnClicked.AddDynamic(this, &UCapstoneSettingUI::FSV_p);
	SoundVolume = Cast<UTextBlock>(GetWidgetFromName(TEXT("TextBlock_sound")));

	SV1_q = Cast<UButton>(GetWidgetFromName(TEXT("Button_sound_q_1")));
	SV1_d = Cast<UButton>(GetWidgetFromName(TEXT("Button_sound_down_1")));
	SV1_p = Cast<UButton>(GetWidgetFromName(TEXT("Button_sound_plus_1")));
	SV1_q->OnClicked.AddDynamic(this, &UCapstoneSettingUI::FSV1_q);
	SV1_d->OnClicked.AddDynamic(this, &UCapstoneSettingUI::FSV1_d);
	SV1_p->OnClicked.AddDynamic(this, &UCapstoneSettingUI::FSV1_p);
	SoundVolume1 = Cast<UTextBlock>(GetWidgetFromName(TEXT("TextBlock_sound_1")));


	size0 = Cast<UButton>(GetWidgetFromName(TEXT("Button_size0")));
	size1 = Cast<UButton>(GetWidgetFromName(TEXT("Button_size1")));
	size0->OnClicked.AddDynamic(this, &UCapstoneSettingUI::FSC_F);
	size1->OnClicked.AddDynamic(this, &UCapstoneSettingUI::FSC_W);

	BClose = Cast<UButton>(GetWidgetFromName(TEXT("Button_close")));
	BClose->OnClicked.AddDynamic(this, &UCapstoneSettingUI::FClose);

	FString SoundClassPath = TEXT("SoundClass'/Game/Assets/CapstoneSoundClass.CapstoneSoundClass'");
	CapstoneSoundClass = Cast<USoundClass>(StaticLoadObject(USoundClass::StaticClass(), nullptr, *SoundClassPath));


	FString SoundClassPath1 = TEXT("SoundClass'/Game/HorrorAndTension/Background.Background'");
	BackGroundSoundClass = Cast<USoundClass>(StaticLoadObject(USoundClass::StaticClass(), nullptr, *SoundClassPath1));

	FString SoundClassPath2 = TEXT("SoundClass'/Game/HorrorAndTension/FootStep.FootStep'");
	FootStepSoundClass = Cast<USoundClass>(StaticLoadObject(USoundClass::StaticClass(), nullptr, *SoundClassPath2));
	
}

void UCapstoneSettingUI::FGQ_L()
{
	FString Command = FString::Printf(TEXT("sg.ViewDistanceQuality %d"), 0);
	GEngine->GameViewport->GetWorld()->GetFirstPlayerController()->ConsoleCommand(*Command, true);
}
void UCapstoneSettingUI::FGQ_M()
{
	FString Command = FString::Printf(TEXT("sg.ViewDistanceQuality %d"), 1);
	GEngine->GameViewport->GetWorld()->GetFirstPlayerController()->ConsoleCommand(*Command, true);
}
void UCapstoneSettingUI::FGQ_H()
{
	FString Command = FString::Printf(TEXT("sg.ViewDistanceQuality %d"), 2);
	GEngine->GameViewport->GetWorld()->GetFirstPlayerController()->ConsoleCommand(*Command, true);
}

void UCapstoneSettingUI::FPP_L()
{
	FString Command = FString::Printf(TEXT("sg.PostProcessQuality %d"), 0);
	GEngine->GameViewport->GetWorld()->GetFirstPlayerController()->ConsoleCommand(*Command, true);
}
void UCapstoneSettingUI::FPP_M()
{
	FString Command = FString::Printf(TEXT("sg.PostProcessQuality %d"), 1);
	GEngine->GameViewport->GetWorld()->GetFirstPlayerController()->ConsoleCommand(*Command, true);
}
void UCapstoneSettingUI::FPP_H()
{
	FString Command = FString::Printf(TEXT("sg.PostProcessQuality %d"), 2);
	GEngine->GameViewport->GetWorld()->GetFirstPlayerController()->ConsoleCommand(*Command, true);
}
void UCapstoneSettingUI::FAA_L()
{
	FString Command = FString::Printf(TEXT("sg.AntiAliasingQuality %d"), 0);
	GEngine->GameViewport->GetWorld()->GetFirstPlayerController()->ConsoleCommand(*Command, true);
}
void UCapstoneSettingUI::FAA_M()
{
	FString Command = FString::Printf(TEXT("sg.AntiAliasingQuality %d"), 1);
	GEngine->GameViewport->GetWorld()->GetFirstPlayerController()->ConsoleCommand(*Command, true);
}
void UCapstoneSettingUI::FAA_H()
{
	FString Command = FString::Printf(TEXT("sg.AntiAliasingQuality %d"), 2);
	GEngine->GameViewport->GetWorld()->GetFirstPlayerController()->ConsoleCommand(*Command, true);
}
void UCapstoneSettingUI::FSQ_L()
{
	FString Command = FString::Printf(TEXT("sg.ShadowQuality %d"), 0);
	GEngine->GameViewport->GetWorld()->GetFirstPlayerController()->ConsoleCommand(*Command, true);

}
void UCapstoneSettingUI::FSQ_M()
{
	FString Command = FString::Printf(TEXT("sg.ShadowQuality %d"), 1);
	GEngine->GameViewport->GetWorld()->GetFirstPlayerController()->ConsoleCommand(*Command, true);

}
void UCapstoneSettingUI::FSQ_H()
{
	FString Command = FString::Printf(TEXT("sg.ShadowQuality %d"), 2);
	GEngine->GameViewport->GetWorld()->GetFirstPlayerController()->ConsoleCommand(*Command, true);
}
void UCapstoneSettingUI::FFR_L()
{
	IConsoleVariable* MaxFPSVar = IConsoleManager::Get().FindConsoleVariable(TEXT("t.MaxFPS"));
	MaxFPSVar->Set(30.0f, ECVF_SetByCode);
}
void UCapstoneSettingUI::FFR_M()
{
	IConsoleVariable* MaxFPSVar = IConsoleManager::Get().FindConsoleVariable(TEXT("t.MaxFPS"));
	MaxFPSVar->Set(60.0f, ECVF_SetByCode);
}
void UCapstoneSettingUI::FFR_H()
{
	IConsoleVariable* MaxFPSVar = IConsoleManager::Get().FindConsoleVariable(TEXT("t.MaxFPS"));
	MaxFPSVar->Set(90.0f, ECVF_SetByCode);
}
void UCapstoneSettingUI::FSV_q()
{
	BackGroundSoundClass = Cast<USoundClass>(StaticLoadObject(USoundClass::StaticClass(), nullptr, TEXT("SoundClass'/Game/HorrorAndTension/Background.Background'")));
	SoundMix = Cast<USoundMix>(StaticLoadObject(USoundMix::StaticClass(), nullptr, TEXT("SoundMix'/Game/HorrorAndTension/MBackground.MBackground'")));

	if (!BackGroundSoundClass || !SoundMix)
	{
		return;
	}

	for (FSoundClassAdjuster& Adjuster : SoundMix->SoundClassEffects)
	{
		if (Adjuster.SoundClassObject == BackGroundSoundClass)
		{
			Adjuster.VolumeAdjuster = 0.01f;
			Adjuster.bApplyToChildren = true;
			UGameplayStatics::PopSoundMixModifier(GetWorld(), SoundMix);
			UGameplayStatics::PushSoundMixModifier(GetWorld(), SoundMix);
			break;
		}
	}

	SoundVolume->SetText(FText::FromString("0"));
}
void UCapstoneSettingUI::FSV_d()
{
	BackGroundSoundClass = Cast<USoundClass>(StaticLoadObject(USoundClass::StaticClass(), nullptr, TEXT("SoundClass'/Game/HorrorAndTension/Background.Background'")));
	SoundMix = Cast<USoundMix>(StaticLoadObject(USoundMix::StaticClass(), nullptr, TEXT("SoundMix'/Game/HorrorAndTension/MBackground.MBackground'")));
	
	if (!BackGroundSoundClass || !SoundMix)
		return;
	
	for (FSoundClassAdjuster& Adjuster : SoundMix->SoundClassEffects)
	{
		if (Adjuster.SoundClassObject == BackGroundSoundClass)
		{
			float NewVolume = FMath::Clamp(Adjuster.VolumeAdjuster - 0.1f, 0.0f, 1.0f); 
			NewVolume = NewVolume < 0.1f ? 0.01f : NewVolume;
			Adjuster.VolumeAdjuster = NewVolume;
			Adjuster.bApplyToChildren = true;
			
			if (NewVolume >= 0.1f)
			{
				FString VolumeString = FString::Printf(TEXT("%.1f"), NewVolume * 100.0f);
				SoundVolume->SetText(FText::FromString(VolumeString));
			}
			else
			{
				SoundVolume->SetText(FText::FromString("0"));
			}
			UGameplayStatics::PopSoundMixModifier(GetWorld(), SoundMix);
			UGameplayStatics::PushSoundMixModifier(GetWorld(), SoundMix);
			break;
		}
	}

}
void UCapstoneSettingUI::FSV_p()
{
	BackGroundSoundClass = Cast<USoundClass>(StaticLoadObject(USoundClass::StaticClass(), nullptr, TEXT("SoundClass'/Game/HorrorAndTension/Background.Background'")));
	SoundMix = Cast<USoundMix>(StaticLoadObject(USoundMix::StaticClass(), nullptr, TEXT("SoundMix'/Game/HorrorAndTension/MBackground.MBackground'")));

	if (!BackGroundSoundClass || !SoundMix)
		return;

	for (FSoundClassAdjuster& Adjuster : SoundMix->SoundClassEffects)
	{
		if (Adjuster.SoundClassObject == BackGroundSoundClass)
		{
			if (Adjuster.VolumeAdjuster < 0.1f)
				Adjuster.VolumeAdjuster = 0.0f;
			float NewVolume = FMath::Clamp(Adjuster.VolumeAdjuster + 0.1f, 0.0f, 1.0f);
			Adjuster.VolumeAdjuster = NewVolume;
			Adjuster.bApplyToChildren = true;

			if (NewVolume >= 0.1f)
			{
				FString VolumeString = FString::Printf(TEXT("%.1f"), NewVolume * 100.0f);
				SoundVolume->SetText(FText::FromString(VolumeString));
			}
			else
			{
				SoundVolume->SetText(FText::FromString("0"));
			}
			UGameplayStatics::PopSoundMixModifier(GetWorld(), SoundMix);
			UGameplayStatics::PushSoundMixModifier(GetWorld(), SoundMix);
			break;
		}
	}

}

void UCapstoneSettingUI::FSV1_q()
{
	ACapstoneCharacter* C = Cast<ACapstoneCharacter>(GetWorld()->GetFirstPlayerController()->GetPawn());
	C->FSoundq();
}

void UCapstoneSettingUI::FSV1_d()
{
	ACapstoneCharacter* C = Cast<ACapstoneCharacter>(GetWorld()->GetFirstPlayerController()->GetPawn());
	C->FSoundd();
}

void UCapstoneSettingUI::FSV1_p()
{
	ACapstoneCharacter* C = Cast<ACapstoneCharacter>(GetWorld()->GetFirstPlayerController()->GetPawn());
	C->FSoundp();
}


void UCapstoneSettingUI::FClose()
{
	const auto CapstoneController = Cast<ACapstoneController>(GetWorld()->GetFirstPlayerController());
	CapstoneController->CloseSetting();
}

void UCapstoneSettingUI::FSC_F()
{
	UGameUserSettings* UserSettings = GEngine->GetGameUserSettings();
	if (UserSettings)
	{
		EWindowMode::Type CurrentMode = UserSettings->GetFullscreenMode();

		if (CurrentMode == EWindowMode::Windowed)
		{
			UserSettings->SetFullscreenMode(EWindowMode::Fullscreen);
			UserSettings->ApplySettings(true);
		}
	}
}

void UCapstoneSettingUI::FSC_W()
{
	UGameUserSettings* UserSettings = GEngine->GetGameUserSettings();
	if (UserSettings)
	{
		EWindowMode::Type CurrentMode = UserSettings->GetFullscreenMode();

		if (CurrentMode == EWindowMode::Fullscreen)
		{
			UserSettings->SetFullscreenMode(EWindowMode::Windowed);
			UserSettings->ApplySettings(false);
		}
	}
}