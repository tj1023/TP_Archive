// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Tellours.h"
#include "Animation/AnimInstance.h"
#include "TOBossAnimInstance.generated.h"

DECLARE_MULTICAST_DELEGATE(FOnAttackHitCheckDelegate);

/**
 * 
 */
UCLASS()
class TELLOURS_API UTOBossAnimInstance : public UAnimInstance
{
	GENERATED_BODY()
	
public:
	UTOBossAnimInstance();
	virtual void NativeUpdateAnimation(float DeltaSeconds) override;
	void PlayAttackMontage();



public:
	FOnAttackHitCheckDelegate OnAttackHitCheck;
	void SetDeadAnim() { IsDead = true; }
	void SetPhase0() { Phase0 = true; }
	void SetPhase1() { Phase1 = true; Phase0 = false; }
	void SetPhase2() { Phase2 = true; Phase1 = false; }
	void SetPhaseZeroEnd() { PhaseZeroIsEnd = true; }
	void StopMontage();

private:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Boss, Meta = (AllowPrivateAccess = true))
		float CurrentPawnSpeed;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Boss, Meta = (AllowPrivateAccess = true))
		bool IsDead;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Boss, Meta = (AllowPrivateAccess = true))
		bool Phase0;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Boss, Meta = (AllowPrivateAccess = true))
		bool Phase1;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Boss, Meta = (AllowPrivateAccess = true))
		bool Phase2;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Boss, Meta = (AllowPrivateAccess = true))
		bool PhaseZeroIsEnd;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = Attack, Meta = (AllowPrivateAccess = true))
		UAnimMontage* AttackMontage;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = Attack, Meta = (AllowPrivateAccess = true))
		UAnimMontage* AttackMontage1;

	UFUNCTION()
		void AnimNotify_AttackHitCheck();

};
