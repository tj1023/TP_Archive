// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "ProjectN.h"
#include "GameFramework/SaveGame.h"
#include "NSaveGame.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTN_API UNSaveGame : public USaveGame
{
	GENERATED_BODY()

public:
	UNSaveGame();

	UPROPERTY()
		TArray<int32> ProgressStatus;

	UPROPERTY()
		int32 Happy;

	UPROPERTY()
		int32 Sad;

	UPROPERTY()
		int32 Anger;

	UPROPERTY()
		int32 Bored;

	UPROPERTY()
		int32 Survival_time;

	// 물 공포증 수치
	UPROPERTY()
		int32 Aquaphobia;

	// 상태이상
	UPROPERTY()
		bool Status_Effect0;

	UPROPERTY()
		bool Status_Effect1;

	UPROPERTY()
		bool Status_Effect2;

	UPROPERTY()
		bool Status_Effect3;
};
