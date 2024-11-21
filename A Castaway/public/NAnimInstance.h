// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "ProjectN.h"
#include "Animation/AnimInstance.h"
#include "NAnimInstance.generated.h"

DECLARE_MULTICAST_DELEGATE(FFootstepDelegate);

/**
 * 
 */
UCLASS()
class PROJECTN_API UNAnimInstance : public UAnimInstance
{
	GENERATED_BODY()

public:
	UNAnimInstance();

	virtual void NativeUpdateAnimation(float DeltaSeconds) override;
	void SetDeadAnim();
	bool GetIsDead();
	void SetOceanAnim();
	void SetLandAnim();
	void SetExercise();
	bool GetExercise();
	void SetWhistle();
	bool GetWhistle();

	FFootstepDelegate Footstep;

private:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Pawn, META = (AllowPrivateAccess = true))
	float CurrentPawnSpeed;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Pawn, META = (AllowPrivateAccess = true))
	bool IsDead;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Pawn, META = (AllowPrivateAccess = true))
	bool IsSwimming;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Pawn, META = (AllowPrivateAccess = true))
	bool IsExercise;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Pawn, META = (AllowPrivateAccess = true))
	bool IsWhistle;

	UFUNCTION()
		void AnimNotify_Footstep();
};
