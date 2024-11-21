// Fill out your copyright notice in the Description page of Project Settings.


#include "TOChest.h"
#include "TOItem.h"
#include "TOChestSpawner.h"
#include "EngineUtils.h"
#include "TOCharacter.h"
#include "TOCharacterStatComponent.h"
#include "Components/WidgetComponent.h"

// Sets default values
ATOChest::ATOChest()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	Chest = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("CHEST"));
	UStaticMesh* SM_Chest = Cast< UStaticMesh >(StaticLoadObject(UStaticMesh::StaticClass(), NULL, TEXT("/Game/AncientTreasures/Meshes/SM_Chest_01a.SM_Chest_01a")));
	if (SM_Chest)
	{
		Chest->SetStaticMesh(SM_Chest);
	}
	Chest->SetCollisionProfileName(TEXT("BlockAll"));
	Chest->SetSimulatePhysics(true);
	Chest->SetMassOverrideInKg("", 1000);

	// ��ȣ�ۿ� UI
	InteractionWidget = CreateDefaultSubobject<UWidgetComponent>(TEXT("INTERACTIONWIDGET"));
	InteractionWidget->SetupAttachment(Chest);
	InteractionWidget->SetRelativeLocation(FVector(0, 0, 50));
	InteractionWidget->SetWidgetSpace(EWidgetSpace::Screen);
	static ConstructorHelpers::FClassFinder<UUserWidget> UI_Interaction(TEXT("/Game/Tellours/Developer/UI/UI_Interaction.UI_Interaction_C"));
	if (UI_Interaction.Succeeded())
	{
		InteractionWidget->SetWidgetClass(UI_Interaction.Class);
		InteractionWidget->SetDrawSize(FVector2D(50, 40));
	}
	InteractionWidget->SetVisibility(false);

	IsOpened = false;
}

// Called when the game starts or when spawned
void ATOChest::BeginPlay()
{
	Super::BeginPlay();

	if (RequiredKey)
	{
		UStaticMesh* SM_Chest = Cast< UStaticMesh >(StaticLoadObject(UStaticMesh::StaticClass(), NULL, TEXT("/Game/AncientTreasures/Meshes/SM_Chest_02c.SM_Chest_02c")));
		if (SM_Chest)
		{
			Chest->SetStaticMesh(SM_Chest);
		}
	}
}

// Called every frame
void ATOChest::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}



/*
* ���� ����
*/
void ATOChest::ChestOpen(ATOCharacter* Character)
{
	if (IsOpened)
	{
		return;
	}
	IsOpened = true;

	if (!RequiredKey || Character->CharacterStat->GetInventoryItemCount()[0])
	{
		UStaticMesh* SM_Chest = Cast< UStaticMesh >(StaticLoadObject(UStaticMesh::StaticClass(), NULL, TEXT("/Game/AncientTreasures/Meshes/SM_Chest_01b.SM_Chest_01b")));
		if (RequiredKey)
		{
			SM_Chest = Cast< UStaticMesh >(StaticLoadObject(UStaticMesh::StaticClass(), NULL, TEXT("/Game/AncientTreasures/Meshes/SM_Chest_02d.SM_Chest_02d")));
		}
		if (SM_Chest)
		{
			Chest->SetStaticMesh(SM_Chest);
		}

		// ������ ���
		for (int i = 0; i < FMath::RandRange(3, 10); i++)
			GetWorld()->SpawnActor<ATOItem>(GetActorLocation() + FVector::UpVector * 100, FRotator::ZeroRotator)->ItemDrop();

		// ���� ����, �����
		GetWorld()->GetTimerManager().SetTimer(ChestDeadTimeHandle, FTimerDelegate::CreateLambda([&]() {Destroy(); }), 5, false);
		GetWorld()->GetTimerManager().SetTimer(ChestSpawnTimeHandle, FTimerDelegate::CreateUObject(MotherSpawner, &ATOChestSpawner::ChestSpawn), 5, false);
	}
}


/*
* ���� ������ ����
*/
void ATOChest::SetMotherSpawner(ATOChestSpawner* NewSpawner)
{
	MotherSpawner = NewSpawner;
}



/*
* ��ȣ�ۿ� UI
*/
void ATOChest::SetInteractionUIVisible(bool NewBool)
{
	InteractionWidget->SetVisibility(NewBool);
}



bool ATOChest::GetIsOpened()
{
	return IsOpened;
}
