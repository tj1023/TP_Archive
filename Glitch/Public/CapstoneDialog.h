// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Blueprint/IUserObjectListEntry.h"
#include "CapstoneDialog.generated.h"

/**
 * 
 */
UCLASS()
class CAPSTONE_API UCapstoneDialog : public UUserWidget, public IUserObjectListEntry
{
	GENERATED_BODY()
	
public:
	virtual void NativeOnListItemObjectSet(UObject* ListItemObject) override;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = true))
	class UTextBlock* textBlock;

	UPROPERTY(Meta = (BindWidgetAnim), Transient)
	class UWidgetAnimation* FadeIn;

protected:
	virtual void NativeConstruct() override;
};
