// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Tellours.h"
#include "Blueprint/UserWidget.h"
#include "TOSaveScript.generated.h"

/**
 * 
 */
UCLASS()
class TELLOURS_API UTOSaveScript : public UUserWidget
{
	GENERATED_BODY()
	
public:
	virtual void NativeConstruct() override;
};
