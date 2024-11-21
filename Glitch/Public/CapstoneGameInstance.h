// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "CapstoneGameInstance.generated.h"

/**
 * 
 */
UCLASS()
class CAPSTONE_API UCapstoneGameInstance : public UGameInstance
{
	GENERATED_BODY()

public:
	UCapstoneGameInstance();

	virtual void Init() override;
	
};
