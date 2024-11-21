// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTask_TurnToTarget.h"
#include "TOAIEnemyController.h"
#include "TOEnemy.h"
#include "TOCharacter.h"
#include "BehaviorTree/BlackboardComponent.h"

UBTTask_TurnToTarget::UBTTask_TurnToTarget()
{
	NodeName = TEXT("Turn");
}

EBTNodeResult::Type UBTTask_TurnToTarget::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	EBTNodeResult::Type Result = Super::ExecuteTask(OwnerComp, NodeMemory);

	auto TOEnemy = Cast<ATOEnemy>(OwnerComp.GetAIOwner()->GetPawn());
	if (nullptr == TOEnemy)
		return EBTNodeResult::Failed;

	auto Target = Cast<ATOCharacter>(OwnerComp.GetBlackboardComponent()->GetValueAsObject(ATOAIEnemyController::TargetKey));
	if (nullptr == Target)
		return EBTNodeResult::Failed;

	FVector LookVector = Target->GetActorLocation() - TOEnemy->GetActorLocation();
	LookVector.Z = 0.0f;
	FRotator TargetRot = FRotationMatrix::MakeFromX(LookVector).Rotator();
	TOEnemy->SetActorRotation(FMath::RInterpTo(TOEnemy->GetActorRotation(), TargetRot, GetWorld()->GetDeltaSeconds(), 2.0f));

	return EBTNodeResult::Succeeded;
}
