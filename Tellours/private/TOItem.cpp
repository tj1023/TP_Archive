// Fill out your copyright notice in the Description page of Project Settings.


#include "TOItem.h"
#include "TOCharacterStatComponent.h"
#include "Components/WidgetComponent.h"

// Sets default values
ATOItem::ATOItem()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Item = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ITEM"));
	Item->SetSimulatePhysics(true);
	Item->SetMassOverrideInKg(NAME_None, 1000.0f);

	// 상호작용 UI
	InteractionWidget = CreateDefaultSubobject<UWidgetComponent>(TEXT("INTERACTIONWIDGET"));
	InteractionWidget->SetupAttachment(Item);
	InteractionWidget->SetRelativeLocation(FVector(0, 0, 50));
	InteractionWidget->SetWidgetSpace(EWidgetSpace::Screen);
	static ConstructorHelpers::FClassFinder<UUserWidget> UI_Interaction(TEXT("/Game/Tellours/Developer/UI/UI_Interaction.UI_Interaction_C"));
	if (UI_Interaction.Succeeded())
	{
		InteractionWidget->SetWidgetClass(UI_Interaction.Class);
		InteractionWidget->SetDrawSize(FVector2D(50, 40));
	}
	InteractionWidget->SetVisibility(false);
}

// Called when the game starts or when spawned
void ATOItem::BeginPlay()
{
	Super::BeginPlay();
	
	SetItemType(ItemType::FLOWER);
}

// Called every frame
void ATOItem::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}



/*
* 상호작용 UI
*/
void ATOItem::SetInteractionUIVisible(bool NewBool)
{
	InteractionWidget->SetVisibility(NewBool);
}

void ATOItem::ItemDrop()
{
	int32 RandNum = FMath::RandRange(1, 6);
	if (RandNum > 5)
		Destroy();
	else
	{
		switch (RandNum) {

		case 1: {
			SetItemType(ItemType::SWORD);
			break;
		}
		case 2: {
			SetItemType(ItemType::POTION);
			break;
		}
		case 3: {
			SetItemType(ItemType::KEY);
			break;
		}
		case 4: {
			SetItemType(ItemType::MAP);
			break;
		}
		case 5: {
			SetItemType(ItemType::FLOWER);
			break;
		}
		}
	}

	int32 RandX = FMath::RandRange(-5, 5);
	int32 RandY = FMath::RandRange(-5, 5);
	FVector Force = FVector(RandX * 200.0f, RandY * 200.0f, 5000.0f);
	Item->AddForce(Force*1000);
}


/*
* 아이템 분류
* 주의점 : case를 {}로 묶지않으면 오류발생
*/
ItemType ATOItem::GetItemType()
{
	return CurrentItemType;
}

void ATOItem::SetItemType(ItemType NewEnemyType)
{
	CurrentItemType = NewEnemyType;

	switch (CurrentItemType) {

	case ItemType::SWORD: {
		UStaticMesh* SM_Sword = Cast<UStaticMesh>(StaticLoadObject(UStaticMesh::StaticClass(), NULL, TEXT("/Game/AncientTreasures/Meshes/SM_Sword_01a.SM_Sword_01a")));
		if (SM_Sword)
		{
			Item->SetStaticMesh(SM_Sword);
		}
		break;
	}

	case ItemType::POTION: {
		UStaticMesh* SM_Potion = Cast<UStaticMesh>(StaticLoadObject(UStaticMesh::StaticClass(), NULL, TEXT("/Game/Megascans/3D_Assets/Asset_Portion/SM_Portion.SM_Portion")));
		if (SM_Potion)
		{
			Item->SetStaticMesh(SM_Potion);
		}
		break;
	}

	case ItemType::KEY: {
		UStaticMesh* SM_Key = Cast<UStaticMesh>(StaticLoadObject(UStaticMesh::StaticClass(), NULL, TEXT("/Game/Megascans/3D_Assets/Asset_KEY/SM_KEY.SM_KEY")));
		if (SM_Key)
		{
			Item->SetStaticMesh(SM_Key);
		}
		break;
	}

	case ItemType::MAP: {
		UStaticMesh* SM_Map = Cast<UStaticMesh>(StaticLoadObject(UStaticMesh::StaticClass(), NULL, TEXT("/Game/AncientTreasures/Meshes/SM_Map_01a.SM_Map_01a")));
		if (SM_Map)
		{
			Item->SetStaticMesh(SM_Map);
		}
		break;
	}
		
	case ItemType::FLOWER: {
		UStaticMesh* SM_Flower = Cast<UStaticMesh>(StaticLoadObject(UStaticMesh::StaticClass(), NULL, TEXT("/Game/Megascans/3D_Plants/Amaryllis_sgzkv/SM_Flower3.SM_Flower3")));
		if (SM_Flower)
		{
			Item->SetStaticMesh(SM_Flower);
		}
		break;
	}
	}
}
