// Fill out your copyright notice in the Description page of Project Settings.


#include "Fireplace.h"
#include "Components/WidgetComponent.h"
#include "CapstoneSubsystem.h"

// Sets default values
AFireplace::AFireplace()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MESH"));
	RootComponent = Mesh;
	UStaticMesh* SM_Fireplace = Cast< UStaticMesh >(StaticLoadObject(UStaticMesh::StaticClass(), NULL, TEXT("/Game/SICKA_mansion/StaticMeshes/SM_Fireplace.SM_Fireplace")));
	if (SM_Fireplace) {
		Mesh->SetStaticMesh(SM_Fireplace);
	}

	// 상호작용 UI
	InteractionWidget = CreateDefaultSubobject<UWidgetComponent>(TEXT("INTERACTIONWIDGET"));
	InteractionWidget->SetupAttachment(Mesh);
	InteractionWidget->SetRelativeLocation(FVector(0, 0, 0));
	InteractionWidget->SetWidgetSpace(EWidgetSpace::Screen);
	static ConstructorHelpers::FClassFinder<UUserWidget> UI_Interaction(TEXT("/Game/UI/UI_Interaction.UI_Interaction_C"));
	if (UI_Interaction.Succeeded())
	{
		InteractionWidget->SetWidgetClass(UI_Interaction.Class);
		InteractionWidget->SetDrawSize(FVector2D(50, 40));
	}
	InteractionWidget->SetVisibility(false);
}

// Called when the game starts or when spawned
void AFireplace::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AFireplace::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AFireplace::Interaction()
{
	UCapstoneSubsystem* CapstoneSubsystem = GetWorld()->GetGameInstance()->GetSubsystem<UCapstoneSubsystem>();
	CapstoneSubsystem->CheckIsCleared();
}

void AFireplace::SetInteractionUIVisible(bool NewBool)
{
	InteractionWidget->SetVisibility(NewBool);
}
