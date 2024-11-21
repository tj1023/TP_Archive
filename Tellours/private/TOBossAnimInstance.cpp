// Fill out your copyright notice in the Description page of Project Settings.


#include "TOBossAnimInstance.h"

UTOBossAnimInstance::UTOBossAnimInstance()
{
	CurrentPawnSpeed = 0.0f;
	IsDead = false;

	Phase0 = false;
	Phase1 = false;
	Phase2 = false;
	PhaseZeroIsEnd = false;

	static ConstructorHelpers::FObjectFinder<UAnimMontage> ATTACK_MONTAGE(TEXT("/Game/Tellours/Developer/Animations/PigMontage.PigMontage"));
	if (ATTACK_MONTAGE.Succeeded())
	{
		AttackMontage = ATTACK_MONTAGE.Object;
	}
	static ConstructorHelpers::FObjectFinder<UAnimMontage> ATTACK_MONTAGE1(TEXT("/Game/Tellours/Developer/Animations/PigMontage1.PigMontage1"));
	if (ATTACK_MONTAGE1.Succeeded())
	{
		AttackMontage1 = ATTACK_MONTAGE.Object;
	}
}

void UTOBossAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);

	auto Pawn = TryGetPawnOwner();
	if (::IsValid(Pawn)) 
		CurrentPawnSpeed = Pawn->GetVelocity().Size();
}

void UTOBossAnimInstance::PlayAttackMontage()
{
	if (IsDead)
		return;

	// 페이즈에 따른 공격 변경
	if (Phase0 == true)
	{
		ABLOG(Warning, TEXT("PlayAttackMontage0"));
		return;
	}
	else if (Phase1 == true)
	{
		ABLOG(Warning, TEXT("PlayAttackMontage1"));
		Montage_Play(AttackMontage, 1.0f);
		return;
	}
	else if (Phase2 == true)
	{
		ABLOG(Warning, TEXT("PlayAttackMontage2"));
		Montage_Play(AttackMontage1, 1.0f);
		return;
	}
}

void UTOBossAnimInstance::AnimNotify_AttackHitCheck()
{
	OnAttackHitCheck.Broadcast();
	ABLOG(Warning, TEXT("Hit"));
}

void UTOBossAnimInstance::StopMontage()
{
	Montage_Stop(0.0f, AttackMontage1);
}
