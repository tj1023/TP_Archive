// Fill out your copyright notice in the Description page of Project Settings.


#include "BTDecorator_IsInAttackRange.h"
#include "TOAIEnemyController.h"
#include "TOEnemy.h"
#include "TOCharacter.h"
#include "BehaviorTree/BlackboardComponent.h"


UBTDecorator_IsInAttackRange::UBTDecorator_IsInAttackRange()
{
	NodeName = TEXT("CanAttack");
}

/*
* 거리 안에 드는지 계산
*/
bool UBTDecorator_IsInAttackRange::CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const
{
	bool bResult = Super::CalculateRawConditionValue(OwnerComp, NodeMemory);

	auto ControllingPawn = Cast<ATOEnemy>(OwnerComp.GetAIOwner()->GetPawn());
	if (nullptr == ControllingPawn)
		return false;

	auto Target = Cast<ATOCharacter>(OwnerComp.GetBlackboardComponent()->GetValueAsObject(ATOAIEnemyController::TargetKey));
	if (nullptr == Target)
		return false;

	bResult = (Target->GetDistanceTo(ControllingPawn) <= 200);

	return bResult;
}
