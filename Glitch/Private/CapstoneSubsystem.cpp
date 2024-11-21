// Fill out your copyright notice in the Description page of Project Settings.


#include "CapstoneSubsystem.h"
#include "CapstoneController.h"
#include "Door.h"

UCapstoneSubsystem::UCapstoneSubsystem()
{

}

void UCapstoneSubsystem::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);
}

void UCapstoneSubsystem::Deinitialize()
{
	Super::Deinitialize();
}

void UCapstoneSubsystem::GetAppartionState(bool ApparitionMode)
{
	/*
	* ���⼭ HumanForm, ApparitionForm �� ���� ���� �ް�, ��üȭ ���� Ȯ�� �� ������ �� ���� �޾ƿ� �����Ѵ�.
	* 03.06�� ���� GetForm�� �ϳ����� �и��Ǵ� �۾��� ����� �� �� �� ������ ���� �������ָ� �ȴ�.
	*/

	if (ApparitionMode)			// ��üȭ ������ ��
	{
		/*
		* ��� 1. Actor�� Iterator�� ����Ͽ� ������ �±׸� ���� �͵��� ã�Ƽ� SetForm�� ���� Form�� �����Ѵ�.
		* ��� 2. �ٲ� �� ���͸� ������ �� (ex. �ʿ� 10�� �����ȴ� �����ϸ�, 10���� ���� ������ �̸� ����.), ������ ������ ����Ͽ� ����(����) ----> Actor1->SetForm(Actor1->GetForm() + 2)����
		*/
		for (TActorIterator<ACapstoneObject> Actor(GetWorld()); Actor; ++Actor)
		{
			if (Actor->ActorHasTag("CapstonObject"))
			{
				Actor->SetApparitionMode(ApparitionMode);
				Actor->SetApparitionForm(Actor->GetApparitionForm());
			}
		}
	}
	else						// �Ϲ� ������ ��
	{


		for (TActorIterator<ACapstoneObject> Actor(GetWorld()); Actor; ++Actor)
		{
			if (Actor->ActorHasTag("CapstonObject"))
			{
				Actor->SetApparitionMode(ApparitionMode);
				Actor->SetHumanForm(Actor->GetHumanForm());
			}
		}
	}
}

bool UCapstoneSubsystem::CheckIsCleared()
{
	bool flag = true;

	for (TActorIterator<ACapstoneObject> Actor(GetWorld()); Actor; ++Actor)
	{
		if (Actor->ActorHasTag("CapstonObject"))
		{
			// Key ��
			if (Actor->GetKey() != Actor->GetHumanForm())
			{
				flag = false;
			}
		}
	}

	ACapstoneController* CapstoneController = Cast<ACapstoneController>(GetWorld()->GetFirstPlayerController());

	if (flag)
	{
		CapstoneController->ShowTrueEndingUI();
		return flag;
	}
	else
	{
		if (IsValid(CapstoneController->GetHUDWidget()))
			CapstoneController->GetHUDWidget()->ShowDialog(FString("FAIL..!"));
		return flag;
	}
}

ADoor* UCapstoneSubsystem::GetTPDoor()
{
	TArray<ADoor*> Doors;
	for (ADoor* Door : TActorRange<ADoor>(GetWorld()))
	{
		if (Door->GetCanOpenDoor()) {
			Doors.Emplace(Door);
		}
	}

	if (Doors.Num() <= 0)
		return nullptr;

	int idx = FMath::RandRange(0, Doors.Num() - 1);
	if (Doors.IsValidIndex(idx))
		return Doors[idx];
	else
		return nullptr;
}

void UCapstoneSubsystem::SetCorLoc(TArray<FVector> CorridersLocation)
{
	CorLoc = CorridersLocation;
}

TArray<FVector> UCapstoneSubsystem::GetCorLoc()
{
	return CorLoc;
}
