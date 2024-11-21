// Fill out your copyright notice in the Description page of Project Settings.


#include "TONPCAnimInstance.h"


UTONPCAnimInstance::UTONPCAnimInstance()
{
	CurrentPawnSpeed = 0;
}

void UTONPCAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);

	auto Pawn = TryGetPawnOwner();
	if (::IsValid(Pawn))
	{
		CurrentPawnSpeed = Pawn->GetVelocity().Size();
	}
}
