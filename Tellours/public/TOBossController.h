// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Tellours.h"
#include "AIController.h"
#include "TOBossController.generated.h"

/**
 * 
 */
UCLASS()
class TELLOURS_API ATOBossController : public AAIController
{
	GENERATED_BODY()
	
	
public:
	ATOBossController();
	virtual void OnPossess(APawn* InPawn) override;
	virtual void Tick(float DeltaTime) override;


public:
	static const FName HomePosKey;
	static const FName PatrolPosKey;
	static const FName TargetKey;
	void StartAI();
	void StopAI();
	void Phase_0_function();
	void Phase_1_function();
	void Phase_2_function();

private:
	UPROPERTY()
		class UBehaviorTree* BTAsset;

	UPROPERTY()
		class UBlackboardData* BBAsset;
	
	UPROPERTY()
		UBehaviorTreeComponent* BehaviorTreeComponent;
};
