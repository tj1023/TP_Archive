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

	// 초기값 지정
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
* 진행도
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
* 감정 수치
*/
void UNCharacterStatComponent::ChangeEmotion(int32 NewDamage, int32 Emotion)
{
	// 상태이상에 따른 감정 변화 수치 조정 - 해당 상태이상만 설정할 것.
	// 상태이상 기능 수정(한 번 살아날 수 있도록 하는 기능으로)
	// 따라서 아래 기능은 삭제 예정
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

	// 상태이상 버프로 회복 기능 구현
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
* 상태 이상
*/
bool UNCharacterStatComponent::GetStatusEffect(int32 StatusEffectNum)
{
	return StatusEffect[StatusEffectNum];
}

void UNCharacterStatComponent::SetStatusEffect(bool value, int32 StatusEffectNum)
{
	StatusEffect[StatusEffectNum] = value;
}

// 디버프
void UNCharacterStatComponent::SetStatusDeffect(bool value, int32 StatusEffectNum)
{
	StatusDeffect[StatusEffectNum] = value;
}

bool UNCharacterStatComponent::GetStatusDeffect(int32 StatusEffectNum)
{
	return StatusDeffect[StatusEffectNum];
}

//// 상태이상 시 매 턴 특정 감정 감소
//void UNCharacterStatComponent::AffectStatusEffect()
//{
//	/*
//	* 0번 상태이상은 물 공포증임
//	if (GetStatusEffect(0))
//	*/
//	if (GetStatusEffect(1))
//	{
//		// 효과 없음
//	}
//	if (GetStatusEffect(2))
//	{
//		// 2번 감정을 5만큼 매 턴 증가
//		ChangeEmotion(5, 2);
//	}
//	if (GetStatusEffect(3))
//	{
//		// 3번 감정을 5만큼 매 턴 감소
//		ChangeEmotion(-5, 3);
//	}
//}


/*
* 생존 일수 - 스크립트 개수로 수정
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
* 물 공포증
*/
int32 UNCharacterStatComponent::GetAquaphobia()
{
	return Aquaphobia;
}
void UNCharacterStatComponent::SetAquaphobia(int32 AquaphobiaValue)
{
	Aquaphobia = AquaphobiaValue;
}