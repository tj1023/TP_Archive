// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Tellours.h"
#include "Components/ActorComponent.h"
#include "TOBossStatComponent.generated.h"


DECLARE_MULTICAST_DELEGATE(FOnHPisZeroDelegate);
DECLARE_MULTICAST_DELEGATE(FOnHPChanagedDelegate);


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class TELLOURS_API UTOBossStatComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UTOBossStatComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;
	virtual void InitializeComponent() override;
	virtual void TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;


	/*
	* Ω∫≈» º≥¡§
	*/
public:
	FOnHPisZeroDelegate OnHPIsZero;
	FOnHPChanagedDelegate OnHPChanged;

	void SetNewLevel(int32 NewLevel);
	void SetDamage(float NewDamage);
	void SetHP(float NewHP);
	float GetAttack();
	float GetHPRatio();
	void SetPhase();
	int32 GetPhase();
	TArray<bool> Phase;

private:
	struct FTOBossData* CurrentStatData = nullptr;


	UPROPERTY(EditInstanceOnly, Category = Stat, Meta = (AllowPrivateAccess = true))
		int32 Level;

	UPROPERTY(Transient, VisibleInstanceOnly, Category = Stat, Meta = (AllowPrivateAccess = true))
		float CurrentHP;
};
