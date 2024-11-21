// Fill out your copyright notice in the Description page of Project Settings.


#include "BTService_Detect.h"
#include "TOAIEnemyController.h"
#include "TOCharacter.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "DrawDebugHelpers.h"
#include "TOEnemy.h"


UBTService_Detect::UBTService_Detect()
{
	NodeName = TEXT("Detect");

	// 감지 주기
	Interval = 1.0f;
}



/*
* 반경 내의 캐릭터 감지
*/
void UBTService_Detect::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);

	APawn* ControllingPawn = OwnerComp.GetAIOwner()->GetPawn();
	if (nullptr == ControllingPawn) return;

	UWorld* World = ControllingPawn->GetWorld();
	FVector Center = ControllingPawn->GetActorLocation();

	// 반경 거리
	float DetectRadius = 1000;

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

	// 타겟 지정, DrawDebug
	if (bResult)
	{
		for (auto const& OverlapResult : OverlapResults) {
			ATOCharacter* TOCharacter = Cast<ATOCharacter>(OverlapResult.GetActor());
			if (TOCharacter && TOCharacter->GetController()->IsPlayerController())
			{
				OwnerComp.GetBlackboardComponent()->SetValueAsObject(ATOAIEnemyController::TargetKey, TOCharacter);
				DrawDebugSphere(World, Center, DetectRadius, 16, FColor::Green, false, 0.2f);
				DrawDebugPoint(World, TOCharacter->GetActorLocation(), 10.0f, FColor::Blue, false, 0.2f);
				DrawDebugLine(World, ControllingPawn->GetActorLocation(), TOCharacter->GetActorLocation(), FColor::Blue, false, 0.27f);
				return;
			}
		}
	}

	OwnerComp.GetBlackboardComponent()->SetValueAsObject(ATOAIEnemyController::TargetKey, nullptr);
	DrawDebugSphere(World, Center, DetectRadius, 16, FColor::Red, false, 0.2);
}

