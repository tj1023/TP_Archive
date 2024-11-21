// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "BTTask_FindCenterPos.generated.h"

/**
 * 
 */
UCLASS()
class CAPSTONE_API UBTTask_FindCenterPos : public UBTTaskNode
{
	GENERATED_BODY()
	
public:
	UBTTask_FindCenterPos();

	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
};
