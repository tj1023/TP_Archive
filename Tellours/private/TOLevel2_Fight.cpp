// Fill out your copyright notice in the Description page of Project Settings.


#include "TOLevel2_Fight.h"
#include "Components/WidgetComponent.h"
#include "TOEnemySpawner.h"
#include "TOTeleport.h"

// Sets default values
ATOLevel2_Fight::ATOLevel2_Fight()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Statue = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("STATUE"));

	static ConstructorHelpers::FObjectFinder<UStaticMesh> SM_STATUE(TEXT("/Game/AncientTreasures/Meshes/SM_Statue_02a.SM_Statue_02a"));
	if (SM_STATUE.Succeeded())
	{
		Statue->SetStaticMesh(SM_STATUE.Object);
	}

	Statue->SetWorldScale3D(FVector(3.0f));

	InteractionWidget = CreateDefaultSubobject<UWidgetComponent>(TEXT("INTERACTIONWIDGET"));
	InteractionWidget->SetupAttachment(Statue);
	InteractionWidget->SetRelativeLocation(FVector(0, 0, 75));
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
void ATOLevel2_Fight::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ATOLevel2_Fight::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

/*
* 상호작용 UI
*/
void ATOLevel2_Fight::SetInteractionUIVisible(bool NewBool)
{
	InteractionWidget->SetVisibility(NewBool);
}

void ATOLevel2_Fight::StartPhase()
{
	ATOEnemySpawner* EnemySpawner = (ATOEnemySpawner*)GetWorld()->SpawnActor<ATOEnemySpawner>(GetActorLocation(), FRotator::ZeroRotator);
	EnemySpawner->SetSpawnType(EnemyType::MANNEQUIN);
	EnemySpawner->SetNumberOfSpawn(1);
	EnemySpawner->SetSpawnNum(3);
	EnemySpawner->AllKill.AddLambda([this, EnemySpawner]() -> void {
		ABLOG(Warning, TEXT("ED"));

		ATOTeleport* Teleport = (ATOTeleport*)GetWorld()->SpawnActor<ATOTeleport>(Statue->GetRelativeLocation(), FRotator::ZeroRotator);
		Teleport->SetCurrentLevel("Level2");
		Teleport->SetTeleportDestinationLevel("Room");
		Teleport->SetTeleportLocation(FVector(-350.0, -20.0, 155.0));
		Teleport->SetNeedProgress(1);

		EnemySpawner->Destroy();
		});

	Statue->DestroyComponent();
}