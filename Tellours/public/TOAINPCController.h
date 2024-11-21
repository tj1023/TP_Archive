// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Tellours.h"
#include "AIController.h"
#include "TOAINPCController.generated.h"


UCLASS()
class TELLOURS_API ATOAINPCController : public AAIController
{
	GENERATED_BODY()

// �����̺��Ʈ�� ������ ���� ������
public:
	ATOAINPCController();

	virtual void OnPossess(APawn* InPawn) override;

// ������ġ, ������ġ, Ÿ�� �Ҵ�
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
