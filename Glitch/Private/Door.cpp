// Fill out your copyright notice in the Description page of Project Settings.


#include "Door.h"
#include "Components/WidgetComponent.h"
#include "CapstoneCharacter.h"
#include "CapstoneSubsystem.h"

// Sets default values
ADoor::ADoor()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	MeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshComponent"));
	RootComponent = MeshComponent;

	static ConstructorHelpers::FObjectFinder<UStaticMesh> Door(TEXT("/Game/SICKA_mansion/Rooms/SM_Door.SM_Door"));

	if (Door.Succeeded())
	{
		MeshComponent->SetStaticMesh(Door.Object);
	}

	// 상호작용 UI
	InteractionWidget = CreateDefaultSubobject<UWidgetComponent>(TEXT("INTERACTIONWIDGET"));
	InteractionWidget->SetupAttachment(MeshComponent);
	InteractionWidget->SetRelativeLocation(FVector(-80.0f, -20.0f, 200.0f));
	InteractionWidget->SetWidgetSpace(EWidgetSpace::Screen);
	static ConstructorHelpers::FClassFinder<UUserWidget> UI_Interaction(TEXT("/Game/UI/UI_Interaction.UI_Interaction_C"));
	if (UI_Interaction.Succeeded())
	{
		InteractionWidget->SetWidgetClass(UI_Interaction.Class);
		InteractionWidget->SetDrawSize(FVector2D(50, 40));
	}
	InteractionWidget->SetVisibility(false);

	// true일때 문이 열림
	CanOpenDoor = true;
	IsOpened = false;
}

// Called when the game starts or when spawned
void ADoor::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void ADoor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ADoor::SetInteractionUIVisible(bool NewBool)
{
	InteractionWidget->SetVisibility(NewBool);
}

void ADoor::Interaction()
{
	if (CanOpenDoor)
	{
		if (!IsOpened) {
			OpenDoor();
			IsOpened = true;
		}
		else {
			CloseDoor();
			IsOpened = false;
		}
	}
	else
	{
		UCapstoneSubsystem* CapstoneSubsystem = GetWorld()->GetGameInstance()->GetSubsystem<UCapstoneSubsystem>();
		ADoor* TPDoor = CapstoneSubsystem->GetTPDoor();
		if (TPDoor != nullptr) {
			auto Character = Cast<ACapstoneCharacter>(GetWorld()->GetFirstPlayerController()->GetPawn());
			FVector DoorOffset = FVector(81.5, -11, 0);
			FVector InteractionDoorLoc = GetActorLocation() + DoorOffset;
			FVector TPDoorLoc = TPDoor->GetActorLocation() - DoorOffset;
			FVector CharacterToDoor = InteractionDoorLoc - Character->GetActorLocation();
			Character->SetActorLocation(Character->GetActorLocation() + TPDoorLoc - InteractionDoorLoc
				+ FVector(CharacterToDoor.X, CharacterToDoor.Y, 0) * 2);
			Character->GetController()->SetControlRotation(Character->GetControlRotation() + FRotator(0, 180, 0));
			TPDoor->OpenDoor();
		}
	}
}

bool ADoor::GetCanOpenDoor()
{
	return CanOpenDoor;
}
