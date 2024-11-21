// Fill out your copyright notice in the Description page of Project Settings.


#include "TOAnimInstance.h"
#include "TOCharacter.h"
#include "TODeadWidget.h"

/*
* 기본 생성자
*/
UTOAnimInstance::UTOAnimInstance() 
{
	CurrentPawnSpeed = 0.0f;
	// 움직임 관련 변수 초기화
	IsInAir = false;
	DashState = false;

	// 몽타주 애니메이션 재생 - 연속공격
	static ConstructorHelpers::FObjectFinder<UAnimMontage> ATTACK_MONTAGE(TEXT("/Game/Tellours/Developer/Animations/Test_Skeleton_Montage.Test_Skeleton_Montage"));
	if (ATTACK_MONTAGE.Succeeded())
	{
		AttackMontage = ATTACK_MONTAGE.Object;
	}

	static ConstructorHelpers::FObjectFinder<UAnimMontage> HIT_ANIM_MONTAGE(TEXT("/Game/Tellours/Developer/Animations/Test_Hit_Montage.Test_Hit_Montage"));
	if (HIT_ANIM_MONTAGE.Succeeded())
	{
		HitMontage = HIT_ANIM_MONTAGE.Object;
	}

	static ConstructorHelpers::FObjectFinder<UAnimMontage> SHIELD_ANIM_MONTAGE(TEXT("/Game/Tellours/Developer/Animations/Test_Shield_Anim.Test_Shield_Anim"));
	if (SHIELD_ANIM_MONTAGE.Succeeded())
	{
		ShieldMontage = SHIELD_ANIM_MONTAGE.Object;
	}

	static ConstructorHelpers::FObjectFinder<UAnimMontage> SKILL2_ANIM_MONTAGE(TEXT("/Game/Tellours/Developer/Animations/Skill2_Montage.Skill2_Montage"));
	if (SKILL2_ANIM_MONTAGE.Succeeded())
	{
		Skill2_Montage = SKILL2_ANIM_MONTAGE.Object;
	}

	static ConstructorHelpers::FObjectFinder<UAnimMontage> SKILL3_ANIM_MONTAGE(TEXT("/Game/Tellours/Developer/Animations/Skill3_Montage.Skill3_Montage"));
	if (SKILL3_ANIM_MONTAGE.Succeeded())
	{
		Skill3_Montage = SKILL3_ANIM_MONTAGE.Object;
	}

	// 사망 애니메이션
	static ConstructorHelpers::FObjectFinder<UAnimSequence> DEATH_ANIM_1(TEXT("/Game/OrcaGamesFullAnimBundle/UltimateAnimationSet_V2/Animations/AS_Death_Anim.AS_Death_Anim"));
	if (DEATH_ANIM_1.Succeeded())
	{
		DeathAnim_1 = DEATH_ANIM_1.Object;
	}

	static ConstructorHelpers::FObjectFinder<UAnimSequence> DEATH_ANIM_2(TEXT("/Game/OrcaGamesFullAnimBundle/UltimateAnimationSet_V2/Animations/AS_Death_B_02_Anim.AS_Death_B_02_Anim"));
	if (DEATH_ANIM_2.Succeeded())
	{
		DeathAnim_2 = DEATH_ANIM_2.Object;
	}

	static ConstructorHelpers::FObjectFinder<UAnimSequence> DEATH_ANIM_3(TEXT("/Game/OrcaGamesFullAnimBundle/UltimateAnimationSet_V2/Animations/AS_Death_F_Anim.AS_Death_F_Anim"));
	if (DEATH_ANIM_3.Succeeded())
	{
		DeathAnim_3 = DEATH_ANIM_3.Object;
	}

	static ConstructorHelpers::FObjectFinder<UAnimSequence> DEATH_ANIM_4(TEXT("/Game/OrcaGamesFullAnimBundle/UltimateAnimationSet_V2/Animations/AS_Death_L_Anim.AS_Death_L_Anim"));
	if (DEATH_ANIM_4.Succeeded())
	{
		DeathAnim_4 = DEATH_ANIM_4.Object;
	}

	static ConstructorHelpers::FObjectFinder<UAnimSequence> DEATH_ANIM_5(TEXT("/Game/OrcaGamesFullAnimBundle/UltimateAnimationSet_V2/Animations/AS_Death_R_Anim.AS_Death_R_Anim"));
	if (DEATH_ANIM_5.Succeeded())
	{
		DeathAnim_5 = DEATH_ANIM_5.Object;
	}

	static ConstructorHelpers::FClassFinder<UUserWidget> UI_DEAD(TEXT("/Game/Tellours/Developer/UI/UI_Dead.UI_Dead_C"));
	if (UI_DEAD.Succeeded())
	{
		DeadWidgetClass = UI_DEAD.Class;
	};

	// 상태 관련 변수 초기화
	IsDead = false;
}

void UTOAnimInstance::NativeUpdateAnimation(float DeltaSeconds) {
	Super::NativeUpdateAnimation(DeltaSeconds);
	auto Pawn = TryGetPawnOwner();

	if (!::IsValid(Pawn)) return;
	if (!IsDead)
	{
		CurrentPawnSpeed = Pawn->GetVelocity().Size();
		auto Character = Cast<ACharacter>(Pawn);

		if (Character)
		{
			IsInAir = Character->GetMovementComponent()->IsFalling();
		}
	}
}

void UTOAnimInstance::SetDeadAnim()
{
	IsDead = true;

	DeadWidget = CreateWidget<UTODeadWidget>(GetWorld(), DeadWidgetClass);

	auto Character = Cast<ATOCharacter>(GetWorld()->GetFirstPlayerController()->GetCharacter());

	int32 random = FMath::RandRange(1, 5);

	ABLOG(Warning, TEXT("%d"), random);

	switch (random)
	{
		case 1:
			GetWorld()->GetFirstPlayerController()->GetCharacter()->GetMesh()->PlayAnimation(DeathAnim_1, false);
			break;
		case 2:
			GetWorld()->GetFirstPlayerController()->GetCharacter()->GetMesh()->PlayAnimation(DeathAnim_2, false);
			break;
		case 3:
			GetWorld()->GetFirstPlayerController()->GetCharacter()->GetMesh()->PlayAnimation(DeathAnim_3, false);
			break;
		case 4:
			GetWorld()->GetFirstPlayerController()->GetCharacter()->GetMesh()->PlayAnimation(DeathAnim_4, false);
			break;
		case 5:
			GetWorld()->GetFirstPlayerController()->GetCharacter()->GetMesh()->PlayAnimation(DeathAnim_5, false);
			break;
	}

	GetWorld()->GetFirstPlayerController()->SetIgnoreLookInput(true);
	GetWorld()->GetFirstPlayerController()->SetIgnoreMoveInput(true);

	DeadWidget->AddToViewport();
	DeadWidget->PlayDeadWidgetAnimation();
}

void UTOAnimInstance::SetMontageJump(FString Name)
{
	if (Name.Equals(FString("Shield")))
	{
		Montage_JumpToSection("Blocking", ShieldMontage);
	}
}


/*
*  몽타주 애니메이션 재생 - 연속 공격 몽타주
*/
void UTOAnimInstance::PlayAttackMontage()
{
	ABCHECK(!IsDead);
	Montage_Play(AttackMontage, 1.0);
}

void UTOAnimInstance::StopAttackMontage()
{
	Montage_Stop(0.1f, AttackMontage);
}

void UTOAnimInstance::AnimNotify_AttackHitCheck()
{
	OnAttackHitCheck.Broadcast();
}

void UTOAnimInstance::AnimNotify_NextAttackCheck()
{
	OnNextAttackCheck.Broadcast();
}

void UTOAnimInstance::AnimNotify_AttackStart()
{
	AttackStart.Broadcast();
}

void UTOAnimInstance::AnimNotify_Footstep()
{
	Footstep.Broadcast();
}

void UTOAnimInstance::AnimNotify_JumpSound()
{
	JumpSound.Broadcast();
}



/*
*  Hit 애니메이션 플레이
*/
void UTOAnimInstance::PlayHitAnimation()
{
	Montage_Play(HitMontage, 1.0);
}



/*
*  Shield 애니메이션 플레이
*/
void UTOAnimInstance::PlayShieldAnimation()
{
	Montage_Play(ShieldMontage, 1.0);
}

void UTOAnimInstance::AnimNotify_ShieldEnd()
{
	ShieldEnd.Broadcast();
	ABLOG(Warning, TEXT("END"));
}



/*
* Skill 2 Animation Play
*/
void UTOAnimInstance::PlaySkill2Animation()
{
	Montage_Play(Skill2_Montage, 1.0);
}

void UTOAnimInstance::AnimNotify_Skill2End()
{
	Skill2End.Broadcast();
	ABLOG(Warning, TEXT("END"));
}



/*
* Skill 3 Animation Play
*/
void UTOAnimInstance::PlaySkill3Animation()
{
	Montage_Play(Skill3_Montage, 1.0);
}

void UTOAnimInstance::AnimNotify_Skill3dEnd()
{
	Skill3End.Broadcast();
	ABLOG(Warning, TEXT("END"));
}



/*
*  이동 및 상태 관련
*/
bool UTOAnimInstance::GetAir()
{
	return IsInAir;
}

bool UTOAnimInstance::IsMontagePlaying(FString Name)
{
	if (Name.Equals(FString("Shield")))
	{
		if (Montage_IsPlaying(ShieldMontage))
		{
			return true;
		}
		else
		{
			return false;
		}
	}
	if (Name.Equals(FString("Attack")))
	{
		if (Montage_IsPlaying(AttackMontage))
		{
			return true;
		}
		else
		{
			return false;
		}
	}
	else
	{
		return false;
	}
	/*if (Montage_IsPlaying(AttackMontage))
	{
		return true;
	}
	else
	{
		return false;
	}*/
}