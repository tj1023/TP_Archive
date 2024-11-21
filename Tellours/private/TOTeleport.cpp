// Fill out your copyright notice in the Description page of Project Settings.


#include "TOTeleport.h"
#include "TOCharacter.h"
#include "Kismet/GameplayStatics.h"
#include "Components/WidgetComponent.h"
#include "Engine/LevelStreaming.h"
#include "TOPlayerState.h"

// Sets default values
ATOTeleport::ATOTeleport()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;


	TeleportMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("TeleportMesh"));
	TeleportMesh->SetRelativeLocation(FVector(0.0f, 0.0f, 0.0f));

	// �ӽ� �޽� ����
	static ConstructorHelpers::FObjectFinder<UStaticMesh> SM_CheckPoint(TEXT("/Game/Tellours/Developer/Texture/CheckPoint/StaticMesh_Lamp.StaticMesh_Lamp"));
	if (SM_CheckPoint.Succeeded())
	{
		TeleportMesh->SetStaticMesh(SM_CheckPoint.Object);
	}

	RootComponent = TeleportMesh;

	// Level �⺻ ����.
	LatentActionInfo.UUID = AID_Loading;
	LatentActionInfo.CallbackTarget = this;
	LatentActionInfo.Linkage = LID_Link;
	LatentActionInfo.ExecutionFunction = FName(TEXT("OnStreamLevelLoaded"));

	// �⺻ ����.
	CurrentLevel = "Room";
	TeleportDestinationLevel = "Room";
	TeleportLocation = FVector(FVector::ZeroVector);
	NeedProgress = 1;

	// ��ȣ�ۿ� UI
	InteractionWidget = CreateDefaultSubobject<UWidgetComponent>(TEXT("INTERACTIONWIDGET"));
	InteractionWidget->SetupAttachment(TeleportMesh);
	InteractionWidget->SetRelativeLocation(FVector(0, 0, 240));
	InteractionWidget->SetWidgetSpace(EWidgetSpace::Screen);
	static ConstructorHelpers::FClassFinder<UUserWidget> UI_Interaction(TEXT("/Game/Tellours/Developer/UI/UI_Interaction.UI_Interaction_C"));
	if (UI_Interaction.Succeeded())
	{
		InteractionWidget->SetWidgetClass(UI_Interaction.Class);
		InteractionWidget->SetDrawSize(FVector2D(50, 40));
	}
	InteractionWidget->SetVisibility(false);

	//Light
	SpotLightComponent = CreateDefaultSubobject<USpotLightComponent>(TEXT("SpotLightComponent"));
	SpotLightComponent->SetupAttachment(TeleportMesh);
	SpotLightComponent->SetRelativeLocation(FVector(0.0f, 0.0f, 500.0f));
	SpotLightComponent->SetRelativeRotation(FRotator(-90.0f, 0.0f, 0.0f));
	SpotLightComponent->SetIntensity(100000.f);
	SpotLightComponent->SetOuterConeAngle(20.0f);
	SpotLightComponent->SetLightColor(FLinearColor(0.3f, 0.85f, 1.0f));
	SpotLightComponent->SetCastShadows(false);

	// �ε�ȭ�� Test
	static ConstructorHelpers::FClassFinder<UUserWidget> UI_Loading(TEXT("/Game/Tellours/Developer/UI/UI_Loading.UI_Loading_C"));
	if (UI_Loading.Succeeded())
	{
		TestWidgetClass = UI_Loading.Class;
	}
}

// Called when the game starts or when spawned
void ATOTeleport::BeginPlay()
{
	Super::BeginPlay();
	
	ATOPlayerState* TOPlayerState = Cast<ATOPlayerState>(GetWorld()->GetFirstPlayerController()->GetCharacter()->GetPlayerState());

	// ���� ���α׷������� ������ ���͸� ����.
	if (TOPlayerState->GetProgress() < NeedProgress)
	{
		TeleportMesh->DestroyComponent();
		InteractionWidget->DestroyComponent();
		SpotLightComponent->DestroyComponent();
	}
}

// Called every frame
void ATOTeleport::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ATOTeleport::Teleport()
{
	if (CurrentLevel != FName("NONE") && TeleportDestinationLevel != FName("NONE"))
	{
		// �ε�ȭ�� Test
		TestWidget = CreateWidget<UUserWidget>(GetWorld(), TestWidgetClass);
		TestWidget->AddToViewport();

		UGameplayStatics::LoadStreamLevel(this, TeleportDestinationLevel, true, false, LatentActionInfo);
	}
	else
	{
		ACharacter* Character = UGameplayStatics::GetPlayerCharacter(this, 0);
		Character->SetActorLocation(TeleportLocation);
	}
}

void ATOTeleport::OnStreamLevelLoaded()
{
	TestWidget->RemoveFromViewport();

	ACharacter* Character = UGameplayStatics::GetPlayerCharacter(this, 0);
	Character->SetActorLocation(TeleportLocation);

	FTimerHandle WaitHandle;
	GetWorld()->GetTimerManager().SetTimer(WaitHandle, FTimerDelegate::CreateLambda([&]()
		{
			UGameplayStatics::UnloadStreamLevel(this, CurrentLevel, FLatentActionInfo(), false);
		}), 0.2f, false);
}

/*
* ��ȣ�ۿ� UI
*/
void ATOTeleport::SetInteractionUIVisible(bool NewBool)
{
	InteractionWidget->SetVisibility(NewBool);
}

void ATOTeleport::SetCurrentLevel(FName CurrentLevelValue)
{
	CurrentLevel = CurrentLevelValue;
}

void ATOTeleport::SetTeleportDestinationLevel(FName TeleportDestinationLevelValue)
{
	TeleportDestinationLevel = TeleportDestinationLevelValue;
}

void ATOTeleport::SetTeleportLocation(FVector TeleportLocationValue)
{
	TeleportLocation = TeleportLocationValue;
}

void ATOTeleport::SetNeedProgress(int32 NeedProgressValue)
{
	NeedProgress = NeedProgressValue;
}
