
// Fill out your copyright notice in the Description page of Project Settings.


#include "TOAIEnemyController.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BlackboardData.h"
#include "BehaviorTree/BlackboardComponent.h"




/*
* ������ġ, ������ġ, Ÿ�� �Ҵ�
*/
const FName ATOAIEnemyController::HomePosKey(TEXT("HomePos"));
const FName ATOAIEnemyController::PatrolPosKey(TEXT("PatrolPos"));
const FName ATOAIEnemyController::TargetKey(TEXT("Target"));

ATOAIEnemyController::ATOAIEnemyController()
{
	// ������, �����̺��Ʈ�� ���� �� ����
	static ConstructorHelpers::FObjectFinder<UBlackboardData> BBObject(TEXT("/Game/Tellours/Developer/AI/BB_TOEnemy.BB_TOEnemy"));
	if (BBObject.Succeeded())
	{
		BBAsset = BBObject.Object;
	}

	static ConstructorHelpers::FObjectFinder<UBehaviorTree> BTObject(TEXT("/Game/Tellours/Developer/AI/BT_TOEnemy.BT_TOEnemy"));
	if (BTObject.Succeeded())
	{
		BTAsset = BTObject.Object;
	}
}



/*
* �� ���� �� ��ġ����
*/
void ATOAIEnemyController::OnPossess(APawn* InPawn) {
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



void ATOAIEnemyController::StopAI()
{
	auto BehaviorTreeComponent = Cast<UBehaviorTreeComponent>(BrainComponent);
	if (nullptr != BehaviorTreeComponent)
	{
		BehaviorTreeComponent->StopTree(EBTStopMode::Safe);
	}
}
