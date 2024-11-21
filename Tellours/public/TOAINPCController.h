// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Tellours.h"
#include "AIController.h"
#include "TOAINPCController.generated.h"


UCLASS()
class TELLOURS_API ATOAINPCController : public AAIController
{
	GENERATED_BODY()

// 비헤이비어트리 구동을 위한 생성자
public:
	ATOAINPCController();

	virtual void OnPossess(APawn* InPawn) override;

// 생성위치, 순찰위치, 타겟 할당
public:
	static const FName HomePosKey;
	static const FName PatrolPosKey;
	static const FName TargetKey;

private:
	UPROPERTY()
		class UBehaviorTree* BTAsset;

	UPROPERTY()
		class UBlackboardData* BBAsset;
};
