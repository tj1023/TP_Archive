// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "ProjectN.h"
#include "Components/ActorComponent.h"
#include "NCharacterStatComponent.generated.h"

#define A_VALUE 2

DECLARE_MULTICAST_DELEGATE(FOnEmotionZeroDelegate);
DECLARE_MULTICAST_DELEGATE(FOnEmotionChangedDelegate);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class PROJECTN_API UNCharacterStatComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UNCharacterStatComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	virtual void InitializeComponent() override;
	
public:
	void SetFirstStart();
	float GetHPRatio(int32);

	// �������
	void SetProgress(int32 NewProgress, int32 Progress);
	int32 GetProgress(int32 Progress);

	// ���� ��ȭ
	void ChangeEmotion(int32 NewDamage, int32 Emotion);
	void SetEmotion(int32 NewEmotion, int32 Emotion);
	int32 GetEmotion(int32 Emotion);

	// �����̻�
	bool GetStatusEffect(int32 StatusEffectNum);
	void SetStatusEffect(bool value, int32 StatusEffectNum);
	void AffectStatusEffect();
	bool GetStatusDeffect(int32 StatusEffectNum);
	void SetStatusDeffect(bool value, int32 StatusEffectNum);

	// �����ϼ�
	int32 GetSurvivalDays();
	void SetSurvivalDays(int32 days);

	// �� ������
	int32 GetAquaphobia();
	void SetAquaphobia(int32 AquaphobiaValue);

	FOnEmotionZeroDelegate EmotionZero;
	FOnEmotionChangedDelegate OnEmotionChanged;

private:
	UPROPERTY(Transient, VisibleInstanceOnly, Category = Stat, Meta = (AllowPrivateAccess = true))
		TArray<int32> ProgressStatus;

	UPROPERTY(Transient, VisibleInstanceOnly, Category = Stat, Meta = (AllowPrivateAccess = true))
		TArray<int32> EmotionStatus;

	UPROPERTY(Transient, VisibleInstanceOnly, Category = Stat, Meta = (AllowPrivateAccess = true))
		TArray<bool> StatusEffect;

	UPROPERTY(Transient, VisibleInstanceOnly, Category = Stat, Meta = (AllowPrivateAccess = true))
		TArray<bool> StatusDeffect;

	UPROPERTY(Transient, VisibleInstanceOnly, Category = Stat, Meta = (AllowPrivateAccess = true))
		int32 Survival_time;

	UPROPERTY(Transient, VisibleInstanceOnly, Category = Stat, Meta = (AllowPrivateAccess = true))
		int32 Aquaphobia;
	
	// ���� ���� - �Ⱦ�
	struct FNCharacterData* CurrentStatData = nullptr;
};
