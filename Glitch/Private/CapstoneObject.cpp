// Fill out your copyright notice in the Description page of Project Settings.


#include "CapstoneObject.h"
#include "Components/WidgetComponent.h"
#include <cstdlib>
#include <ctime>

#include "CapstoneController.h"
#include "CapstoneCharacter.h"


// Sets default values
ACapstoneObject::ACapstoneObject()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MESH"));
	UStaticMesh* SM_Object = Cast< UStaticMesh >(StaticLoadObject(UStaticMesh::StaticClass(), NULL, TEXT("/Game/Geometry/Meshes/1M_Cube.1M_Cube")));
	if (SM_Object) {
		Mesh->SetStaticMesh(SM_Object);
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

	this->Tags.Add("CapstonObject");
	ApparitionMode = false;

	MaxForm = 7;
	TypeName = ERoomType::MAINROOM;
}

// Called when the game starts or when spawned
void ACapstoneObject::BeginPlay()
{
	Super::BeginPlay();

	RandForm();
}

// Called every frame
void ACapstoneObject::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ACapstoneObject::Interaction()
{
	HUDWidget = Cast<UCapstoneHUDWidget>(Cast<ACapstoneController>(UGameplayStatics::GetPlayerController(GetWorld(), 0))->GetHUDWidget());

	// ApparitionMode 확인 후 변경
	if (ApparitionMode)
	{
		//// 0 번은 HummanForm의 기본 상태로 사용됨.
		//ApparitionForm = (ApparitionForm + 1) % MaxForm;
		//if (ApparitionForm == 0)
		//	ApparitionForm++;
		//SetApparitionForm(ApparitionForm);
		//
		//if(IsValid(HUDWidget))
		//	HUDWidget->ShowDialog(FString("Change Object State"));
	}
	else
	{
		HumanForm = (HumanForm + 1) % MaxForm;
		if (HumanForm == 0)
			HumanForm++; 
		SetHumanForm(HumanForm);
		

		if (IsValid(HUDWidget))
			HUDWidget->ShowDialog(FString("Change Object State"));
	}

}

void ACapstoneObject::SetInteractionUIVisible(bool NewBool)
{
	InteractionWidget->SetVisibility(NewBool);
}

void ACapstoneObject::RandForm()
{
	HumanForm = FMath::RandRange(1, MaxForm - 1);
	ApparitionForm = 0;
	Key = GetApparitionKey();

	SetHumanForm(HumanForm);
	SetApparitionForm(ApparitionForm);
}

void ACapstoneObject::SetApparitionMode(bool Mode)
{
	ApparitionMode = Mode;
}

int32 ACapstoneObject::GetHumanForm()
{
	return HumanForm;
}

int32 ACapstoneObject::GetApparitionForm()
{
	return ApparitionForm;
}

int32 ACapstoneObject::GetKey()
{
	return Key;
}