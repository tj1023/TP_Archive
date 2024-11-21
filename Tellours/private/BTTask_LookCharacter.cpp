// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTask_LookCharacter.h"
#include "TOAINPCController.h"
#include "TONPC.h"
#include "TOCharacter.h"
#include "BehaviorTree/BlackboardComponent.h"

UBTTask_LookCharacter::UBTTask_LookCharacter()
{
	NodeName = TEXT("LookCharacter");
}

EBTNodeResult::Type UBTTask_LookCharacter::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	EBTNodeResult::Type Result = Super::ExecuteTask(OwnerComp, NodeMemory);

	auto TONPC = Cast<ATONPC>(OwnerComp.GetAIOwner()->GetPawn());
	if (nullptr == TONPC)
		return EBTNodeResult::Failed;

	auto Target = Cast<ATOCharacter>(OwnerComp.GetBlackboardComponent()->GetValueAsObject(ATOAINPCController::TargetKey));
	if (nullptr == Target)
		return EBTNodeResult::Failed;

	FVector LookVector = Target->GetActorLocation() - TONPC->GetActorLocation();
	LookVector.Z = 0.0f;
	FRotator TargetRot = FRotationMatrix::MakeFromX(LookVector).Rotator();
	TONPC->SetActorRotation(FMath::RInterpTo(TONPC->GetActorRotation(), TargetRot, GetWorld()->GetDeltaSeconds(), 4.0f));

	return EBTNodeResult::Succeeded;
}
