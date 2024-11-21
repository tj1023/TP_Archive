// Fill out your copyright notice in the Description page of Project Settings.


#include "TOAINPCController.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BlackboardData.h"
#include "BehaviorTree/BlackboardComponent.h"



/*
* ������ġ, ������ġ, Ÿ�� �Ҵ�
*/
const FName ATOAINPCController::HomePosKey(TEXT("HomePos"));
const FName ATOAINPCController::PatrolPosKey(TEXT("PatrolPos"));
const FName ATOAINPCController::TargetKey(TEXT("Target"));

ATOAINPCController::ATOAINPCController()
{
	// ������, �����̺��Ʈ�� ���� �� ����
	static ConstructorHelpers::FObjectFinder<UBlackboardData> BBObject(TEXT("/Game/Tellours/Developer/AI/BB_TONPC.BB_TONPC"));
	if (BBObject.Succeeded())
	{
		BBAsset = BBObject.Object;
	}

	static ConstructorHelpers::FObjectFinder<UBehaviorTree> BTObject(TEXT("/Game/Tellours/Developer/AI/BT_TONPC.BT_TONPC"));
	if (BTObject.Succeeded())
	{
		BTAsset = BTObject.Object;
	}
}



/*
* �� ���� �� ��ġ����
*/
void ATOAINPCController::OnPossess(APawn* InPawn) {
	Super::OnPossess(InPawn);

	if (UseBlackboard(BBAsset, Blackboard))
	{
		Blackboard->SetValueAsVector(HomePosKey, GetPawn()->GetActorLocation());
		if (!RunBehaviorTree(BTAsset))
		{
			ABLOG(Error, TEXT("AIController couldn't run behavior tree!"));
		}
	}
}
