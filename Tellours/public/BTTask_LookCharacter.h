// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "BTTask_LookCharacter.generated.h"

/**
 * 
 */
UCLASS()
class TELLOURS_API UBTTask_LookCharacter : public UBTTaskNode
{
	GENERATED_BODY()
	

public:
	UBTTask_LookCharacter();

	// �½�ũ ����
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnereComp, uint8* NodeMemory) override;
};
