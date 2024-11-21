// Fill out your copyright notice in the Description page of Project Settings.


#include "NCharacterStatComponent.h"
#include "NGameInstance.h"
#include "NPlayerController.h"
#include "NGameSystemComponent.h"

// Sets default values for this component's properties
UNCharacterStatComponent::UNCharacterStatComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;
	bWantsInitializeComponent = true;

	// �ʱⰪ ����
	EmotionStatus.Init(100, 4);
	ProgressStatus.Init(0, SCRIPT_LEN);
	StatusEffect.Init(false, 4);
	StatusDeffect.Init(false, 4);
	Survival_time = 0;
	Aquaphobia = 100;
}


// Called when the game starts
void UNCharacterStatComponent::BeginPlay()
{
	Super::BeginPlay();
}

void UNCharacterStatComponent::InitializeComponent()
{
	Super::InitializeComponent();
}

/*
* ���൵
*/
void UNCharacterStatComponent::SetProgress(int32 NewProgress, int32 Progress)
{
	ProgressStatus[Progress] = NewProgress;
}

int32 UNCharacterStatComponent::GetProgress(int32 Progress)
{
	return ProgressStatus[Progress];
}



/*
* ���� ��ġ
*/
void UNCharacterStatComponent::ChangeEmotion(int32 NewDamage, int32 Emotion)
{
	// �����̻� ���� ���� ��ȭ ��ġ ���� - �ش� �����̻� ������ ��.
	// �����̻� ��� ����(�� �� ��Ƴ� �� �ֵ��� �ϴ� �������)
	// ���� �Ʒ� ����� ���� ����
	if(StatusDeffect[Emotion] && Emotion == 1)
		SetEmotion(FMath::Clamp<int32>(EmotionStatus[Emotion] + NewDamage * A_VALUE, 0, 100), Emotion);	
	else if (StatusDeffect[Emotion] && Emotion == 2)
		 SetEmotion(FMath::Clamp<int32>(EmotionStatus[Emotion] + NewDamage * A_VALUE, 0, 100), Emotion);
	else if (StatusDeffect[Emotion] && Emotion == 3)
		SetEmotion(FMath::Clamp<int32>(EmotionStatus[Emotion] + NewDamage * A_VALUE, 0, 100), Emotion);
	else if (StatusDeffect[Emotion] && Emotion == 4)
		SetEmotion(FMath::Clamp<int32>(EmotionStatus[Emotion] + NewDamage * A_VALUE, 0, 100), Emotion);
	else 
		SetEmotion(FMath::Clamp<int32>(EmotionStatus[Emotion] + NewDamage, 0, 100), Emotion);
}

void UNCharacterStatComponent::SetEmotion(int32 NewEmotion, int32 Emotion)
{
	EmotionStatus[Emotion] = NewEmotion;
	OnEmotionChanged.Broadcast();

	// �����̻� ������ ȸ�� ��� ����
	if ((EmotionStatus[Emotion] <= 0 || EmotionStatus[Emotion] >= 100)&& GetStatusEffect(Emotion))
	{
		SetEmotion(50, Emotion);
		SetStatusEffect(false, Emotion);
		ANPlayerController* Controller = Cast<ANPlayerController>(GetWorld()->GetFirstPlayerController());
		Controller->UpdateUI();
	}
		

	if (EmotionStatus[Emotion] <= 0 || EmotionStatus[Emotion] >= 100)
		EmotionZero.Broadcast();
}

int32 UNCharacterStatComponent::GetEmotion(int32 Emotion)
{
	return EmotionStatus[Emotion];
}

float UNCharacterStatComponent::GetHPRatio(int32 EmotionNum)
{
	return (100.0f < KINDA_SMALL_NUMBER) ? 0.0f : (EmotionStatus[EmotionNum] / 100.0f);
}



/*
* ���� �̻�
*/
bool UNCharacterStatComponent::GetStatusEffect(int32 StatusEffectNum)
{
	return StatusEffect[StatusEffectNum];
}

void UNCharacterStatComponent::SetStatusEffect(bool value, int32 StatusEffectNum)
{
	StatusEffect[StatusEffectNum] = value;
}

// �����
void UNCharacterStatComponent::SetStatusDeffect(bool value, int32 StatusEffectNum)
{
	StatusDeffect[StatusEffectNum] = value;
}

bool UNCharacterStatComponent::GetStatusDeffect(int32 StatusEffectNum)
{
	return StatusDeffect[StatusEffectNum];
}

//// �����̻� �� �� �� Ư�� ���� ����
//void UNCharacterStatComponent::AffectStatusEffect()
//{
//	/*
//	* 0�� �����̻��� �� ��������
//	if (GetStatusEffect(0))
//	*/
//	if (GetStatusEffect(1))
//	{
//		// ȿ�� ����
//	}
//	if (GetStatusEffect(2))
//	{
//		// 2�� ������ 5��ŭ �� �� ����
//		ChangeEmotion(5, 2);
//	}
//	if (GetStatusEffect(3))
//	{
//		// 3�� ������ 5��ŭ �� �� ����
//		ChangeEmotion(-5, 3);
//	}
//}


/*
* ���� �ϼ� - ��ũ��Ʈ ������ ����
*/
int32 UNCharacterStatComponent::GetSurvivalDays()
{
	return Survival_time;
}
void UNCharacterStatComponent::SetSurvivalDays(int32 days)
{
	NLOG(Warning, TEXT("Update Survival day : %d"), days);
	Survival_time = days;
}


/*
* �� ������
*/
int32 UNCharacterStatComponent::GetAquaphobia()
{
	return Aquaphobia;
}
void UNCharacterStatComponent::SetAquaphobia(int32 AquaphobiaValue)
{
	Aquaphobia = AquaphobiaValue;
}