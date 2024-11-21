// Fill out your copyright notice in the Description page of Project Settings.


#include "TOCheckPoint.h"
#include "Components/WidgetComponent.h"
#include "TOCharacter.h"

// Sets default values
ATOCheckPoint::ATOCheckPoint()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	CheckPoint = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("CHECKPOINT"));
	CheckPoint->SetRelativeLocation(FVector(0.0f, 0.0f, 0.0f));

	static ConstructorHelpers::FObjectFinder<UStaticMesh> SM_CheckPoint(TEXT("/Game/Tellours/Developer/Texture/CheckPoint/StaticMesh_Lamp.StaticMesh_Lamp"));
	if (SM_CheckPoint.Succeeded())
	{
		CheckPoint->SetStaticMesh(SM_CheckPoint.Object);
	}

	RootComponent = CheckPoint;
	

	RectLightComponent1 = CreateDefaultSubobject<URectLightComponent>(TEXT("RectLightComponent1"));
	RectLightComponent1->SetWorldLocation(FVector(-30.f, 0.f, 170.f));
	RectLightComponent1->SetWorldRotation(FRotator(0.f, 0.f, 0.f));
	RectLightComponent1->SetIntensity(2000.f);
	RectLightComponent1->SetSourceWidth(64.f);
	RectLightComponent1->SetSourceHeight(64.f);
	RectLightComponent1->SetLightColor(FLinearColor(0.0f, 0.01f, 1.0f));
	RectLightComponent1->SetupAttachment(CheckPoint);

	RectLightComponent2 = CreateDefaultSubobject<URectLightComponent>(TEXT("RectLightComponent2"));
	RectLightComponent2->SetWorldLocation(FVector(30.f, 0.f, 170.f));
	RectLightComponent2->SetWorldRotation(FRotator(0.f, 180.f, 0.f));
	RectLightComponent2->SetIntensity(2000.f);
	RectLightComponent2->SetSourceWidth(64.f);
	RectLightComponent2->SetSourceHeight(64.f);
	RectLightComponent2->SetLightColor(FLinearColor(0.0f, 0.01f, 1.0f));
	RectLightComponent2->SetupAttachment(CheckPoint);

	RectLightComponent3 = CreateDefaultSubobject<URectLightComponent>(TEXT("RectLightComponent3"));
	RectLightComponent3->SetWorldLocation(FVector(0.f, 30.f, 170.f));
	RectLightComponent3->SetWorldRotation(FRotator(0.f, -90.f, 0.f));
	RectLightComponent3->SetIntensity(2000.f);
	RectLightComponent3->SetSourceWidth(64.f);
	RectLightComponent3->SetSourceHeight(64.f);
	RectLightComponent3->SetLightColor(FLinearColor(0.0f, 0.01f, 1.0f));
	RectLightComponent3->SetupAttachment(CheckPoint);

	RectLightComponent4 = CreateDefaultSubobject<URectLightComponent>(TEXT("RectLightComponent4"));
	RectLightComponent4->SetWorldLocation(FVector(0.f, -30.f, 170.f));
	RectLightComponent4->SetWorldRotation(FRotator(0.f, 90.f, 0.f));
	RectLightComponent4->SetIntensity(2000.f);
	RectLightComponent4->SetSourceWidth(64.f);
	RectLightComponent4->SetSourceHeight(64.f);
	RectLightComponent4->SetLightColor(FLinearColor(0.0f, 0.01f, 1.0f));
	RectLightComponent4->SetupAttachment(CheckPoint);
	IsSaved = false;

	// 상호작용 UI
	InteractionWidget = CreateDefaultSubobject<UWidgetComponent>(TEXT("INTERACTIONWIDGET"));
	InteractionWidget->SetupAttachment(CheckPoint);
	InteractionWidget->SetRelativeLocation(FVector(0, 0, 240));
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
void ATOCheckPoint::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ATOCheckPoint::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ATOCheckPoint::SavedGame()
{
	RectLightComponent1->SetLightColor(FLinearColor(1.0f, 0.84f, 0.03f));
	RectLightComponent2->SetLightColor(FLinearColor(1.0f, 0.84f, 0.03f));
	RectLightComponent3->SetLightColor(FLinearColor(1.0f, 0.84f, 0.03f));
	RectLightComponent4->SetLightColor(FLinearColor(1.0f, 0.84f, 0.03f));
}

/*
* 상호작용 UI
*/
void ATOCheckPoint::SetInteractionUIVisible(bool NewBool)
{
	InteractionWidget->SetVisibility(NewBool);
}
