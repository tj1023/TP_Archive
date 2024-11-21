// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "CapstoneSettingUI.generated.h"

/**
 * 
 */
UCLASS()
class CAPSTONE_API UCapstoneSettingUI : public UUserWidget
{
	GENERATED_BODY()

	
public:
	virtual void NativeConstruct() override;

	UPROPERTY()
	class UTextBlock* SoundVolume1;
private:
	// Graphical Quality
	UPROPERTY()
	class UButton* GQ_L;

	UPROPERTY()
	class UButton* GQ_M;

	UPROPERTY()
	class UButton* GQ_H;

	// Post Processing
	UPROPERTY()
	class UButton* PP_L;

	UPROPERTY()
	class UButton* PP_M;

	UPROPERTY()
	class UButton* PP_H;

	// Anti-Aliasing
	UPROPERTY()
	class UButton* AA_L;

	UPROPERTY()
	class UButton* AA_M;

	UPROPERTY()
	class UButton* AA_H;

	//  Shadow Quality
	UPROPERTY()
	class UButton* SQ_L;

	UPROPERTY()
	class UButton* SQ_M;

	UPROPERTY()
	class UButton* SQ_H;

	// Frame Rate
	UPROPERTY()
	class UButton* FR_L;

	UPROPERTY()
	class UButton* FR_M;

	UPROPERTY()
	class UButton* FR_H;

	// Sound Volume
	UPROPERTY()
	class UButton* SV_q;

	UPROPERTY()
	class UButton* SV_d;

	UPROPERTY()
	class UButton* SV_p;

	UPROPERTY()
	class UTextBlock* SoundVolume;

	UPROPERTY()
	class UButton* SV1_q;

	UPROPERTY()
	class UButton* SV1_d;

	UPROPERTY()
	class UButton* SV1_p;


	// Close
	UPROPERTY()
	class UButton* BClose;

	// Game Mode
	UPROPERTY()
	class UButton* size0;

	UPROPERTY()
	class UButton* size1;

	// onclick function
	UFUNCTION()
	void FGQ_L();

	UFUNCTION()
	void FGQ_M();

	UFUNCTION()
	void FGQ_H();

	// 
	UFUNCTION()
	void FPP_L();

	UFUNCTION()
	void FPP_M();

	UFUNCTION()
	void FPP_H();

	// AA_L
	UFUNCTION()
	void FAA_L();

	UFUNCTION()
	void FAA_M();

	UFUNCTION()
	void FAA_H();
	// SQ_L
	UFUNCTION()
	void FSQ_L();

	UFUNCTION()
	void FSQ_M();

	UFUNCTION()
	void FSQ_H();
	// FR_L
	UFUNCTION()
	void FFR_L();

	UFUNCTION()
	void FFR_M();

	UFUNCTION()
	void FFR_H();

	// SV_q
	UFUNCTION()
	void FSV_q();

	UFUNCTION()
	void FSV_d();

	UFUNCTION()
	void FSV_p();
	
	UFUNCTION()
	void FSV1_q();

	UFUNCTION()
	void FSV1_d();

	UFUNCTION()
	void FSV1_p();

	// close
	UFUNCTION()
	void FClose();

	// Screen Size
	UFUNCTION()
	void FSC_F();

	UFUNCTION()
	void FSC_W();

	UPROPERTY()
	USoundClass* CapstoneSoundClass;

	UPROPERTY()
	USoundClass* BackGroundSoundClass;

	UPROPERTY()
	USoundClass* FootStepSoundClass;

	UPROPERTY()
	USoundMix* SoundMix;
	
	UPROPERTY()
	USoundMix* SoundMix1;
};
