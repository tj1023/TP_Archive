// Fill out your copyright notice in the Description page of Project Settings.


#include "TOBossStatComponent.h"
#include "TOGameInstance.h"
#include "TOBossController.h"
#include "BehaviorTree/BlackboardComponent.h"

// Sets default values for this component's properties
UTOBossStatComponent::UTOBossStatComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
	bWantsInitializeComponent = true;

	Level = 4;
	Phase.Add(false);
	Phase.Add(false);
	Phase.Add(false);
}

void UTOBossStatComponent::BeginPlay()
{
	Super::BeginPlay();
}

void UTOBossStatComponent::TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	
}


/*
* 스탯 초기화
*/
void UTOBossStatComponent::InitializeComponent()
{
	Super::InitializeComponent();

	SetNewLevel(Level);
}



/*
* 레벨, 현재체력 설정
*/
void UTOBossStatComponent::SetNewLevel(int32 NewLevel)
{
	auto TOGameInstance = Cast<UTOGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));

	ABCHECK(nullptr != TOGameInstance);

	// csv에서 레벨에 맞는 스탯을 가져온다
	CurrentStatData = TOGameInstance->GetTOBossData(NewLevel);
	if (nullptr != CurrentStatData)
	{
		Level = NewLevel;
		SetHP(CurrentStatData->MaxHP);
		ABLOG(Error, TEXT("CurrentHP : %f"), CurrentHP);
	}
	else
	{
		ABLOG(Error, TEXT("Level (%d) data doesn't exist"), NewLevel);
	}
}



/*
* HP설정
*/
void UTOBossStatComponent::SetHP(float NewHP)
{
	CurrentHP = NewHP;
	OnHPChanged.Broadcast();
	ABLOG(Error, TEXT("CurrentHP : %f"), CurrentHP);
	if (CurrentHP < KINDA_SMALL_NUMBER)
	{
		CurrentHP = 0;
		OnHPIsZero.Broadcast();
	}
	SetPhase();
}

void UTOBossStatComponent::SetPhase()
{
	float Ratio = GetHPRatio();
	if (0.9f < Ratio)
	{
		ABLOG(Warning, TEXT("SetPhase0"));
		Phase[0] = true;
		return;
	}
	else if (0.8f < Ratio)
	{
		ABLOG(Warning, TEXT("SetPhase1"));
		Phase[0] = false;
		Phase[1] = true;
		return;
	}
	else if (KINDA_SMALL_NUMBER < Ratio)
	{
		ABLOG(Warning, TEXT("SetPhase2"));
		Phase[1] = false;
		Phase[2] = true;
		return;
	}
	else
	{
		ABLOG(Warning, TEXT("Dead state"));
		Phase[2] = false;
		return;
	}
}


int32 UTOBossStatComponent::GetPhase()
{
	for (int32 index = 2; index >= 0; index--)
	{
		if (Phase[index] == true) 
		{
			ABLOG(Warning, TEXT("GetPhase %d"), index);
			return index;
		}
	}
	ABLOG(Warning, TEXT("GetPhase %d"), 999);
	return 999;
}

float UTOBossStatComponent::GetHPRatio()
{
	ABCHECK(nullptr != CurrentStatData, 0);

	// HP 비율 반환
	return (CurrentStatData->MaxHP < KINDA_SMALL_NUMBER) ? 0 : (CurrentHP / CurrentStatData->MaxHP);
}



/*
* 받은 데미지 적용
*/
void UTOBossStatComponent::SetDamage(float NewDamage)
{
	ABCHECK(nullptr != CurrentStatData);
	SetHP(FMath::Clamp<float>(CurrentHP - NewDamage, 0, CurrentStatData->MaxHP));
	if (CurrentHP <= 0.0f)
	{
		OnHPIsZero.Broadcast();
	}
}

float UTOBossStatComponent::GetAttack()
{
	ABCHECK(nullptr != CurrentStatData, 0);

	// 공격력 반환
	return CurrentStatData->Attack;
}
