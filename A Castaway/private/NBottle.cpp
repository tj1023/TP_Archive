// Fill out your copyright notice in the Description page of Project Settings.


#include "NBottle.h"
#include "NCharacter.h"
#include "NCharacterStatComponent.h"

// Sets default values
ANBottle::ANBottle()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	BottleMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshComponent"));
	SetRootComponent(BottleMesh);

	static ConstructorHelpers::FObjectFinder<UStaticMesh> MeshAsset_1(TEXT("/Game/Assets/botttle/1/SM_bottle1.SM_bottle1"));
	if (MeshAsset_1.Succeeded())
	{
		Bottle_1 = MeshAsset_1.Object;
	}

	static ConstructorHelpers::FObjectFinder<UStaticMesh> MeshAsset_2(TEXT("/Game/Assets/botttle/2/SM_bottle2.SM_bottle2"));
	if (MeshAsset_2.Succeeded())
	{
		Bottle_2 = MeshAsset_2.Object;
	}

	static ConstructorHelpers::FObjectFinder<UStaticMesh> MeshAsset_3(TEXT("/Game/Assets/botttle/3/SM_bottle3.SM_bottle3"));
	if (MeshAsset_3.Succeeded())
	{
		Bottle_3 = MeshAsset_3.Object;
	}

	static ConstructorHelpers::FObjectFinder<UStaticMesh> MeshAsset_4(TEXT("/Game/Assets/botttle/4/SM_bottle4.SM_bottle4"));
	if (MeshAsset_4.Succeeded())
	{
		Bottle_4 = MeshAsset_4.Object;
	}

	static ConstructorHelpers::FObjectFinder<UStaticMesh> MeshAsset_5(TEXT("/Game/Assets/botttle/1/SM_bottle1.SM_bottle1"));
	if (MeshAsset_5.Succeeded())
	{
		Bottle_5 = MeshAsset_5.Object;
	}

	static ConstructorHelpers::FObjectFinder<UStaticMesh> MeshAsset_6(TEXT("/Game/Assets/botttle/2/SM_bottle2.SM_bottle2"));
	if (MeshAsset_6.Succeeded())
	{
		Bottle_6 = MeshAsset_6.Object;
	}

	static ConstructorHelpers::FObjectFinder<UStaticMesh> MeshAsset_7(TEXT("/Game/Assets/botttle/3/SM_bottle3.SM_bottle3"));
	if (MeshAsset_7.Succeeded())
	{
		Bottle_7 = MeshAsset_7.Object;
	}

	static ConstructorHelpers::FObjectFinder<UStaticMesh> MeshAsset_8(TEXT("/Game/Assets/botttle/4/SM_bottle4.SM_bottle4"));
	if (MeshAsset_8.Succeeded())
	{
		Bottle_8 = MeshAsset_8.Object;
	}

	BottleMesh->SetWorldScale3D(FVector(2.5f, 2.5f, 2.5f));

	IsMoving = false;
	RunningTime = 0.0f;
}

// Called when the game starts or when spawned
void ANBottle::BeginPlay()
{
	Super::BeginPlay();

	StartLocation = GetActorLocation();
}

// Called every frame
void ANBottle::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	// 병 움직임
	float Distance = FVector::Distance(StartLocation, FVector(GetActorLocation().X, GetActorLocation().Y, 0));

	if (IsMoving && !IsGoBack)
	{
		if (Distance > 1200.0f)
			IsMoving = false;
		else
		{
			NewLocation = GetActorLocation() + (GetActorForwardVector() * 240.0f * DeltaTime);
			RunningTime += DeltaTime;
		}
	}
	else if (IsGoBack)
	{
		if (Distance < 100.0f)
			Destroy();
		else
			NewLocation = GetActorLocation() + (-GetActorForwardVector() * 240.0f * DeltaTime);
	}
	RunningTime += DeltaTime;
	if(!IsGoDown)
		NewLocation.Z = 30.0f * FMath::Sin(1.5 * RunningTime);
	else
		NewLocation.Z = GetActorLocation().Z - 100.0f * DeltaTime;
	SetActorLocation(NewLocation);

	if (GetActorLocation().Z < -200) Destroy();
}

void ANBottle::SetValue(int32 ExceptNum)
{
	// **** 이 것을 이용하여 랜덤하게 지문을 정하기
	while (true)
	{
		value = FMath::RandRange(2, SCRIPT_LEN - 1);

		if (value != ExceptNum)
		{
			break;
		}
	}

	// Tutorial
	if (ExceptNum == 0)
	{
		value = 0;
	}

	// 스크립트 value 고정
	if (FixedValue != 0) value = FixedValue;

	auto NCharacter = Cast<ANCharacter>(GetWorld()->GetFirstPlayerController()->GetPawn());

	// 지문이 정해지면 스크립트 설정
	if (value == 0)
	{
		NLOG(Warning, TEXT("Tutorial Script is Selected"));
		BottleMesh->SetStaticMesh(Bottle_1);
	}
	else if (value == 1)
	{
		NLOG(Warning, TEXT("Main Script is Selected"));
		BottleMesh->SetStaticMesh(Bottle_1);
	}
	else
	{
		if (value % 7 == 2)
		{
			NLOG(Warning, TEXT("Sub_%d is Selected"), value - 2);
			BottleMesh->SetStaticMesh(Bottle_2);
		}
		else if (value % 7 == 3)
		{
			NLOG(Warning, TEXT("Sub_%d is Selected"), value - 2);
			BottleMesh->SetStaticMesh(Bottle_3);
		}
		else if (value % 7 == 4)
		{
			NLOG(Warning, TEXT("Sub_%d is Selected"), value - 2);
			BottleMesh->SetStaticMesh(Bottle_4);
		}
		else if (value % 7 == 5)
		{
			NLOG(Warning, TEXT("Sub_%d is Selected"), value - 2);
			BottleMesh->SetStaticMesh(Bottle_5);
		}
		else if (value % 7 == 6)
		{
			NLOG(Warning, TEXT("Sub_%d is Selected"), value - 2);
			BottleMesh->SetStaticMesh(Bottle_6);
		}
		else if (value % 7 == 0)
		{
			NLOG(Warning, TEXT("Sub_%d is Selected"), value - 2);
			BottleMesh->SetStaticMesh(Bottle_7);
		}
		else
		{
			NLOG(Warning, TEXT("Sub_%d is Selected"), value - 2);
			BottleMesh->SetStaticMesh(Bottle_8);
		}
	}

	FixedValue = 0;
}

void ANBottle::SetStart()
{
	IsMoving = true;
}

void ANBottle::RemoveBottle()
{
	this->Destroy();
}

int32 ANBottle::GetValue()
{
	return value;
}

void ANBottle::GoBack()
{
	IsGoBack = true;
}

void ANBottle::GoDown()
{
	IsGoDown = true;
}

void ANBottle::FixValue(int32 n)
{
	FixedValue = n;
}