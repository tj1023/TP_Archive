// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTask_EnemyAttack.h"
#include "TOAIEnemyController.h"
#include "TOEnemy.h"


UBTTask_EnemyAttack::UBTTask_EnemyAttack()
{
	bNotifyTick = true;
	IsAttacking = false;
}

EBTNodeResult::Type UBTTask_EnemyAttack::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	EBTNodeResult::Type Result = Super::ExecuteTask(OwnerComp, NodeMemory);

	auto TOEnemy = Cast<ATOEnemy>(OwnerComp.GetAIOwner()->GetPawn());
	if (nullptr == TOEnemy)
		return EBTNodeResult::Failed;

	TOEnemy->Attack();
	IsAttacking = true;
	TOEnemy->OnAttackEnd.AddLambda([this]() -> void {
		IsAttacking = false;
		});

	return EBTNodeResult::InProgress;
}

void UBTTask_EnemyAttack::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickTask(OwnerComp, NodeMemory, DeltaSeconds);
	if (!IsAttacking)
	{
		FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
	}
}
