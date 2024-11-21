// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "ProjectN.h"
#include "GameFramework/PlayerState.h"
#include "NPlayerState.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTN_API ANPlayerState : public APlayerState
{
	GENERATED_BODY()

	ANPlayerState();

protected:
	virtual void BeginPlay() override;
	
public:
	void InitPlayerData();
	void SavePlayerData();

	FString SaveDataName;

	UPROPERTY()
		TArray<int32> ProgressStatus;

	UPROPERTY(Transient)
		int32 Happy;

	UPROPERTY(Transient)
		int32 Sad;

	UPROPERTY(Transient)
		int32 Anger;

	UPROPERTY(Transient)
		int32 Bored;

	UPROPERTY(Transient)
		int32 Survival_time;

	// 물 공포증 수치
	UPROPERTY(Transient)
		int32 Aquaphobia;

	// 상태이상
	UPROPERTY(Transient)
		bool Status_Effect0;

	UPROPERTY(Transient)
		bool Status_Effect1;

	UPROPERTY(Transient)
		bool Status_Effect2;

	UPROPERTY(Transient)
		bool Status_Effect3;

};
