// Fill out your copyright notice in the Description page of Project Settings.


#include "NAnimInstance.h"

UNAnimInstance::UNAnimInstance()
{
	CurrentPawnSpeed = 0.0f;
	IsDead = false;
	IsExercise = false;
	IsWhistle = false;
}

void UNAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);


	auto Pawn = TryGetPawnOwner();

	if (!::IsValid(Pawn)) return;

	if(!IsDead){
		CurrentPawnSpeed = Pawn->GetVelocity().Size();
	}
}

void UNAnimInstance::SetDeadAnim()
{ 
	IsDead = true; 
}

bool UNAnimInstance::GetIsDead()
{
	return IsDead;
}

void UNAnimInstance::AnimNotify_Footstep()
{
	Footstep.Broadcast();
}

void UNAnimInstance::SetOceanAnim()
{
	IsSwimming = true;
}

void UNAnimInstance::SetLandAnim()
{
	IsSwimming = false;
}

void UNAnimInstance::SetExercise()
{
	IsExercise = !IsExercise;
}

bool UNAnimInstance::GetExercise()
{
	return IsExercise;
}

void UNAnimInstance::SetWhistle()
{
	IsWhistle = !IsWhistle;
}

bool UNAnimInstance::GetWhistle()
{
	return IsWhistle;
}