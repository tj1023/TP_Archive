// Fill out your copyright notice in the Description page of Project Settings.


#include "TOFlower.h"
#include "Components/WidgetComponent.h"

// Sets default values
ATOFlower::ATOFlower()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	
	ObjectMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("OBJECT"));
	ObjectMesh->SetRelativeLocation(FVector(0.0f, 0.0f, 0.0f));

	static ConstructorHelpers::FObjectFinder<UStaticMesh> SM_ObJECT(TEXT("/Game/Megascans/3D_Plants/Amaryllis_sgzkv/SM_Flower.SM_Flower"));
	if (SM_ObJECT.Succeeded())
	{
		ObjectMesh->SetStaticMesh(SM_ObJECT.Object);
	}
	ObjectMesh->SetWorldScale3D(FVector(3.0f, 3.0f, 3.0f));
	//ObjectMesh->SetCollisionProfileName(TEXT("Flower"));
	RootComponent = ObjectMesh;

	PointLightArray.Add(CreateDefaultSubobject<UPointLightComponent>(TEXT("Light1")));
	PointLightArray.Add(CreateDefaultSubobject<UPointLightComponent>(TEXT("Light2")));
	PointLightArray.Add(CreateDefaultSubobject<UPointLightComponent>(TEXT("Light3")));
	PointLightArray.Add(CreateDefaultSubobject<UPointLightComponent>(TEXT("Light4")));

	for (int32 index = 0; index < 4; index++)
	{
		
		switch(index)
		{
			case 0:
			{
				PointLightArray[index]->SetWorldLocation(FVector(-50.f, 0.f, 150.f));
				break;
			}
			case 1:
			{
				PointLightArray[index]->SetWorldLocation(FVector(50.f, 0.f, 150.f));
				break;
			}
			case 2:
			{
				PointLightArray[index]->SetWorldLocation(FVector(0.f, 50.f, 150.f));
				break;
			}
			case 3:
			{
				PointLightArray[index]->SetWorldLocation(FVector(0.f, -50.f, 150.f));
				break;
			}
		}
		PointLightArray[index]->SetIntensity(62500.0);
		PointLightArray[index]->SetupAttachment(ObjectMesh);
	}

	// 상호작용 UI
	InteractionWidget = CreateDefaultSubobject<UWidgetComponent>(TEXT("INTERACTIONWIDGET"));
	InteractionWidget->SetupAttachment(ObjectMesh);
	InteractionWidget->SetRelativeLocation(FVector(0, 0, 100));
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
void ATOFlower::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ATOFlower::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}




/*
* 상호작용 UI
*/
void ATOFlower::SetInteractionUIVisible(bool NewBool)
{
	InteractionWidget->SetVisibility(NewBool);
}