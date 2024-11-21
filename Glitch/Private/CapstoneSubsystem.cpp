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
	* 여기서 HumanForm, ApparitionForm 두 개의 값을 받고, 영체화 상태 확인 후 각각의 폼 값을 받아와 설정한다.
	* 03.06일 기준 GetForm이 하나지만 분리되는 작업이 수행될 시 그 때 각각의 값을 가져와주면 된다.
	*/

	if (ApparitionMode)			// 영체화 상태일 시
	{
		/*
		* 방법 1. Actor를 Iterator를 사용하여 각각의 태그를 가진 것들을 찾아서 SetForm을 통해 Form을 조절한다.
		* 방법 2. 바뀔 총 액터를 지정한 후 (ex. 맵에 10개 생성된다 지정하면, 10개의 액터 변수를 미리 셋팅.), 각각의 변수를 사용하여 지정(비추) ----> Actor1->SetForm(Actor1->GetForm() + 2)느낌
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
	else						// 일반 상태일 시
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
			// Key 비교
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
