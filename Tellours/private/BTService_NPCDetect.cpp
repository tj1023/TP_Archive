// Fill out your copyright notice in the Description page of Project Settings.


#include "BTService_NPCDetect.h"
#include "TOCharacter.h"
#include "TONPC.h"
#include "TOAINPCController.h"
#include "BehaviorTree/BlackboardComponent.h"

UBTService_NPCDetect::UBTService_NPCDetect()
{
	NodeName = TEXT("Detect");

	// ���� �ֱ�
	Interval = 1.0f;
}



/*
* �ݰ� ���� ĳ���� ����
*/
void UBTService_NPCDetect::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);

	APawn* ControllingPawn = OwnerComp.GetAIOwner()->GetPawn();
	if (nullptr == ControllingPawn) return;

	UWorld* World = ControllingPawn->GetWorld();
	FVector Center = ControllingPawn->GetActorLocation();

	// �ݰ� �Ÿ�
	float DetectRadius = 200;

	if (nullptr == World) return;

	TArray<FOverlapResult> OverlapResults;
	FCollisionQueryParams CollisionQueryParam(NAME_None, false, ControllingPawn);
	bool bResult = World->OverlapMultiByChannel(
		OverlapResults,
		Center,
		FQuat::Identity,
		ECollisionChannel::ECC_GameTraceChannel2,
		FCollisionShape::MakeSphere(DetectRadius),
		CollisionQueryParam
	);

	// Ÿ�� ����
	if (bResult)
	{
		for (auto const& OverlapResult : OverlapResults) {
			ATOCharacter* TOCharacter = Cast<ATOCharacter>(OverlapResult.GetActor());
			if (TOCharacter && TOCharacter->GetController()->IsPlayerController())
			{
				OwnerComp.GetBlackboardComponent()->SetValueAsObject(ATOAINPCController::TargetKey, TOCharacter);
				return;
			}
		}
	}

	OwnerComp.GetBlackboardComponent()->SetValueAsObject(ATOAINPCController::TargetKey, nullptr);
}
