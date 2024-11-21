// Fill out your copyright notice in the Description page of Project Settings.


#include "GhostAIController.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BlackboardData.h"
#include "BehaviorTree/BlackboardComponent.h"

FName AGhostAIController::Target(TEXT("Target"));
FName AGhostAIController::PatrolPosKey(TEXT("PatrolPos"));
FName AGhostAIController::CenterPosKey(TEXT("CenterPos"));
FName AGhostAIController::ForwardRotator(TEXT("ForwardRotator"));
FName AGhostAIController::SearchParameter(TEXT("SearchParameter"));

AGhostAIController::AGhostAIController()
{
	static ConstructorHelpers::FObjectFinder<UBlackboardData> BBObject(TEXT("/Game/AI/BB_Ghost.BB_Ghost"));
	if (BBObject.Succeeded())
		BBAsset = BBObject.Object;

	static ConstructorHelpers::FObjectFinder<UBehaviorTree> BTObject(TEXT("/Game/AI/BT_Ghost.BT_Ghost"));
	if (BTObject.Succeeded())
		BTAsset = BTObject.Object;
}

void AGhostAIController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);

	if (UseBlackboard(BBAsset, Blackboard))
	{
		if (!RunBehaviorTree(BTAsset))
		{
			;
		}
	}
}
