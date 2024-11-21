// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Tellours.h"
#include "BehaviorTree/BTDecorator.h"
#include "BTDecorator_IsInAttackRange.generated.h"

/**
 * 
 */
UCLASS()
class TELLOURS_API UBTDecorator_IsInAttackRange : public UBTDecorator
{
	GENERATED_BODY()
	

public:
	UBTDecorator_IsInAttackRange();

protected:
	// 거리 안에 드는지 계산
	virtual bool CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const override;
};
