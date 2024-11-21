// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "BTTask_FindPatrolPos.generated.h"

/**
 * 
 */
UCLASS()
class TELLOURS_API UBTTask_FindPatrolPos : public UBTTaskNode
{
	GENERATED_BODY()
	

public:
	UBTTask_FindPatrolPos();

	// �½�ũ ����
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnereComp, uint8* NodeMemory) override;
};
