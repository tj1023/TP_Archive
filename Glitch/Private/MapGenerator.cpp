// Fill out your copyright notice in the Description page of Project Settings.


#include "MapGenerator.h"
#include "MainRoom.h"
#include "Room.h"
#include "Corrider.h"
#include "EngineUtils.h"
#include "CapstoneGhost.h"
#include "CapstoneSubsystem.h"

// Sets default values
AMapGenerator::AMapGenerator()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	MeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshComponent"));
	RootComponent = MeshComponent;

	mapScale = 3;
	ChunkDistance = 2000;
}

// Called when the game starts or when spawned
void AMapGenerator::BeginPlay()
{
	Super::BeginPlay();

	GeneratingMap();
}

// Called every frame
void AMapGenerator::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AMapGenerator::GeneratingMap()
{
	FActorSpawnParameters tParams;

	// ���� �� ����
	AMainRoom* Main = GetWorld()->SpawnActor<AMainRoom>(AMainRoom::StaticClass(), FVector(GetActorLocation().X, GetActorLocation().Y + (ChunkDistance / 2), GetActorLocation().Z), FRotator::ZeroRotator, tParams);

	ACorrider* upCorrider = GetWorld()->SpawnActor<ACorrider>(ACorrider::StaticClass(), FVector(GetActorLocation().X + ChunkDistance, GetActorLocation().Y, GetActorLocation().Z), FRotator::ZeroRotator, tParams);
	ACorrider* rightCorrider = GetWorld()->SpawnActor<ACorrider>(ACorrider::StaticClass(), FVector(GetActorLocation().X, GetActorLocation().Y + (2 * ChunkDistance), GetActorLocation().Z), FRotator::ZeroRotator, tParams);
	ACorrider* leftCorrider = GetWorld()->SpawnActor<ACorrider>(ACorrider::StaticClass(), FVector(GetActorLocation().X, GetActorLocation().Y - ChunkDistance, GetActorLocation().Z), FRotator::ZeroRotator, tParams);

	upCorrider->SetDoor(FString("down"), true);
	rightCorrider->SetDoor(FString("left"), true);
	leftCorrider->SetDoor(FString("right"), true);

	AChunk* root_1 = upCorrider;
	AChunk* root_2 = rightCorrider;
	AChunk* root_3 = leftCorrider;

	//root 1
	for (int i = 0; i < 10; i++)
	{
		root_1 = GeneratingChunk(root_1, false);

		if (root_1 == nullptr)
			break;
	}

	//root 2
	for (int i = 0; i < 10; i++)
	{
		root_2 = GeneratingChunk(root_2, false);

		if (root_2 == nullptr)
			break;
	}

	//root 3
	for (int i = 0; i < 10; i++)
	{
		root_3 = GeneratingChunk(root_3, false);

		if (root_3 == nullptr)
			break;
	}

	if (root_1 != nullptr)
		root_1 = GeneratingChunk(root_1, true);
	if (root_2 != nullptr)
		root_2 = GeneratingChunk(root_2, true);
	if (root_3 != nullptr)
		root_3 = GeneratingChunk(root_3, true);

	for (TActorIterator<AChunk> Chunk(GetWorld()); Chunk; ++Chunk)
	{
		if (Chunk->ActorHasTag("way"))
		{
			Chunk->SpawnTypeActor();
		}
	}

	Main->SetActorLocation(FVector::ZeroVector);

	// �� ���� ����
	TArray<ACorrider*> Corriders;
	TArray<FVector> CorridersLoc;
	const int SpawnNum = 5;
	int CorriderNum[SpawnNum];


	for (TActorIterator<ACorrider> Corrider(GetWorld()); Corrider; ++Corrider) {
		Corriders.Emplace(*Corrider);
		CorridersLoc.Emplace(Corrider->GetActorLocation());
	}

	UCapstoneSubsystem* CapstoneSubsystem = GetWorld()->GetGameInstance()->GetSubsystem<UCapstoneSubsystem>();
	CapstoneSubsystem->SetCorLoc(CorridersLoc);

	int i = 0;
	UClass* GeneratedBP = Cast<UClass>(StaticLoadObject(UClass::StaticClass(), NULL, TEXT("/Game/Assets/Ghost/source/BP_Ghost.BP_Ghost_C")));

	while (i < 5) {
		int NewNum = FMath::RandRange(0, Corriders.Num() - 1);
		bool IsIn = false;
		for (int j = 0; j < i; j++)
			if (CorriderNum[j] == NewNum) IsIn = true;
		if (!IsIn) {
			ACorrider* Corrider = Corriders[NewNum];
			GetWorld()->SpawnActor<AActor>(GeneratedBP, Corrider->GetActorLocation() + FVector(0, 0, 50), FRotator::ZeroRotator);
			CorriderNum[i] = NewNum;
			i++;
		}
	}

	for (TActorIterator<AChunk> Chunk(GetWorld()); Chunk; ++Chunk)
		Chunk->Destroy();
}

AChunk* AMapGenerator::SpawnRoom(FVector location, FString doorLocation)
{
	FActorSpawnParameters tParams;
	ARoom* Room = GetWorld()->SpawnActor<ARoom>(ARoom::StaticClass(), location, FRotator::ZeroRotator, tParams);
	Room->SetDoor(doorLocation, true);

	return Room;
}

AChunk* AMapGenerator::SpawnCorrider(FVector location, FString doorLocation)
{
	FActorSpawnParameters tParams;
	ACorrider* Corrider = GetWorld()->SpawnActor<ACorrider>(ACorrider::StaticClass(), location, FRotator::ZeroRotator, tParams);
	Corrider->SetDoor(doorLocation, true);

	return Corrider;
}

AChunk* AMapGenerator::GeneratingChunk(AChunk* CurrentChunk, bool End)
{
	FCollisionQueryParams QueryParams;
	QueryParams.AddIgnoredActor(CurrentChunk);

	AChunk* returnActor = CurrentChunk;

	if (End)
	{
		FVector loc = CurrentChunk->GetActorLocation();
		CurrentChunk->Destroy();

		if (CurrentChunk->GetDoor("up"))
			SpawnRoom(loc, "up");
		else if (CurrentChunk->GetDoor("right"))
			SpawnRoom(loc, "right");
		else if (CurrentChunk->GetDoor("down"))
			SpawnRoom(loc, "down");
		else
			SpawnRoom(loc, "left");

		return nullptr;
	}

	bool upHitSuccess;
	bool rightHitSuccess;
	bool downHitSuccess;
	bool leftHitSuccess;
	FHitResult upHitResult;
	FHitResult rightHitResult;
	FHitResult downHitResult;
	FHitResult leftHitResult;

	upHitSuccess = GetWorld()->LineTraceSingleByChannel(
		upHitResult,
		CurrentChunk->GetActorLocation(),
		FVector(CurrentChunk->GetActorLocation().X + ChunkDistance, CurrentChunk->GetActorLocation().Y, CurrentChunk->GetActorLocation().Z),
		ECC_Visibility,
		QueryParams
	);

	rightHitSuccess = GetWorld()->LineTraceSingleByChannel(
		rightHitResult,
		CurrentChunk->GetActorLocation(),
		FVector(CurrentChunk->GetActorLocation().X, CurrentChunk->GetActorLocation().Y + ChunkDistance, CurrentChunk->GetActorLocation().Z),
		ECC_Visibility,
		QueryParams
	);

	downHitSuccess = GetWorld()->LineTraceSingleByChannel(
		downHitResult,
		CurrentChunk->GetActorLocation(),
		FVector(CurrentChunk->GetActorLocation().X - ChunkDistance, CurrentChunk->GetActorLocation().Y, CurrentChunk->GetActorLocation().Z),
		ECC_Visibility,
		QueryParams
	);

	leftHitSuccess = GetWorld()->LineTraceSingleByChannel(
		leftHitResult,
		CurrentChunk->GetActorLocation(),
		FVector(CurrentChunk->GetActorLocation().X, CurrentChunk->GetActorLocation().Y - ChunkDistance, CurrentChunk->GetActorLocation().Z),
		ECC_Visibility,
		QueryParams
	);

	/*
	* ���� �����ִ� ���
	*/
	if (upHitSuccess && !rightHitSuccess && !downHitSuccess && !leftHitSuccess)
	{
		// ���� ������ų�� ����
		if (FMath::RandRange(0, 1) == 0)		// ���� ����
		{
			/*
			* ���� ���� ��Ų ��, ������ �ϳ� �� ������ ������ ����.
			* Door�� �ִ� �κе� �Բ� �������ش�.
			*/
			int8 roomLocation;

			switch (FMath::RandRange(0, 2))
			{
				// RIGHT
			case 0:
				SpawnRoom(FVector(CurrentChunk->GetActorLocation().X, CurrentChunk->GetActorLocation().Y + ChunkDistance, CurrentChunk->GetActorLocation().Z), FString("left"));
				roomLocation = 1;
				CurrentChunk->SetDoor(FString("right"), true);
				break;
				// DOWN
			case 1:
				SpawnRoom(FVector(CurrentChunk->GetActorLocation().X - ChunkDistance, CurrentChunk->GetActorLocation().Y, CurrentChunk->GetActorLocation().Z), FString("up"));
				roomLocation = 2;
				CurrentChunk->SetDoor(FString("down"), true);
				break;
				// LEFT
			case 2:
				SpawnRoom(FVector(CurrentChunk->GetActorLocation().X, CurrentChunk->GetActorLocation().Y - ChunkDistance, CurrentChunk->GetActorLocation().Z), FString("right"));
				roomLocation = 3;
				CurrentChunk->SetDoor(FString("left"), true);
				break;
			default:
				break;
			}

			int8 checkCanGo = FMath::RandRange(0, 2);
			TArray<int8> roomNumber = { 1, 2, 3 };

			while (roomNumber[checkCanGo] == roomLocation)
				checkCanGo = FMath::RandRange(0, 2);

			switch (checkCanGo)
			{
				// RIGHT
			case 0:
				returnActor = SpawnCorrider(FVector(CurrentChunk->GetActorLocation().X, CurrentChunk->GetActorLocation().Y + ChunkDistance, CurrentChunk->GetActorLocation().Z), FString("left"));
				CurrentChunk->SetDoor(FString("right"), true);
				break;
				// DOWN
			case 1:
				returnActor = SpawnCorrider(FVector(CurrentChunk->GetActorLocation().X - ChunkDistance, CurrentChunk->GetActorLocation().Y, CurrentChunk->GetActorLocation().Z), FString("up"));
				CurrentChunk->SetDoor(FString("down"), true);
				break;
				// LEFT
			case 2:
				returnActor = SpawnCorrider(FVector(CurrentChunk->GetActorLocation().X, CurrentChunk->GetActorLocation().Y - ChunkDistance, CurrentChunk->GetActorLocation().Z), FString("right"));
				CurrentChunk->SetDoor(FString("left"), true);
				break;
			default:
				break;
			}

		}
		else									// ������ ����
		{
			switch (FMath::RandRange(0, 2))
			{
				// RIGHT
			case 0:
				returnActor = SpawnCorrider(FVector(CurrentChunk->GetActorLocation().X, CurrentChunk->GetActorLocation().Y + ChunkDistance, CurrentChunk->GetActorLocation().Z), FString("left"));
				CurrentChunk->SetDoor(FString("right"), true);
				break;
				// DOWN
			case 1:
				returnActor = SpawnCorrider(FVector(CurrentChunk->GetActorLocation().X - ChunkDistance, CurrentChunk->GetActorLocation().Y, CurrentChunk->GetActorLocation().Z), FString("up"));
				CurrentChunk->SetDoor(FString("down"), true);
				break;
				// LEFT
			case 2:
				returnActor = SpawnCorrider(FVector(CurrentChunk->GetActorLocation().X, CurrentChunk->GetActorLocation().Y - ChunkDistance, CurrentChunk->GetActorLocation().Z), FString("right"));
				CurrentChunk->SetDoor(FString("left"), true);
				break;
			default:
				break;
			}
		}
	}

	/*
	* �������� �����ִ� ���
	*/
	else if (!upHitSuccess && rightHitSuccess && !downHitSuccess && !leftHitSuccess)
	{
		// ���� ������ų�� ����
		if (FMath::RandRange(0, 1) == 0)		// ���� ����
		{
			/*
			* ���� ���� ��Ų ��, ������ �ϳ� �� ������ ������ ����.
			* Door�� �ִ� �κе� �Բ� �������ش�.
			*/
			int8 roomLocation;

			switch (FMath::RandRange(0, 2))
			{
				// UP
			case 0:
				SpawnRoom(FVector(CurrentChunk->GetActorLocation().X + ChunkDistance, CurrentChunk->GetActorLocation().Y, CurrentChunk->GetActorLocation().Z), FString("down"));
				roomLocation = 0;
				CurrentChunk->SetDoor(FString("up"), true);
				break;
				// DOWN
			case 1:
				SpawnRoom(FVector(CurrentChunk->GetActorLocation().X - ChunkDistance, CurrentChunk->GetActorLocation().Y, CurrentChunk->GetActorLocation().Z), FString("up"));
				roomLocation = 2;
				CurrentChunk->SetDoor(FString("down"), true);
				break;
				// LEFT
			case 2:
				SpawnRoom(FVector(CurrentChunk->GetActorLocation().X, CurrentChunk->GetActorLocation().Y - ChunkDistance, CurrentChunk->GetActorLocation().Z), FString("right"));
				roomLocation = 3;
				CurrentChunk->SetDoor(FString("left"), true);
				break;
			default:
				break;
			}

			// ���� �ձ� or �� �Ѱ��� ��
			// if ���� ���� FMath::RandRange(0, 1) == 0
			if (true)
			{
				int8 checkCanGo = FMath::RandRange(0, 2);
				TArray<int8> roomNumber = { 0, 2, 3 };

				while (roomNumber[checkCanGo] == roomLocation)
					checkCanGo = FMath::RandRange(0, 2);

				switch (checkCanGo)
				{
					// UP
				case 0:
					returnActor = SpawnCorrider(FVector(CurrentChunk->GetActorLocation().X + ChunkDistance, CurrentChunk->GetActorLocation().Y, CurrentChunk->GetActorLocation().Z), FString("down"));
					CurrentChunk->SetDoor(FString("up"), true);
					break;
					// DOWN
				case 1:
					returnActor = SpawnCorrider(FVector(CurrentChunk->GetActorLocation().X - ChunkDistance, CurrentChunk->GetActorLocation().Y, CurrentChunk->GetActorLocation().Z), FString("up"));
					CurrentChunk->SetDoor(FString("down"), true);
					break;
					// LEFT
				case 2:
					returnActor = SpawnCorrider(FVector(CurrentChunk->GetActorLocation().X, CurrentChunk->GetActorLocation().Y - ChunkDistance, CurrentChunk->GetActorLocation().Z), FString("right"));
					CurrentChunk->SetDoor(FString("left"), true);
					break;
				default:
					break;
				}
			}
			else
				return nullptr;

		}
		else									// ������ ����
		{
			switch (FMath::RandRange(0, 2))
			{
				// UP
			case 0:
				returnActor = SpawnCorrider(FVector(CurrentChunk->GetActorLocation().X + ChunkDistance, CurrentChunk->GetActorLocation().Y, CurrentChunk->GetActorLocation().Z), FString("down"));
				CurrentChunk->SetDoor(FString("up"), true);
				break;
				// DOWN
			case 1:
				returnActor = SpawnCorrider(FVector(CurrentChunk->GetActorLocation().X - ChunkDistance, CurrentChunk->GetActorLocation().Y, CurrentChunk->GetActorLocation().Z), FString("up"));
				CurrentChunk->SetDoor(FString("down"), true);
				break;
				// LEFT
			case 2:
				returnActor = SpawnCorrider(FVector(CurrentChunk->GetActorLocation().X, CurrentChunk->GetActorLocation().Y - ChunkDistance, CurrentChunk->GetActorLocation().Z), FString("right"));
				CurrentChunk->SetDoor(FString("left"), true);
				break;
			default:
				break;
			}
		}
	}

	/*
	* �Ʒ��� �����ִ� ���
	*/
	else if (!upHitSuccess && !rightHitSuccess && downHitSuccess && !leftHitSuccess)
	{
		// ���� ������ų�� ����
		if (FMath::RandRange(0, 1) == 0)		// ���� ����
		{
			/*
			* ���� ���� ��Ų ��, ������ �ϳ� �� ������ ������ ����.
			* Door�� �ִ� �κе� �Բ� �������ش�.
			*/
			int8 roomLocation;

			switch (FMath::RandRange(0, 2))
			{
				// UP
			case 0:
				SpawnRoom(FVector(CurrentChunk->GetActorLocation().X + ChunkDistance, CurrentChunk->GetActorLocation().Y, CurrentChunk->GetActorLocation().Z), FString("down"));
				roomLocation = 0;
				CurrentChunk->SetDoor(FString("up"), true);
				break;
				// RIGHT
			case 1:
				SpawnRoom(FVector(CurrentChunk->GetActorLocation().X, CurrentChunk->GetActorLocation().Y + ChunkDistance, CurrentChunk->GetActorLocation().Z), FString("left"));
				roomLocation = 1;
				CurrentChunk->SetDoor(FString("right"), true);
				break;
				// LEFT
			case 2:
				SpawnRoom(FVector(CurrentChunk->GetActorLocation().X, CurrentChunk->GetActorLocation().Y - ChunkDistance, CurrentChunk->GetActorLocation().Z), FString("right"));
				roomLocation = 3;
				CurrentChunk->SetDoor(FString("left"), true);
				break;
			default:
				break;
			}

			// ���� �ձ� or �� �Ѱ��� ��
			// if ���� ���� FMath::RandRange(0, 1) == 0
			if (true)
			{
				int8 checkCanGo = FMath::RandRange(0, 2);
				TArray<int8> roomNumber = { 0, 1, 3 };

				while (roomNumber[checkCanGo] == roomLocation)
					checkCanGo = FMath::RandRange(0, 2);

				switch (checkCanGo)
				{
					// UP
				case 0:
					returnActor = SpawnCorrider(FVector(CurrentChunk->GetActorLocation().X + ChunkDistance, CurrentChunk->GetActorLocation().Y, CurrentChunk->GetActorLocation().Z), FString("down"));
					CurrentChunk->SetDoor(FString("up"), true);
					break;
					// RIGHT
				case 1:
					returnActor = SpawnCorrider(FVector(CurrentChunk->GetActorLocation().X, CurrentChunk->GetActorLocation().Y + ChunkDistance, CurrentChunk->GetActorLocation().Z), FString("left"));
					CurrentChunk->SetDoor(FString("right"), true);
					break;
					// LEFT
				case 2:
					returnActor = SpawnCorrider(FVector(CurrentChunk->GetActorLocation().X, CurrentChunk->GetActorLocation().Y - ChunkDistance, CurrentChunk->GetActorLocation().Z), FString("right"));
					CurrentChunk->SetDoor(FString("left"), true);
					break;
				default:
					break;
				}
			}
			else
				return nullptr;

		}
		else									// ������ ����
		{
			switch (FMath::RandRange(0, 2))
			{
				// UP
			case 0:
				returnActor = SpawnCorrider(FVector(CurrentChunk->GetActorLocation().X + ChunkDistance, CurrentChunk->GetActorLocation().Y, CurrentChunk->GetActorLocation().Z), FString("down"));
				CurrentChunk->SetDoor(FString("up"), true);
				break;
				// RIGHT
			case 1:
				returnActor = SpawnCorrider(FVector(CurrentChunk->GetActorLocation().X, CurrentChunk->GetActorLocation().Y + ChunkDistance, CurrentChunk->GetActorLocation().Z), FString("left"));
				CurrentChunk->SetDoor(FString("right"), true);
				break;
				// LEFT
			case 2:
				returnActor = SpawnCorrider(FVector(CurrentChunk->GetActorLocation().X, CurrentChunk->GetActorLocation().Y - ChunkDistance, CurrentChunk->GetActorLocation().Z), FString("right"));
				CurrentChunk->SetDoor(FString("left"), true);
				break;
			default:
				break;
			}
		}
	}

	/*
	* ������ �����ִ� ���
	*/
	else if (!upHitSuccess && !rightHitSuccess && !downHitSuccess && leftHitSuccess)
	{
		// ���� ������ų�� ����
		if (FMath::RandRange(0, 1) == 0)		// ���� ����
		{
			/*
			* ���� ���� ��Ų ��, ������ �ϳ� �� ������ ������ ����.
			* Door�� �ִ� �κе� �Բ� �������ش�.
			*/
			int8 roomLocation;

			switch (FMath::RandRange(0, 2))
			{
				// UP
			case 0:
				SpawnRoom(FVector(CurrentChunk->GetActorLocation().X + ChunkDistance, CurrentChunk->GetActorLocation().Y, CurrentChunk->GetActorLocation().Z), FString("down"));
				roomLocation = 0;
				CurrentChunk->SetDoor(FString("up"), true);
				break;
				// RIGHT
			case 1:
				SpawnRoom(FVector(CurrentChunk->GetActorLocation().X, CurrentChunk->GetActorLocation().Y + ChunkDistance, CurrentChunk->GetActorLocation().Z), FString("left"));
				roomLocation = 1;
				CurrentChunk->SetDoor(FString("right"), true);
				break;
				// DOWN
			case 2:
				SpawnRoom(FVector(CurrentChunk->GetActorLocation().X - ChunkDistance, CurrentChunk->GetActorLocation().Y, CurrentChunk->GetActorLocation().Z), FString("up"));
				roomLocation = 2;
				CurrentChunk->SetDoor(FString("down"), true);
				break;
			default:
				break;
			}

			// ���� �ձ� or �� �Ѱ��� ��
			// if ���� ���� FMath::RandRange(0, 1) == 0
			if (true)
			{
				int8 checkCanGo = FMath::RandRange(0, 2);
				TArray<int8> roomNumber = { 0, 1, 2 };

				while (roomNumber[checkCanGo] == roomLocation)
					checkCanGo = FMath::RandRange(0, 2);

				switch (checkCanGo)
				{
					// UP
				case 0:
					returnActor = SpawnCorrider(FVector(CurrentChunk->GetActorLocation().X + ChunkDistance, CurrentChunk->GetActorLocation().Y, CurrentChunk->GetActorLocation().Z), FString("down"));
					CurrentChunk->SetDoor(FString("up"), true);
					break;
					// RIGHT
				case 1:
					returnActor = SpawnCorrider(FVector(CurrentChunk->GetActorLocation().X, CurrentChunk->GetActorLocation().Y + ChunkDistance, CurrentChunk->GetActorLocation().Z), FString("left"));
					CurrentChunk->SetDoor(FString("right"), true);
					break;
					// DOWN
				case 2:
					returnActor = SpawnCorrider(FVector(CurrentChunk->GetActorLocation().X - ChunkDistance, CurrentChunk->GetActorLocation().Y, CurrentChunk->GetActorLocation().Z), FString("up"));
					CurrentChunk->SetDoor(FString("down"), true);
					break;
				default:
					break;
				}
			}
			else
				return nullptr;

		}
		else									// ������ ����
		{
			switch (FMath::RandRange(0, 2))
			{
				// UP
			case 0:
				returnActor = SpawnCorrider(FVector(CurrentChunk->GetActorLocation().X + ChunkDistance, CurrentChunk->GetActorLocation().Y, CurrentChunk->GetActorLocation().Z), FString("down"));
				CurrentChunk->SetDoor(FString("up"), true);
				break;
				// RIGHT
			case 1:
				returnActor = SpawnCorrider(FVector(CurrentChunk->GetActorLocation().X, CurrentChunk->GetActorLocation().Y + ChunkDistance, CurrentChunk->GetActorLocation().Z), FString("left"));
				CurrentChunk->SetDoor(FString("right"), true);
				break;
				// DOWN
			case 2:
				returnActor = SpawnCorrider(FVector(CurrentChunk->GetActorLocation().X - ChunkDistance, CurrentChunk->GetActorLocation().Y, CurrentChunk->GetActorLocation().Z), FString("up"));
				CurrentChunk->SetDoor(FString("down"), true);
				break;
			default:
				break;
			}
		}
	}

	/*
	* ���� �������� �����ִ� ���
	*/
	else if (upHitSuccess && rightHitSuccess && !downHitSuccess && !leftHitSuccess)
	{
		MakingDoor(CurrentChunk, upHitResult, rightHitResult, downHitResult, leftHitResult);

		// ���� ������ų�� ����
		if (FMath::RandRange(0, 1) == 0)		// ���� ����
		{
			/*
			* ���� ���� ��Ų ��, ������ �ϳ� �� ������ ������ ����.
			* Door�� �ִ� �κе� �Բ� �������ش�.
			*/
			int8 roomLocation;

			switch (FMath::RandRange(0, 1))
			{
				// DOWN
			case 0:
				SpawnRoom(FVector(CurrentChunk->GetActorLocation().X - ChunkDistance, CurrentChunk->GetActorLocation().Y, CurrentChunk->GetActorLocation().Z), FString("up"));
				roomLocation = 2;
				CurrentChunk->SetDoor(FString("down"), true);
				break;
				// LEFT
			case 1:
				SpawnRoom(FVector(CurrentChunk->GetActorLocation().X, CurrentChunk->GetActorLocation().Y - ChunkDistance, CurrentChunk->GetActorLocation().Z), FString("right"));
				roomLocation = 3;
				CurrentChunk->SetDoor(FString("left"), true);
				break;
			default:
				break;
			}

			// ���� �ձ� or �� �Ѱ��� ��
			// if ���� ���� FMath::RandRange(0, 1) == 0
			if (true)
			{
				int8 checkCanGo = FMath::RandRange(0, 1);
				TArray<int8> roomNumber = { 2, 3 };

				while (roomNumber[checkCanGo] == roomLocation)
					checkCanGo = FMath::RandRange(0, 1);

				switch (checkCanGo)
				{
					// DOWN
				case 0:
					returnActor = SpawnCorrider(FVector(CurrentChunk->GetActorLocation().X - ChunkDistance, CurrentChunk->GetActorLocation().Y, CurrentChunk->GetActorLocation().Z), FString("up"));
					CurrentChunk->SetDoor(FString("down"), true);
					break;
					// LEFT
				case 1:
					returnActor = SpawnCorrider(FVector(CurrentChunk->GetActorLocation().X, CurrentChunk->GetActorLocation().Y - ChunkDistance, CurrentChunk->GetActorLocation().Z), FString("right"));
					CurrentChunk->SetDoor(FString("left"), true);
					break;
				default:
					break;
				}
			}
			else
				return nullptr;

		}
		else									// ������ ����
		{
			switch (FMath::RandRange(0, 1))
			{
				// DOWN
			case 0:
				returnActor = SpawnCorrider(FVector(CurrentChunk->GetActorLocation().X - ChunkDistance, CurrentChunk->GetActorLocation().Y, CurrentChunk->GetActorLocation().Z), FString("up"));
				CurrentChunk->SetDoor(FString("down"), true);
				break;
				// LEFT
			case 1:
				returnActor = SpawnCorrider(FVector(CurrentChunk->GetActorLocation().X, CurrentChunk->GetActorLocation().Y - ChunkDistance, CurrentChunk->GetActorLocation().Z), FString("right"));
				CurrentChunk->SetDoor(FString("left"), true);
				break;
			default:
				break;
			}
		}
	}

	/*
	* �����ʰ� �Ʒ��� �����ִ� ���
	*/
	else if (!upHitSuccess && rightHitSuccess && downHitSuccess && !leftHitSuccess)
	{
		MakingDoor(CurrentChunk, upHitResult, rightHitResult, downHitResult, leftHitResult);

		// ���� ������ų�� ����
		if (FMath::RandRange(0, 1) == 0)		// ���� ����
		{
			/*
			* ���� ���� ��Ų ��, ������ �ϳ� �� ������ ������ ����.
			* Door�� �ִ� �κе� �Բ� �������ش�.
			*/
			int8 roomLocation;

			switch (FMath::RandRange(0, 1))
			{
				// UP
			case 0:
				SpawnRoom(FVector(CurrentChunk->GetActorLocation().X + ChunkDistance, CurrentChunk->GetActorLocation().Y, CurrentChunk->GetActorLocation().Z), FString("down"));
				roomLocation = 0;
				CurrentChunk->SetDoor(FString("up"), true);
				break;
				// LEFT
			case 1:
				SpawnRoom(FVector(CurrentChunk->GetActorLocation().X, CurrentChunk->GetActorLocation().Y - ChunkDistance, CurrentChunk->GetActorLocation().Z), FString("right"));
				roomLocation = 3;
				CurrentChunk->SetDoor(FString("left"), true);
				break;
			default:
				break;
			}

			// ���� �ձ� or �� �Ѱ��� ��
			// if ���� ���� FMath::RandRange(0, 1) == 0
			if (true)
			{
				int8 checkCanGo = FMath::RandRange(0, 1);
				TArray<int8> roomNumber = { 0, 3 };

				while (roomNumber[checkCanGo] == roomLocation)
					checkCanGo = FMath::RandRange(0, 1);

				switch (checkCanGo)
				{
					// UP
				case 0:
					returnActor = SpawnCorrider(FVector(CurrentChunk->GetActorLocation().X + ChunkDistance, CurrentChunk->GetActorLocation().Y, CurrentChunk->GetActorLocation().Z), FString("down"));
					CurrentChunk->SetDoor(FString("up"), true);
					break;
					// LEFT
				case 1:
					returnActor = SpawnCorrider(FVector(CurrentChunk->GetActorLocation().X, CurrentChunk->GetActorLocation().Y - ChunkDistance, CurrentChunk->GetActorLocation().Z), FString("right"));
					CurrentChunk->SetDoor(FString("left"), true);
					break;
				default:
					break;
				}
			}
			else
				return nullptr;

		}
		else									// ������ ����
		{
			switch (FMath::RandRange(0, 1))
			{
				// UP
			case 0:
				returnActor = SpawnCorrider(FVector(CurrentChunk->GetActorLocation().X + ChunkDistance, CurrentChunk->GetActorLocation().Y, CurrentChunk->GetActorLocation().Z), FString("down"));
				CurrentChunk->SetDoor(FString("up"), true);
				break;
				// LEFT
			case 1:
				returnActor = SpawnCorrider(FVector(CurrentChunk->GetActorLocation().X, CurrentChunk->GetActorLocation().Y - ChunkDistance, CurrentChunk->GetActorLocation().Z), FString("right"));
				CurrentChunk->SetDoor(FString("left"), true);
				break;
			default:
				break;
			}
		}
	}

	/*
	* �Ʒ��� ������ �����ִ� ���
	*/
	else if (!upHitSuccess && !rightHitSuccess && downHitSuccess && leftHitSuccess)
	{
		MakingDoor(CurrentChunk, upHitResult, rightHitResult, downHitResult, leftHitResult);

		// ���� ������ų�� ����
		if (FMath::RandRange(0, 1) == 0)		// ���� ����
		{
			/*
			* ���� ���� ��Ų ��, ������ �ϳ� �� ������ ������ ����.
			* Door�� �ִ� �κе� �Բ� �������ش�.
			*/
			int8 roomLocation;

			switch (FMath::RandRange(0, 1))
			{
				// UP
			case 0:
				SpawnRoom(FVector(CurrentChunk->GetActorLocation().X + ChunkDistance, CurrentChunk->GetActorLocation().Y, CurrentChunk->GetActorLocation().Z), FString("down"));
				roomLocation = 0;
				CurrentChunk->SetDoor(FString("up"), true);
				break;
				// RIGHT
			case 1:
				SpawnRoom(FVector(CurrentChunk->GetActorLocation().X, CurrentChunk->GetActorLocation().Y + ChunkDistance, CurrentChunk->GetActorLocation().Z), FString("left"));
				roomLocation = 1;
				CurrentChunk->SetDoor(FString("right"), true);
				break;
			default:
				break;
			}

			// ���� �ձ� or �� �Ѱ��� ��
			// if ���� ���� FMath::RandRange(0, 1) == 0
			if (true)
			{
				int8 checkCanGo = FMath::RandRange(0, 1);
				TArray<int8> roomNumber = { 0, 1 };

				while (roomNumber[checkCanGo] == roomLocation)
					checkCanGo = FMath::RandRange(0, 1);

				switch (checkCanGo)
				{
					// UP
				case 0:
					returnActor = SpawnCorrider(FVector(CurrentChunk->GetActorLocation().X + ChunkDistance, CurrentChunk->GetActorLocation().Y, CurrentChunk->GetActorLocation().Z), FString("down"));
					CurrentChunk->SetDoor(FString("up"), true);
					break;
					// RIGHT
				case 1:
					returnActor = SpawnCorrider(FVector(CurrentChunk->GetActorLocation().X, CurrentChunk->GetActorLocation().Y + ChunkDistance, CurrentChunk->GetActorLocation().Z), FString("left"));
					CurrentChunk->SetDoor(FString("right"), true);
					break;
				default:
					break;
				}
			}
			else
				return nullptr;

		}
		else									// ������ ����
		{
			switch (FMath::RandRange(0, 1))
			{
				// UP
			case 0:
				returnActor = SpawnCorrider(FVector(CurrentChunk->GetActorLocation().X + ChunkDistance, CurrentChunk->GetActorLocation().Y, CurrentChunk->GetActorLocation().Z), FString("down"));
				CurrentChunk->SetDoor(FString("up"), true);
				break;
				// RIGHT
			case 1:
				returnActor = SpawnCorrider(FVector(CurrentChunk->GetActorLocation().X, CurrentChunk->GetActorLocation().Y + ChunkDistance, CurrentChunk->GetActorLocation().Z), FString("left"));
				CurrentChunk->SetDoor(FString("right"), true);
				break;
			default:
				break;
			}
		}
	}

	/*
	* ���� ������ �����ִ� ���
	*/
	else if (upHitSuccess && !rightHitSuccess && !downHitSuccess && leftHitSuccess)
	{
		MakingDoor(CurrentChunk, upHitResult, rightHitResult, downHitResult, leftHitResult);

		// ���� ������ų�� ����
		if (FMath::RandRange(0, 1) == 0)		// ���� ����
		{
			/*
			* ���� ���� ��Ų ��, ������ �ϳ� �� ������ ������ ����.
			* Door�� �ִ� �κе� �Բ� �������ش�.
			*/
			int8 roomLocation;

			switch (FMath::RandRange(0, 1))
			{
				break;
				// RIGHT
			case 0:
				SpawnRoom(FVector(CurrentChunk->GetActorLocation().X, CurrentChunk->GetActorLocation().Y + ChunkDistance, CurrentChunk->GetActorLocation().Z), FString("left"));
				roomLocation = 1;
				CurrentChunk->SetDoor(FString("right"), true);
				break;
				// DOWN
			case 1:
				SpawnRoom(FVector(CurrentChunk->GetActorLocation().X - ChunkDistance, CurrentChunk->GetActorLocation().Y, CurrentChunk->GetActorLocation().Z), FString("up"));
				roomLocation = 2;
				CurrentChunk->SetDoor(FString("down"), true);
				break;
			default:
				break;
			}

			// ���� �ձ� or �� �Ѱ��� ��
			// if ���� ���� FMath::RandRange(0, 1) == 0
			if (true)
			{
				int8 checkCanGo = FMath::RandRange(0, 1);
				TArray<int8> roomNumber = { 1, 2 };

				while (roomNumber[checkCanGo] == roomLocation)
					checkCanGo = FMath::RandRange(0, 1);

				switch (checkCanGo)
				{
					// RIGHT
				case 0:
					returnActor = SpawnCorrider(FVector(CurrentChunk->GetActorLocation().X, CurrentChunk->GetActorLocation().Y + ChunkDistance, CurrentChunk->GetActorLocation().Z), FString("left"));
					CurrentChunk->SetDoor(FString("right"), true);
					break;
					// DOWN
				case 1:
					returnActor = SpawnCorrider(FVector(CurrentChunk->GetActorLocation().X - ChunkDistance, CurrentChunk->GetActorLocation().Y, CurrentChunk->GetActorLocation().Z), FString("up"));
					CurrentChunk->SetDoor(FString("down"), true);
					break;
				default:
					break;
				}
			}
			else
				return nullptr;

		}
		else									// ������ ����
		{
			switch (FMath::RandRange(0, 1))
			{
				// RIGHT
			case 0:
				returnActor = SpawnCorrider(FVector(CurrentChunk->GetActorLocation().X, CurrentChunk->GetActorLocation().Y + ChunkDistance, CurrentChunk->GetActorLocation().Z), FString("left"));
				CurrentChunk->SetDoor(FString("right"), true);
				break;
				// DOWN
			case 1:
				returnActor = SpawnCorrider(FVector(CurrentChunk->GetActorLocation().X - ChunkDistance, CurrentChunk->GetActorLocation().Y, CurrentChunk->GetActorLocation().Z), FString("up"));
				CurrentChunk->SetDoor(FString("down"), true);
				break;
			default:
				break;
			}
		}
	}

	/*
	* ���� �Ʒ��� �����ִ� ���
	*/
	else if (upHitSuccess && !rightHitSuccess && downHitSuccess && !leftHitSuccess)
	{
		MakingDoor(CurrentChunk, upHitResult, rightHitResult, downHitResult, leftHitResult);

		// ���� ������ų�� ����
		if (FMath::RandRange(0, 1) == 0)		// ���� ����
		{
			/*
			* ���� ���� ��Ų ��, ������ �ϳ� �� ������ ������ ����.
			* Door�� �ִ� �κе� �Բ� �������ش�.
			*/
			int8 roomLocation;

			switch (FMath::RandRange(0, 1))
			{
				// RIGHT
			case 0:
				SpawnRoom(FVector(CurrentChunk->GetActorLocation().X, CurrentChunk->GetActorLocation().Y + ChunkDistance, CurrentChunk->GetActorLocation().Z), FString("left"));
				roomLocation = 1;
				CurrentChunk->SetDoor(FString("right"), true);
				break;
				// LEFT
			case 1:
				SpawnRoom(FVector(CurrentChunk->GetActorLocation().X, CurrentChunk->GetActorLocation().Y - ChunkDistance, CurrentChunk->GetActorLocation().Z), FString("right"));
				roomLocation = 3;
				CurrentChunk->SetDoor(FString("left"), true);
				break;
			default:
				break;
			}

			// ���� �ձ� or �� �Ѱ��� ��
			// if ���� ���� FMath::RandRange(0, 1) == 0
			if (true)
			{
				int8 checkCanGo = FMath::RandRange(0, 1);
				TArray<int8> roomNumber = { 1, 3 };

				while (roomNumber[checkCanGo] == roomLocation)
					checkCanGo = FMath::RandRange(0, 1);

				switch (checkCanGo)
				{
					// RIGHT
				case 0:
					returnActor = SpawnCorrider(FVector(CurrentChunk->GetActorLocation().X, CurrentChunk->GetActorLocation().Y + ChunkDistance, CurrentChunk->GetActorLocation().Z), FString("left"));
					CurrentChunk->SetDoor(FString("right"), true);
					break;
					// LEFT
				case 1:
					returnActor = SpawnCorrider(FVector(CurrentChunk->GetActorLocation().X, CurrentChunk->GetActorLocation().Y - ChunkDistance, CurrentChunk->GetActorLocation().Z), FString("right"));
					CurrentChunk->SetDoor(FString("left"), true);
					break;
				default:
					break;
				}
			}
			else
				return nullptr;

		}
		else									// ������ ����
		{
			switch (FMath::RandRange(0, 1))
			{
				// RIGHT
			case 0:
				returnActor = SpawnCorrider(FVector(CurrentChunk->GetActorLocation().X, CurrentChunk->GetActorLocation().Y + ChunkDistance, CurrentChunk->GetActorLocation().Z), FString("left"));
				CurrentChunk->SetDoor(FString("right"), true);
				break;
				// LEFT
			case 1:
				returnActor = SpawnCorrider(FVector(CurrentChunk->GetActorLocation().X, CurrentChunk->GetActorLocation().Y - ChunkDistance, CurrentChunk->GetActorLocation().Z), FString("right"));
				CurrentChunk->SetDoor(FString("left"), true);
				break;
			default:
				break;
			}
		}
	}

	/*
	* ���ʰ� �������� �����ִ� ���
	*/
	else if (upHitSuccess && !rightHitSuccess && !downHitSuccess && leftHitSuccess)
	{
		MakingDoor(CurrentChunk, upHitResult, rightHitResult, downHitResult, leftHitResult);

		// ���� ������ų�� ����
		if (FMath::RandRange(0, 1) == 0)		// ���� ����
		{
			/*
			* ���� ���� ��Ų ��, ������ �ϳ� �� ������ ������ ����.
			* Door�� �ִ� �κе� �Բ� �������ش�.
			*/
			int8 roomLocation;

			switch (FMath::RandRange(0, 1))
			{
				// UP
			case 0:
				SpawnRoom(FVector(CurrentChunk->GetActorLocation().X + ChunkDistance, CurrentChunk->GetActorLocation().Y, CurrentChunk->GetActorLocation().Z), FString("down"));
				roomLocation = 0;
				CurrentChunk->SetDoor(FString("up"), true);
				break;
				// DOWN
			case 1:
				SpawnRoom(FVector(CurrentChunk->GetActorLocation().X - ChunkDistance, CurrentChunk->GetActorLocation().Y, CurrentChunk->GetActorLocation().Z), FString("up"));
				roomLocation = 2;
				CurrentChunk->SetDoor(FString("down"), true);
				break;
			default:
				break;
			}

			// ���� �ձ� or �� �Ѱ��� ��
			// if ���� ���� FMath::RandRange(0, 1) == 0
			if (true)
			{
				int8 checkCanGo = FMath::RandRange(0, 1);
				TArray<int8> roomNumber = { 0, 2 };

				while (roomNumber[checkCanGo] == roomLocation)
					checkCanGo = FMath::RandRange(0, 1);

				switch (checkCanGo)
				{
					// UP
				case 0:
					returnActor = SpawnCorrider(FVector(CurrentChunk->GetActorLocation().X + ChunkDistance, CurrentChunk->GetActorLocation().Y, CurrentChunk->GetActorLocation().Z), FString("down"));
					CurrentChunk->SetDoor(FString("up"), true);
					break;
					// DOWN
				case 1:
					returnActor = SpawnCorrider(FVector(CurrentChunk->GetActorLocation().X - ChunkDistance, CurrentChunk->GetActorLocation().Y, CurrentChunk->GetActorLocation().Z), FString("up"));
					CurrentChunk->SetDoor(FString("down"), true);
					break;
				default:
					break;
				}
			}
			else
				return nullptr;

		}
		else									// ������ ����
		{
			switch (FMath::RandRange(0, 1))
			{
				// UP
			case 0:
				returnActor = SpawnCorrider(FVector(CurrentChunk->GetActorLocation().X + ChunkDistance, CurrentChunk->GetActorLocation().Y, CurrentChunk->GetActorLocation().Z), FString("down"));
				CurrentChunk->SetDoor(FString("up"), true);
				break;
				// DOWN
			case 1:
				returnActor = SpawnCorrider(FVector(CurrentChunk->GetActorLocation().X - ChunkDistance, CurrentChunk->GetActorLocation().Y, CurrentChunk->GetActorLocation().Z), FString("up"));
				CurrentChunk->SetDoor(FString("down"), true);
				break;
			default:
				break;
			}
		}
	}

	/*
	* ���� ������, �Ʒ��� �����ִ� ���
	*/
	else if (upHitSuccess && rightHitSuccess && downHitSuccess && !leftHitSuccess)
	{
		MakingDoor(CurrentChunk, upHitResult, rightHitResult, downHitResult, leftHitResult);

		// ���� ������ų�� ����
		if (FMath::RandRange(0, 1) == 0)		// ���� ����
		{
			/*
			* ���� ���� ��Ų ��, ������ �ϳ� �� ������ ������ ����.
			* Door�� �ִ� �κе� �Բ� �������ش�.
			*/

			// LEFT
			SpawnRoom(FVector(CurrentChunk->GetActorLocation().X, CurrentChunk->GetActorLocation().Y - ChunkDistance, CurrentChunk->GetActorLocation().Z), FString("right"));
			CurrentChunk->SetDoor(FString("left"), true);
		}
		else									// ������ ����
		{
			// LEFT
			returnActor = SpawnCorrider(FVector(CurrentChunk->GetActorLocation().X, CurrentChunk->GetActorLocation().Y - ChunkDistance, CurrentChunk->GetActorLocation().Z), FString("right"));
			CurrentChunk->SetDoor(FString("left"), true);
		}
	}

	/*
	* �����ʰ� �Ʒ�, ������ �����ִ� ���
	*/
	else if (!upHitSuccess && rightHitSuccess && downHitSuccess && leftHitSuccess)
	{
		MakingDoor(CurrentChunk, upHitResult, rightHitResult, downHitResult, leftHitResult);

		// ���� ������ų�� ����
		if (FMath::RandRange(0, 1) == 0)		// ���� ����
		{
			/*
			* ���� ���� ��Ų ��, ������ �ϳ� �� ������ ������ ����.
			* Door�� �ִ� �κе� �Բ� �������ش�.
			*/

			// UP
			SpawnRoom(FVector(CurrentChunk->GetActorLocation().X + ChunkDistance, CurrentChunk->GetActorLocation().Y, CurrentChunk->GetActorLocation().Z), FString("down"));
			CurrentChunk->SetDoor(FString("up"), true);
		}
		else									// ������ ����
		{
			// UP
			returnActor = SpawnCorrider(FVector(CurrentChunk->GetActorLocation().X + ChunkDistance, CurrentChunk->GetActorLocation().Y, CurrentChunk->GetActorLocation().Z), FString("down"));
			CurrentChunk->SetDoor(FString("up"), true);
		}
	}

	/*
	*�Ʒ��� ����, ���� �����ִ� ���
	*/
	else if (!upHitSuccess && rightHitSuccess && downHitSuccess && leftHitSuccess)
	{
		MakingDoor(CurrentChunk, upHitResult, rightHitResult, downHitResult, leftHitResult);

		// ���� ������ų�� ����
		if (FMath::RandRange(0, 1) == 0)		// ���� ����
		{
			/*
			* ���� ���� ��Ų ��, ������ �ϳ� �� ������ ������ ����.
			* Door�� �ִ� �κе� �Բ� �������ش�.
			*/

			// RIGHT
			SpawnRoom(FVector(CurrentChunk->GetActorLocation().X, CurrentChunk->GetActorLocation().Y + ChunkDistance, CurrentChunk->GetActorLocation().Z), FString("left"));
			CurrentChunk->SetDoor(FString("right"), true);
		}
		else									// ������ ����
		{
			// RIGHT
			returnActor = SpawnCorrider(FVector(CurrentChunk->GetActorLocation().X, CurrentChunk->GetActorLocation().Y + ChunkDistance, CurrentChunk->GetActorLocation().Z), FString("left"));
			CurrentChunk->SetDoor(FString("right"), true);
		}
	}

	/*
	*���ʰ� ��, �������� �����ִ� ���
	*/
	else if (upHitSuccess && rightHitSuccess && !downHitSuccess && leftHitSuccess)
	{
		MakingDoor(CurrentChunk, upHitResult, rightHitResult, downHitResult, leftHitResult);

		// ���� ������ų�� ����
		if (FMath::RandRange(0, 1) == 0)		// ���� ����
		{
			/*
			* ���� ���� ��Ų ��, ������ �ϳ� �� ������ ������ ����.
			* Door�� �ִ� �κе� �Բ� �������ش�.
			*/

			// DOWN
			SpawnRoom(FVector(CurrentChunk->GetActorLocation().X - ChunkDistance, CurrentChunk->GetActorLocation().Y, CurrentChunk->GetActorLocation().Z), FString("up"));
			CurrentChunk->SetDoor(FString("down"), true);
		}
		else									// ������ ����
		{
			// DOWN
			returnActor = SpawnCorrider(FVector(CurrentChunk->GetActorLocation().X - ChunkDistance, CurrentChunk->GetActorLocation().Y, CurrentChunk->GetActorLocation().Z), FString("up"));
			CurrentChunk->SetDoor(FString("down"), true);
		}
	}

	/*
	*��� ���� �����ִ� ���
	*/
	else if (upHitSuccess && rightHitSuccess && downHitSuccess && leftHitSuccess)
	{
		return nullptr;
	}

	return returnActor;
}

void AMapGenerator::MakingDoor(AChunk* currentChunk, FHitResult upHitResult, FHitResult rightHitResult, FHitResult downHitResult, FHitResult leftHitResult)
{
	if (upHitResult.bBlockingHit)
	{
		if (upHitResult.Actor->IsA<ACorrider>())
		{
			Cast<ACorrider>(upHitResult.Actor)->SetDoor(FString("down"), true);
			currentChunk->SetDoor(FString("up"), true);
		}
	}
	if (rightHitResult.bBlockingHit)
	{
		if (rightHitResult.Actor->IsA<ACorrider>())
		{
			Cast<ACorrider>(rightHitResult.Actor)->SetDoor(FString("left"), true);
			currentChunk->SetDoor(FString("right"), true);
		}
	}
	if (downHitResult.bBlockingHit)
	{
		if (downHitResult.Actor->IsA<ACorrider>())
		{
			Cast<ACorrider>(downHitResult.Actor)->SetDoor(FString("up"), true);
			currentChunk->SetDoor(FString("down"), true);
		}
	}
	if (leftHitResult.bBlockingHit)
	{
		if (leftHitResult.Actor->IsA<ACorrider>())
		{
			Cast<ACorrider>(leftHitResult.Actor)->SetDoor(FString("right"), true);
			currentChunk->SetDoor(FString("left"), true);
		}
	}
}