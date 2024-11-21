// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "GhostAIController.generated.h"

/**
 * 
 */
UCLASS()
class CAPSTONE_API AGhostAIController : public AAIController
{
	GENERATED_BODY()

public:
	AGhostAIController();
	virtual void OnPossess(APawn* InPawn) override;

	static FName Target;
	static FName PatrolPosKey;
	static FName CenterPosKey;
	static FName ForwardRotator;
	static FName SearchParameter;

private:
	UPROPERTY()
	class UBehaviorTree* BTAsset;

	UPROPERTY()
	class UBlackboardData* BBAsset;
};
