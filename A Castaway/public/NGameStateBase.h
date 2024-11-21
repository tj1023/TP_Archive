// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "ProjectN.h"
#include "GameFramework/GameStateBase.h"
#include "NGameStateBase.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTN_API ANGameStateBase : public AGameStateBase
{
	GENERATED_BODY()

public:
	ANGameStateBase();
	
//	void InitProgress();
//
//	void AddProgress_Main();
//	void AddProgress_A();
//	void AddProgress_B();
//
//private:
//	UPROPERTY(Transient)
//		int32 MainProgress;
//
//	UPROPERTY(Transient)
//		int32 AProgress;
//
//	UPROPERTY(Transient)
//		int32 BProgress;
};
