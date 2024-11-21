// Fill out your copyright notice in the Description page of Project Settings.


#include "TOBossController.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BlackboardData.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "NavigationSystem.h"

const FName ATOBossController::HomePosKey(TEXT("HomePos"));
const FName ATOBossController::PatrolPosKey(TEXT("PatrolPos"));
const FName ATOBossController::TargetKey(TEXT("Target"));

ATOBossController::ATOBossController()
{
	PrimaryActorTick.bCanEverTick = true;

	static ConstructorHelpers::FObjectFinder<UBlackboardData> BBObject(TEXT("/Game/Tellours/Developer/AI/BB_TOFirstBoss.BB_TOFirstBoss"));
	if (BBObject.Succeeded())
	{
		BBAsset = BBObject.Object;
	}

	static ConstructorHelpers::FObjectFinder<UBehaviorTree> BTObject(TEXT("/Game/Tellours/Developer/AI/BT_TOFirstBoss.BT_TOFirstBoss"));
	if (BTObject.Succeeded())
	{
		BTAsset = BTObject.Object;
	}

	BehaviorTreeComponent = CreateDefaultSubobject<UBehaviorTreeComponent>(TEXT("BehaviorTreeComponent"));
	BehaviorTreeComponent->RegisterComponent();
	BehaviorTreeComponent->StartTree(*BTAsset);
}

void ATOBossController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
}

void ATOBossController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);

	if (UseBlackboard(BBAsset, Blackboard))
	{
		Blackboard->SetValueAsVector(HomePosKey, GetPawn()->GetActorLocation());
		if (!RunBehaviorTree(BTAsset))
		{
			ABLOG(Error, TEXT("AIController couldn't run behavior tree!"));
		}
	}

	Phase_0_function();
}

void ATOBossController::StartAI()
{
	if (!BehaviorTreeComponent->IsRunning())
	{
		BehaviorTreeComponent->StartTree(*BTAsset);
	}
}

void ATOBossController::StopAI()
{
	ABLOG(Warning, TEXT("Stop AI In"))
	if (BehaviorTreeComponent->IsRunning())
	{
		ABLOG(Warning, TEXT("Stop AI"))
		BehaviorTreeComponent->StopTree(EBTStopMode::Safe);
	}
}

void ATOBossController::Phase_0_function()
{
	StopAI();
}

void ATOBossController::Phase_1_function()
{
	StartAI();
}

void ATOBossController::Phase_2_function()
{
	StartAI();
}