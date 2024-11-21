// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Tellours.h"
#include "Blueprint/UserWidget.h"
#include "TOCharacterStatComponent.h"
#include "TOSkillWidget.generated.h"

/**
 * 
 */
UCLASS()
class TELLOURS_API UTOSkillWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	virtual void NativeConstruct() override;
	

/*
* ��ų â On�� ��, ���콺 ������ Ȯ�� �� ��ų�� ����.
*/
public:
	// ��������Ʈ ���ε� �ʱ�ȭ �Լ�.
	void BindButtonClickEvents();

private:
	bool bIsButtonCallbackEnabled;

	FTimerHandle TimerHandle_Shield;
	FTimerHandle TimerHandle_SKill_1;
	FTimerHandle TimerHandle_SKill_2;
	FTimerHandle TimerHandle_SKill_3;
	FTimerHandle TimerHandle_SKill_4;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
		class UButton* Button_Background;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
		class UButton* Button_Shield;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
		class UButton* Button_Skill_1;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
		class UButton* Button_Skill_2;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
		class UButton* Button_Skill_3;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
		class UButton* Button_Skill_4;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
		class ATOPlayerController* TOPlayerController;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
		class ATOCharacter* TOCharacter;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
		bool IsShield_CoolDown;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
		bool IsSkill_1_CoolDown;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
		bool IsSkill_2_CoolDown;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
		bool IsSkill_3_CoolDown;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
		bool IsSkill_4_CoolDown;

	UFUNCTION(BlueprintCallable)
		void ButtonClicked_Background();

	UFUNCTION(BlueprintCallable)
		void ButtonClicked_Shield();

	UFUNCTION(BlueprintCallable)
		void ButtonClicked_Skill_1();

	UFUNCTION(BlueprintCallable)
		void ButtonClicked_Skill_2();

	UFUNCTION(BlueprintCallable)
		void ButtonClicked_Skill_3();

	UFUNCTION(BlueprintCallable)
		void ButtonClicked_Skill_4();

// �ִϸ��̼�
public:
	UPROPERTY()
		class UTOAnimInstance* TOAnim;

	UPROPERTY(EditDefaultsOnly, Category = Projectile)
		TSubclassOf<class ATOFireball> FireballClass;

private:
	UTOCharacterStatComponent* CharacterStat;
};
