// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTask_FindCenterPos.h"
#include "GhostAIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "NavigationSystem.h"
#include "DrawDebugHelpers.h"
#include "CapstoneCharacter.h"

UBTTask_FindCenterPos::UBTTask_FindCenterPos()
{
	NodeName = TEXT("KeepCenterPos");
}

EBTNodeResult::Type UBTTask_FindCenterPos::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	EBTNodeResult::Type Result = Super::ExecuteTask(OwnerComp, NodeMemory);

	auto ControllingPawn = OwnerComp.GetAIOwner()->GetPawn();
	if (nullptr == ControllingPawn)
		return EBTNodeResult::Failed;

	OwnerComp.GetBlackboardComponent()->SetValueAsFloat(AGhostAIController::SearchParameter, 1.0f);
	FVector Origin = ControllingPawn->GetActorLocation();

	FCollisionQueryParams TraceParameters(NAME_None, false, ControllingPawn);
	FHitResult Dir;
	FVector DirVec[4] = { FVector(1,0,0), FVector(0,1,0), FVector(-1,0,0), FVector(0,-1,0) };

	OwnerComp.GetBlackboardComponent()->SetValueAsVector(AGhostAIController::CenterPosKey, Origin);

	for (int i = 0; i < 4; i++) {
		GetWorld()->LineTraceSingleByChannel(
			Dir,
			Origin,
			Origin + DirVec[i] * 220,
			ECollisionChannel::ECC_GameTraceChannel1,
			TraceParameters
		);
		/*DrawDebugLine(
			GetWorld(),
			Origin,
			Origin + DirVec[i] * 220,
			FColor(255, 0, 0),
			false,
			1.f,
			0.f,
			10.f
		);*/

		OwnerComp.GetBlackboardComponent()->SetValueAsRotator(AGhostAIController::ForwardRotator, ControllingPawn->GetActorRotation());

		ACapstoneCharacter* Character = Cast<ACapstoneCharacter>(Dir.Actor);
		if (Dir.Actor.IsValid() && !(Character && Character->GetController()->IsPlayerController())) {
			int dis;
			if (i % 2 == 0)
				dis = /*280 - */abs(Dir.Actor->GetActorLocation().X - Origin.X);
			else
				dis = /*280 - */abs(Dir.Actor->GetActorLocation().Y - Origin.Y);

			OwnerComp.GetBlackboardComponent()->SetValueAsVector(AGhostAIController::CenterPosKey, Origin + DirVec[(i + 2) % 4] * dis);
			return EBTNodeResult::Succeeded;
		}
	}

	return EBTNodeResult::Succeeded;
}
