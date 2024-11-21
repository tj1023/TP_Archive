// Fill out your copyright notice in the Description page of Project Settings.


#include "TOEnemyStatComponent.h"
#include "TOGameInstance.h"


// Sets default values for this component's properties
UTOEnemyStatComponent::UTOEnemyStatComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;
	bWantsInitializeComponent = true;

	Level = 1;
}


// Called when the game starts
void UTOEnemyStatComponent::BeginPlay()
{
	Super::BeginPlay();

}



/*
* ���� �ʱ�ȭ
*/
void UTOEnemyStatComponent::InitializeComponent()
{
	Super::InitializeComponent();

	SetNewLevel(Level);
}



/*
* ����, ����ü�� ����
*/
void UTOEnemyStatComponent::SetNewLevel(int32 NewLevel)
{
	auto TOGameInstance = Cast<UTOGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));

	ABCHECK(nullptr != TOGameInstance);

	// csv���� ������ �´� ������ �����´�
	CurrentStatData = TOGameInstance->GetTOEnemyData(NewLevel);
	if (nullptr != CurrentStatData)
	{
		Level = NewLevel;
		SetHP(CurrentStatData->MaxHP);
		SetAttack(CurrentStatData->Attack);
	}
	else
	{
		ABLOG(Error, TEXT("Level (%d) data doesn't exist"), NewLevel);
	}
}



/*
* HP����
*/
void UTOEnemyStatComponent::SetHP(float NewHP)
{
	CurrentHP = NewHP;
	OnHPChanged.Broadcast();
	if (CurrentHP < KINDA_SMALL_NUMBER)
	{
		CurrentHP = 0;
		OnHPIsZero.Broadcast();
	}
}

float UTOEnemyStatComponent::GetHPRatio()
{
	ABCHECK(nullptr != CurrentStatData, 0);

	// HP ���� ��ȯ
	return (CurrentStatData->MaxHP < KINDA_SMALL_NUMBER) ? 0 : (CurrentHP / CurrentStatData->MaxHP);
}



/*
* ���� ������ ����
*/
void UTOEnemyStatComponent::SetDamage(float NewDamage)
{
	ABCHECK(nullptr != CurrentStatData);
	SetHP(FMath::Clamp<float>(CurrentHP - NewDamage, 0, CurrentStatData->MaxHP));
}

float UTOEnemyStatComponent::GetAttack()
{
	return CurrentAttack;
}

void UTOEnemyStatComponent::SetAttack(float NewAttack)
{
	CurrentAttack = NewAttack;
}
