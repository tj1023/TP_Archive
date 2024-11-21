// Fill out your copyright notice in the Description page of Project Settings.


#include "BTService_TargetSearch.h"
#include "GhostAIController.h"
#include "CapstoneCharacter.h"
#include "CharacterBody.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "DrawDebugHelpers.h"

UBTService_TargetSearch::UBTService_TargetSearch()
{
	NodeName = TEXT("TargetSearch");
	Interval = 0.2f;
}

void UBTService_TargetSearch::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);

	APawn* ControllingPawn = OwnerComp.GetAIOwner()->GetPawn();
	if (nullptr == ControllingPawn) return;

	FVector Origin = ControllingPawn->GetActorLocation();
	FVector Forward = ControllingPawn->GetActorForwardVector();
	Forward.Normalize();

	float SearchParameter = OwnerComp.GetBlackboardComponent()->GetValueAsFloat(AGhostAIController::SearchParameter);

	FCollisionQueryParams TraceParameters(NAME_None, false, ControllingPawn);
	FHitResult Dir;
	ACapstoneCharacter* Character;
	ACharacterBody* CharacterBody;

	for (int i = -50; i <= 50; i++) {
		GetWorld()->LineTraceSingleByChannel(
			Dir,
			Origin,
			Origin + Forward.RotateAngleAxis(i, FVector::UpVector) * 2000 * SearchParameter,
			ECollisionChannel::ECC_GameTraceChannel1,
			TraceParameters
		);
		/*DrawDebugLine(
			GetWorld(),
			Origin,
			Origin + Forward.RotateAngleAxis(i, FVector::UpVector) * 2000 * SearchParameter,
			FColor(0, 0, 255),
			false,
			1.f,
			0.f,
			10.f
		);*/
		if (Dir.Actor.IsValid()) {
			Character = Cast<ACapstoneCharacter>(Dir.Actor);
			CharacterBody = Cast<ACharacterBody>(Dir.Actor);
			
			if (CharacterBody) {
				OwnerComp.GetBlackboardComponent()->SetValueAsObject(AGhostAIController::Target, CharacterBody);
				OwnerComp.GetBlackboardComponent()->SetValueAsVector(AGhostAIController::PatrolPosKey, CharacterBody->GetActorLocation());
				OwnerComp.GetBlackboardComponent()->SetValueAsFloat(AGhostAIController::SearchParameter, 1.5f);
				return;
			}
			if (!CharacterBody && Character && Character->GetController()->IsPlayerController()) {
				OwnerComp.GetBlackboardComponent()->SetValueAsObject(AGhostAIController::Target, Character);
				OwnerComp.GetBlackboardComponent()->SetValueAsVector(AGhostAIController::PatrolPosKey, Character->GetActorLocation());
				OwnerComp.GetBlackboardComponent()->SetValueAsFloat(AGhostAIController::SearchParameter, 1.5f);
				return;
			}
		}
	}

	Character = Cast<ACapstoneCharacter>(GetWorld()->GetFirstPlayerController()->GetPawn());
	if ((Origin - Character->GetActorLocation()).Size() <= 500) {
		OwnerComp.GetBlackboardComponent()->SetValueAsObject(AGhostAIController::Target, Character);
		OwnerComp.GetBlackboardComponent()->SetValueAsVector(AGhostAIController::PatrolPosKey, Character->GetActorLocation());
		OwnerComp.GetBlackboardComponent()->SetValueAsFloat(AGhostAIController::SearchParameter, 1.5f);
		return;
	}

	OwnerComp.GetBlackboardComponent()->SetValueAsObject(AGhostAIController::Target, nullptr);
	OwnerComp.GetBlackboardComponent()->SetValueAsFloat(AGhostAIController::SearchParameter, 1.0f);
	return;
}
