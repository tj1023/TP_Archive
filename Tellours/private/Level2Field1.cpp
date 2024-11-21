// Fill out your copyright notice in the Description page of Project Settings.


#include "Level2Field1.h"
#include "TOEnemySpawner.h"
#include "Components/WidgetComponent.h"

// Sets default values
ALevel2Field1::ALevel2Field1()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	TV = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("TV"));
	UStaticMesh* SM_TV = Cast<UStaticMesh>(StaticLoadObject(UStaticMesh::StaticClass(), NULL, TEXT("/Game/Megascans/3D_Assets/Asset_ClearPoint/SM_ClearPoint.SM_ClearPoint")));
	if (SM_TV)
	{
		TV->SetStaticMesh(SM_TV);
	}

	// 상호작용 UI
	InteractionWidget = CreateDefaultSubobject<UWidgetComponent>(TEXT("INTERACTIONWIDGET"));
	InteractionWidget->SetupAttachment(TV);
	InteractionWidget->SetRelativeLocation(FVector(0, 0, 50));
	InteractionWidget->SetWidgetSpace(EWidgetSpace::Screen);
	static ConstructorHelpers::FClassFinder<UUserWidget> UI_Interaction(TEXT("/Game/Tellours/Developer/UI/UI_Interaction.UI_Interaction_C"));
	if (UI_Interaction.Succeeded())
	{
		InteractionWidget->SetWidgetClass(UI_Interaction.Class);
		InteractionWidget->SetDrawSize(FVector2D(50, 40));
	}
	InteractionWidget->SetVisibility(false);

	Phase1End = false;
	Phase2End = false;
	Phase3End = false;
}

// Called when the game starts or when spawned
void ALevel2Field1::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ALevel2Field1::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}



/*
* 상호작용 UI
*/
void ALevel2Field1::SetInteractionUIVisible(bool NewBool)
{
	InteractionWidget->SetVisibility(NewBool);
}



bool ALevel2Field1::GetPhase1End()
{
	return Phase1End;
}

bool ALevel2Field1::GetPhase2End()
{
	return Phase2End;
}

bool ALevel2Field1::GetPhase3End()
{
	return Phase3End;
}




/*
* 퀘스트
*/
void ALevel2Field1::Phase1()
{
	ATOEnemySpawner* EnemySpawner = (ATOEnemySpawner*)GetWorld()->SpawnActor<ATOEnemySpawner>(GetActorLocation(), FRotator::ZeroRotator);
	EnemySpawner->SetSpawnType(EnemyType::MANNEQUIN);
	EnemySpawner->SetNumberOfSpawn(1);
	EnemySpawner->SetSpawnNum(1);
	EnemySpawner->AllKill.AddLambda([this, EnemySpawner]() -> void {
		Phase1End = true;
		Phase2();
		EnemySpawner->Destroy();
		});
}

void ALevel2Field1::Phase2()
{
	ATOEnemySpawner* EnemySpawner = (ATOEnemySpawner*)GetWorld()->SpawnActor<ATOEnemySpawner>(GetActorLocation(), FRotator::ZeroRotator);
	EnemySpawner->SetSpawnType(EnemyType::MANNEQUIN);
	EnemySpawner->SetNumberOfSpawn(1);
	EnemySpawner->SetSpawnNum(1);
	EnemySpawner->AllKill.AddLambda([this, EnemySpawner]() -> void {
		Phase2End = true;
		Phase3();
		EnemySpawner->Destroy();
		});
}

void ALevel2Field1::Phase3()
{
	ATOEnemySpawner* EnemySpawner = (ATOEnemySpawner*)GetWorld()->SpawnActor<ATOEnemySpawner>(GetActorLocation(), FRotator::ZeroRotator);
	EnemySpawner->SetSpawnType(EnemyType::MANNEQUIN);
	EnemySpawner->SetNumberOfSpawn(1);
	EnemySpawner->SetSpawnNum(1);
	EnemySpawner->AllKill.AddLambda([this, EnemySpawner]() -> void {
		Phase3End = true;
		EnemySpawner->Destroy();
		Destroy();
		});
}
