// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTask_BossAttack.h"
#include "TOBossController.h"
#include "TOFirstBoss.h"

UBTTask_BossAttack::UBTTask_BossAttack()
{
	bNotifyTick = true;
	IsAttacking = false;
}

EBTNodeResult::Type UBTTask_BossAttack::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	EBTNodeResult::Type Result = Super::ExecuteTask(OwnerComp, NodeMemory);

	auto TOFirstBoss = Cast<ATOFirstBoss>(OwnerComp.GetAIOwner()->GetPawn());
	if (nullptr == TOFirstBoss)
		return EBTNodeResult::Failed;
	
	TOFirstBoss->Attack();
	
	IsAttacking = true;
	TOFirstBoss->OnAttackEnd.AddLambda([this]() -> void {
		IsAttacking = false;
		});
	return EBTNodeResult::InProgress;
}

void UBTTask_BossAttack::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickTask(OwnerComp, NodeMemory, DeltaSeconds);
	if (!IsAttacking)
	{
		FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
	}
}
