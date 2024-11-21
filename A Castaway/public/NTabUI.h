// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "ProjectN.h"
#include "Blueprint/UserWidget.h"
#include "NTabUI.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTN_API UNTabUI : public UUserWidget
{
	GENERATED_BODY()
	
public:
	virtual void NativeConstruct() override;
	
};
