// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Tellours.h"
#include "Animation/AnimInstance.h"
#include "TOEnemy.h"
#include "TOEnemyAnimInstance.generated.h"


DECLARE_MULTICAST_DELEGATE(FOnAttackHitCheckDeolegate);


/**
 * 
 */
UCLASS()
class TELLOURS_API UTOEnemyAnimInstance : public UAnimInstance
{
	GENERATED_BODY()
	

public:
	UTOEnemyAnimInstance();
	virtual void NativeUpdateAnimation(float DeltaSeconds) override;

private:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Pawn, Meta = (AllowPrivateAccess = true))
		float CurrentPawnSpeed;

// 분류
public:
	void SetMontageType(int32 EnemyNum);
	void SetPhaseMontage(int32 PhaseNum);

// 공격
public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Pawn, Meta = (AllowPrivateAccess = true))
		bool IsAttacked;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = Attack, Meta = (AllowPrivateAccess = true))
		UAnimMontage* AttackMontage;

	void PlayAttackMontage();

	FOnAttackHitCheckDeolegate OnAttackHitCheck;

private:
	UFUNCTION()
		void AnimNotify_AttackHitCheck();

// Dead
public:
	void SetDeadAnim() { IsDead = true; }

private:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Pawn, Meta = (AllowPrivateAccess = true))
		bool IsDead;
};
