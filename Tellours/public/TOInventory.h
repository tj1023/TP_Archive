// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Tellours.h"
#include "Blueprint/UserWidget.h"
#include "TOInventory.generated.h"

/**
 *
 */
UCLASS()
class TELLOURS_API UTOInventory : public UUserWidget
{
	GENERATED_BODY()
public:
	virtual void NativeConstruct() override;

public:
	// Inventory Item Count
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
		TArray<class UTextBlock* > AInventoryItemCount;

	// Inventory Button
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
		TArray<class UButton* > AInventoryButton;

	// If Item Count is Zero, Show Shadow Image
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
		TArray<class UImage *> AInventoryImage;

	// Check ItemCount function
	void CheckItemCount(int32 ItemNum);

	void ItemAdd(int32 ItemNum);

private:
	UPROPERTY()
		TArray<int32> InventoryItemCount;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
		class ATOPlayerController* TOPlayerController;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
		class ATOCharacter* TOCharacter;

	UFUNCTION(BlueprintCallable)
		void SlotClickEvent0();

	UFUNCTION(BlueprintCallable)
		void SlotClickEvent1();

	UFUNCTION(BlueprintCallable)
		void SlotClickEvent2();

	UFUNCTION(BlueprintCallable)
		void SlotClickEvent3();
	
	UFUNCTION(BlueprintCallable)
		void SlotClickEvent4();

	void InitInventoryItemCount();
	void ItemUse(int32 ItemNum);
};
