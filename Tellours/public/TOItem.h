// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Tellours.h"
#include "GameFramework/Actor.h"
#include "TOCharacter.h"
#include "TOItem.generated.h"


/*
* ������ �з�
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

// ��ȣ�ۿ�
public:
	UPROPERTY(VisibleAnywhere, Category = UI)
		class UWidgetComponent* InteractionWidget;

	void SetInteractionUIVisible(bool NewBool);

	void ItemDrop();

// ������ �з�
public:
	void SetItemType(ItemType NewItemType);
	ItemType GetItemType();

private:
	UPROPERTY(EditAnywhere, Category = Spawn, Meta = (AllowPrivateAccess = true))
		ItemType CurrentItemType;
};
