// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Tellours.h"
#include "BehaviorTree/BTService.h"
#include "BTService_BossDetect.generated.h"

/**
 * 
 */
UCLASS()
class TELLOURS_API UBTService_BossDetect : public UBTService
{
	GENERATED_BODY()
	

	public:
	// 기본 생성자
		UBTService_BossDetect();


protected:
	// 감지를 위한 주기적 호출
	virtual void TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;
	
};
