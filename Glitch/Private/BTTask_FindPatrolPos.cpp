// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTask_FindPatrolPos.h"
#include "GhostAIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "NavigationSystem.h"
#include "DrawDebugHelpers.h"
#include "CapstoneCharacter.h"

UBTTask_FindPatrolPos::UBTTask_FindPatrolPos()
{
	NodeName = TEXT("FindPatrolPos");
}

EBTNodeResult::Type UBTTask_FindPatrolPos::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	EBTNodeResult::Type Result = Super::ExecuteTask(OwnerComp, NodeMemory);

	auto ControllingPawn = OwnerComp.GetAIOwner()->GetPawn();
	if (nullptr == ControllingPawn)
		return EBTNodeResult::Failed;

	FVector Origin = ControllingPawn->GetActorLocation();

	FCollisionQueryParams TraceParameters(NAME_None, false, ControllingPawn);
	FHitResult Dir;
	FHitResult Forward;
	FVector DirVec[4] = { FVector(1,0,0), FVector(-1,0,0), FVector(0,1,0), FVector(0,-1,0) };
	bool DirHit[4] = { false, false, false, false };

	for (int i = 0; i < 4; i++) {
		GetWorld()->LineTraceSingleByChannel(
			Dir,
			Origin,
			Origin + DirVec[i] * 1000,
			ECollisionChannel::ECC_GameTraceChannel1,
			TraceParameters
		);
		ACapstoneCharacter* Character = Cast<ACapstoneCharacter>(Dir.Actor);
		if (Dir.Actor.IsValid() && !(Character && Character->GetController()->IsPlayerController()))
			DirHit[i] = true;

		/*DrawDebugLine(
			GetWorld(),
			Origin,
			Origin + DirVec[i] * 1000,
			FColor(255, 0, 0),
			false,
			1.f,
			0.f,
			10.f
		);*/
	}

	if ((DirHit[0] && DirHit[1] && !DirHit[2] && !DirHit[3]) || (!DirHit[0] && !DirHit[1] && DirHit[2] && DirHit[3])) {
		ControllingPawn->SetActorRotation(OwnerComp.GetBlackboardComponent()->GetValueAsRotator(AGhostAIController::ForwardRotator));

		GetWorld()->LineTraceSingleByChannel(
			Forward,
			Origin,
			Origin + ControllingPawn->GetActorForwardVector() * 1000,
			ECollisionChannel::ECC_GameTraceChannel1,
			TraceParameters
		);
		if (!Forward.Actor.IsValid()) {
			OwnerComp.GetBlackboardComponent()->SetValueAsVector(AGhostAIController::PatrolPosKey, Origin + ControllingPawn->GetActorForwardVector() * 1000);
			return EBTNodeResult::Succeeded;
		}
	}

	int RandDir = FMath::RandRange(0, 3);
	if (!DirHit[RandDir]) {
		OwnerComp.GetBlackboardComponent()->SetValueAsVector(AGhostAIController::PatrolPosKey, Origin + DirVec[RandDir] * 1000);
		return EBTNodeResult::Succeeded;
	}

	return EBTNodeResult::Failed;
}
