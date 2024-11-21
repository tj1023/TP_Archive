// Fill out your copyright notice in the Description page of Project Settings.


#include "TOClearPoint.h"
#include "TOCharacter.h"
#include "TOCharacterStatComponent.h"
#include "Components/WidgetComponent.h"

// Sets default values
ATOClearPoint::ATOClearPoint()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	ClearPoint = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("CLEAR"));
	UStaticMesh* SM_ClearPoint = Cast<UStaticMesh>(StaticLoadObject(UStaticMesh::StaticClass(), NULL, TEXT("/Game/Megascans/3D_Assets/Asset_ClearPoint/SM_ClearPoint.SM_ClearPoint")));
	if (SM_ClearPoint)
	{
		ClearPoint->SetStaticMesh(SM_ClearPoint);
	}

	// 상호작용 UI
	InteractionWidget = CreateDefaultSubobject<UWidgetComponent>(TEXT("INTERACTIONWIDGET"));
	InteractionWidget->SetupAttachment(ClearPoint);
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
void ATOClearPoint::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ATOClearPoint::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}


/*
* 상호작용 UI
*/
void ATOClearPoint::SetInteractionUIVisible(bool NewBool)
{
	InteractionWidget->SetVisibility(NewBool);
}

void ATOClearPoint::CheckPointCondition()
{
	auto TOCharacter = Cast<ATOCharacter>(GetWorld()->GetFirstPlayerController()->GetPawn());
	int32 Progress = TOCharacter->CharacterStat->GetProgress();
	InventoryItem = TOCharacter->CharacterStat->GetInventoryItemCount();

	// 테마1 클리어 조건 체크
	if (Progress == 1)
	{
		if (InventoryItem[0] && InventoryItem[2] && InventoryItem[3]) {
			ABLOG(Warning, TEXT("Progress + 1"));
			TOCharacter->CharacterStat->SetProgress(Progress + 1);
		}
		else
			ABLOG(Warning, TEXT("Not Clear"));
	}
	
}