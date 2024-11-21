// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Tellours.h"
#include "Components/ActorComponent.h"
#include "TOCharacterStatComponent.generated.h"


DECLARE_MULTICAST_DELEGATE(FOnHPisZeroDelegate);
DECLARE_MULTICAST_DELEGATE(FOnHPChanagedDelegate);
DECLARE_MULTICAST_DELEGATE(FOnMPChanagedDelegate);
DECLARE_MULTICAST_DELEGATE(FOnEPChanagedDelegate);
DECLARE_MULTICAST_DELEGATE(FOnItem0AddDelegate);
DECLARE_MULTICAST_DELEGATE(FOnItem1AddDelegate);
DECLARE_MULTICAST_DELEGATE(FOnItem2AddDelegate);
DECLARE_MULTICAST_DELEGATE(FOnItem3AddDelegate);
DECLARE_MULTICAST_DELEGATE(FOnItem4AddDelegate);


UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class TELLOURS_API UTOCharacterStatComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	UTOCharacterStatComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;
	virtual void InitializeComponent() override;



	//스탯 설정
public:
	FOnHPisZeroDelegate OnHPIsZero;
	FOnHPChanagedDelegate OnHPChanged;
	FOnMPChanagedDelegate OnMPChanged;
	FOnEPChanagedDelegate OnEPChanged;

	void SetNewLevel(int32 NewLevel);
	void SetProgress(int32 NewProgress);
	void SetDamage(float NewDamage);
	void SetHP(float NewHP);
	void SetMP(float NewMP);
	void SetEP(float NewEP);
	void AddHP(float Add_HP);
	float GetAttack();
	float GetHPRatio();
	float GetMPRatio();
	float GetEPRatio();
	float GetCurrentHP();
	float GetCurrentMP();
	float GetCurrentEP();
	float GetCurrentLevel();
	int32 GetProgress();

	void UpgradeAttack(int n);

private:
	struct FTOCharacterData* CurrentStatData = nullptr;

	UPROPERTY(EditInstanceOnly, Category = Stat, Meta = (AllowPrivateAccess = true))
	int32 Level;

	UPROPERTY(Transient, VisibleInstanceOnly, Category = Stat, Meta = (AllowPrivateAccess = true))
	float CurrentHP;

	UPROPERTY(Transient, VisibleInstanceOnly, Category = Stat, Meta = (AllowPrivateAccess = true))
	float CurrentMP;

	UPROPERTY(Transient, VisibleInstanceOnly, Category = Stat, Meta = (AllowPrivateAccess = true))
	float CurrentEP;

	UPROPERTY(Transient, VisibleInstanceOnly, Category = Stat, Meta = (AllowPrivateAccess = true))
	int32 Progress;

	int32 AttackUpgrade = 0;

	// 인벤토리
public:
	void SetInventoryItemCount(TArray<int32> InventoryItemCount);
	void AddInventoryItemCount(int32 ItemNum);
	TArray<int32> GetInventoryItemCount();

	FOnItem0AddDelegate OnItem0AddDelegate;
	FOnItem1AddDelegate OnItem1AddDelegate;
	FOnItem2AddDelegate OnItem2AddDelegate;
	FOnItem3AddDelegate OnItem3AddDelegate;
	FOnItem3AddDelegate OnItem4AddDelegate;
private:
	UPROPERTY()
	TArray<int32> CurrentInventoryItemCount;

};
