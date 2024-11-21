// Fill out your copyright notice in the Description page of Project Settings.


#include "TOCharacterStatComponent.h"
#include "TOGameInstance.h"


// Sets default values for this component's properties
UTOCharacterStatComponent::UTOCharacterStatComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;
	bWantsInitializeComponent = true;

	Level = 1;
}

// Called when the game starts
void UTOCharacterStatComponent::BeginPlay()
{
	Super::BeginPlay();
}


// 스탯 초기화
void UTOCharacterStatComponent::InitializeComponent()
{
	Super::InitializeComponent();
	SetNewLevel(Level);
	Progress = GetProgress();
}


/*
* 레벨, 현재체력 설정
*/
void UTOCharacterStatComponent::SetNewLevel(int32 NewLevel)
{
	auto TOGameInstance = Cast<UTOGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));

	ABCHECK(nullptr != TOGameInstance);
	CurrentStatData = TOGameInstance->GetTOCharacterData(NewLevel);
	if (nullptr != CurrentStatData)
	{
		Level = NewLevel;
		SetHP(CurrentStatData->MaxHP);
		SetMP(CurrentStatData->MaxMP);
		SetEP(CurrentStatData->MaxEP);
	}
	else
	{
		ABLOG(Error, TEXT("Level (%d) data doesn't exist"), NewLevel);
	}
}

float UTOCharacterStatComponent::GetCurrentLevel()
{
	return Level;
}

void UTOCharacterStatComponent::SetProgress(int32 NewProgress)
{
	Progress = NewProgress;
}

int32 UTOCharacterStatComponent::GetProgress()
{
	return Progress;
}

void UTOCharacterStatComponent::UpgradeAttack(int n)
{
	AttackUpgrade += n;
}

/*
* HP설정
*/
void UTOCharacterStatComponent::SetHP(float NewHP)
{
	CurrentHP = NewHP;
	OnHPChanged.Broadcast();
	if (CurrentHP < KINDA_SMALL_NUMBER)
	{
		CurrentHP = 0;
		OnHPIsZero.Broadcast();
	}
}

float UTOCharacterStatComponent::GetCurrentHP()
{
	ABLOG(Warning, TEXT("%0.2f"), CurrentHP);
	return CurrentHP;
}

float UTOCharacterStatComponent::GetHPRatio()
{
	ABCHECK(nullptr != CurrentStatData, 0);

	// HP 비율 반환
	return (CurrentStatData->MaxHP < KINDA_SMALL_NUMBER) ? 0 : (CurrentHP / CurrentStatData->MaxHP);
}

void UTOCharacterStatComponent::AddHP(float Add_HP)
{
	// HP 회복
	ABLOG(Warning, TEXT("CurrentHP : %f"), CurrentHP);
	CurrentHP += Add_HP;
	if (CurrentHP < KINDA_SMALL_NUMBER)
	{
		CurrentHP = 0.0f;
	}
	if (CurrentHP - 100.0f > KINDA_SMALL_NUMBER) {
		CurrentHP = 100.0f;
	}
	OnHPChanged.Broadcast();
	ABLOG(Warning, TEXT("After CurrentHP : %f"), CurrentHP);
}



/*
* MP, EP 설정
*/  
void UTOCharacterStatComponent::SetMP(float NewMP)
{
	CurrentMP = NewMP;
	OnHPChanged.Broadcast();
}

void UTOCharacterStatComponent::SetEP(float NewEP)
{
	CurrentEP = NewEP;
}

float UTOCharacterStatComponent::GetCurrentMP()
{
	ABLOG(Warning, TEXT("%0.2f"), CurrentMP);
	return CurrentMP;
}

float UTOCharacterStatComponent::GetCurrentEP()
{
	ABLOG(Warning, TEXT("%0.2f"), CurrentEP);
	return CurrentEP;
}

float UTOCharacterStatComponent::GetMPRatio()
{
	ABCHECK(nullptr != CurrentStatData, 0);

	// MP 비율 반환
	return (CurrentStatData->MaxMP < KINDA_SMALL_NUMBER) ? 0 : (CurrentMP / CurrentStatData->MaxMP);
}

float UTOCharacterStatComponent::GetEPRatio()
{
	ABCHECK(nullptr != CurrentStatData, 0);

	// MP 비율 반환
	return (CurrentStatData->MaxEP < KINDA_SMALL_NUMBER) ? 0 : (CurrentEP / CurrentStatData->MaxEP);
}



/*
* 공격 및 데미지 관련
*/
float UTOCharacterStatComponent::GetAttack()
{
	ABCHECK(nullptr != CurrentStatData, 0);

	// 공격력 반환
	return CurrentStatData->Attack + AttackUpgrade * 10;
}

void UTOCharacterStatComponent::SetDamage(float NewDamage)
{
	ABCHECK(nullptr != CurrentStatData);

	// 받은 데미지 적용
	SetHP(FMath::Clamp<float>(CurrentHP - NewDamage, 0, CurrentStatData->MaxHP));
}



/*
* 인벤토리 
*/
void UTOCharacterStatComponent::SetInventoryItemCount(TArray<int32> InventoryItemCount)
{
	CurrentInventoryItemCount = InventoryItemCount;
	ABLOG(Warning, TEXT("%d	/	%d	/	%d	/	%d"), InventoryItemCount[0], InventoryItemCount[1], InventoryItemCount[2], InventoryItemCount[3]);
}

TArray<int32> UTOCharacterStatComponent::GetInventoryItemCount()
{
	ABLOG_S(Warning);
	return CurrentInventoryItemCount;
}

void UTOCharacterStatComponent::AddInventoryItemCount(int32 ItemNum)
{
	switch (ItemNum) 
	{
	case 0:{
		OnItem0AddDelegate.Broadcast();
		break;
	}
	case 1: {
		OnItem1AddDelegate.Broadcast();
		break;
	}
	case 2: {
		OnItem2AddDelegate.Broadcast();
		break;
	}
	case 3: {
		OnItem3AddDelegate.Broadcast();
		break;
	}
	case 4: {
		OnItem4AddDelegate.Broadcast();
		break;
	}
	}
}
