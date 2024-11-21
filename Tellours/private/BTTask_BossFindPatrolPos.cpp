// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTask_BossFindPatrolPos.h"
#include "TOBossController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "NavigationSystem.h"

UBTTask_BossFindPatrolPos::UBTTask_BossFindPatrolPos()
{
	NodeName = TEXT("BossFindPatrolPos");
}

/*
* 다음 정찰 지점 찾는 로직 구현, 실행 결과 바로 반환
*/
EBTNodeResult::Type UBTTask_BossFindPatrolPos::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	EBTNodeResult::Type Result = Super::ExecuteTask(OwnerComp, NodeMemory);

	auto ControllingPawn = OwnerComp.GetAIOwner()->GetPawn();
	if (nullptr == ControllingPawn)
		return EBTNodeResult::Failed;

	UNavigationSystemV1* NavSystem = UNavigationSystemV1::GetNavigationSystem(ControllingPawn->GetWorld());
	if (nullptr == NavSystem)
		return EBTNodeResult::Failed;

	FVector Origin = OwnerComp.GetBlackboardComponent()->GetValueAsVector(ATOBossController::HomePosKey);
	FNavLocation NextPatrol;

	if (NavSystem->GetRandomPointInNavigableRadius(Origin, 500, NextPatrol))
	{
		OwnerComp.GetBlackboardComponent()->SetValueAsVector(ATOBossController::PatrolPosKey, NextPatrol.Location);

		return EBTNodeResult::Succeeded;
	}

	return EBTNodeResult::Failed;
}
