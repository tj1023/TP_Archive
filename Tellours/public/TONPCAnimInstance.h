// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Tellours.h"
#include "Animation/AnimInstance.h"
#include "TONPCAnimInstance.generated.h"

/**
 * 
 */
UCLASS()
class TELLOURS_API UTONPCAnimInstance : public UAnimInstance
{
	GENERATED_BODY()


public:
	UTONPCAnimInstance();
	virtual void NativeUpdateAnimation(float DeltaSeconds) override;

private:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Pawn, Meta = (AllowPrivateAccess = true))
		float CurrentPawnSpeed;
};
