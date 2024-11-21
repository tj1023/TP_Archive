// Fill out your copyright notice in the Description page of Project Settings.


#include "TOEnemyAnimInstance.h"
#include "TOEnemy.h"


UTOEnemyAnimInstance::UTOEnemyAnimInstance()
{
	CurrentPawnSpeed = 0;

	AttackMontage = nullptr;
	IsDead = false;
	IsAttacked = false;
}

void UTOEnemyAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);

	auto Pawn = TryGetPawnOwner();
	if (::IsValid(Pawn))
		CurrentPawnSpeed = Pawn->GetVelocity().Size();
}



void UTOEnemyAnimInstance::PlayAttackMontage()
{
	Montage_Play(AttackMontage, 1);
}



void UTOEnemyAnimInstance::AnimNotify_AttackHitCheck()
{
	OnAttackHitCheck.Broadcast();
}



/*
* EnemyType에 따른 몽타주 분류
*/
void UTOEnemyAnimInstance::SetMontageType(int32 EnemyNum)
{
	switch (EnemyNum) {

	case 1: {
		UAnimMontage* SM_Wolf = Cast<UAnimMontage>(StaticLoadObject(UAnimMontage::StaticClass(), NULL, TEXT("/Game/Tellours/Developer/Animations/SK_Wolf_Skeleton_Montage.SK_Wolf_Skeleton_Montage")));
		if (SM_Wolf)
		{
			AttackMontage = SM_Wolf;
		}
		break;
	}

	case 2: {
		UAnimMontage* SM_Mannequin = Cast<UAnimMontage>(StaticLoadObject(UAnimMontage::StaticClass(), NULL, TEXT("/Game/Tellours/Developer/Animations/MannequinPhase1.MannequinPhase1")));
		if (SM_Mannequin)
		{
			AttackMontage = SM_Mannequin;
		}
		break;
	}

	}
}

void UTOEnemyAnimInstance::SetPhaseMontage(int32 PhaseNum)
{
	switch (PhaseNum)
	{
	case 2:
	{
		UAnimMontage* SM_Mannequin = Cast<UAnimMontage>(StaticLoadObject(UAnimMontage::StaticClass(), NULL, TEXT("/Game/Tellours/Developer/Animations/MannequinPhase2.MannequinPhase2")));
		if (SM_Mannequin)
		{
			AttackMontage = SM_Mannequin;
		}
		break;
	}
	case 3:
	{
		UAnimMontage* SM_Mannequin = Cast<UAnimMontage>(StaticLoadObject(UAnimMontage::StaticClass(), NULL, TEXT("/Game/Tellours/Developer/Animations/MannequinPhase3.MannequinPhase3")));
		if (SM_Mannequin)
		{
			AttackMontage = SM_Mannequin;
		}
		break;
	}
	}
}
