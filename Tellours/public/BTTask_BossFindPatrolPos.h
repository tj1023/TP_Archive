// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "BTTask_BossFindPatrolPos.generated.h"

/**
 * 
 */
UCLASS()
class TELLOURS_API UBTTask_BossFindPatrolPos : public UBTTaskNode
{
	GENERATED_BODY()
	
public:
	UBTTask_BossFindPatrolPos();

	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnereComp, uint8* NodeMemory) override;
};
