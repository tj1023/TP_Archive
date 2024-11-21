// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Tellours.h"
#include "GameFramework/Actor.h"
#include "TOCharacter.h"
#include "TOItem.generated.h"


/*
* 아이템 분류
*/
UENUM()
enum class ItemType {
	SWORD,
	POTION,
	KEY,
	MAP,
	FLOWER
};


UCLASS()
class TELLOURS_API ATOItem : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ATOItem();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;



public:
	UPROPERTY(VisibleAnywhere, Category = Item)
		UStaticMeshComponent* Item;

// 상호작용
public:
	UPROPERTY(VisibleAnywhere, Category = UI)
		class UWidgetComponent* InteractionWidget;

	void SetInteractionUIVisible(bool NewBool);

	void ItemDrop();

// 아이템 분류
public:
	void SetItemType(ItemType NewItemType);
	ItemType GetItemType();

private:
	UPROPERTY(EditAnywhere, Category = Spawn, Meta = (AllowPrivateAccess = true))
		ItemType CurrentItemType;
};
