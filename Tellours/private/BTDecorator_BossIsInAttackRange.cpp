// Fill out your copyright notice in the Description page of Project Settings.


#include "BTDecorator_BossIsInAttackRange.h"
#include "TOBossController.h"
#include "TOFirstBoss.h"
#include "TOCharacter.h"
#include "BehaviorTree/BlackboardComponent.h"


UBTDecorator_BossIsInAttackRange::UBTDecorator_BossIsInAttackRange()
{
	NodeName = TEXT("BossCanAttack");
}

/*
* 거리 안에 드는지 계산
*/
bool UBTDecorator_BossIsInAttackRange::CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const
{
	bool bResult = Super::CalculateRawConditionValue(OwnerComp, NodeMemory);

	auto ControllingPawn = Cast<ATOFirstBoss>(OwnerComp.GetAIOwner()->GetPawn());
	if (nullptr == ControllingPawn)
		return false;

	auto Target = Cast<ATOCharacter>(OwnerComp.GetBlackboardComponent()->GetValueAsObject(ATOBossController::TargetKey));
	if (nullptr == Target)
		return false;

	bResult = (Target->GetDistanceTo(ControllingPawn) <= 400);

	return bResult;
}