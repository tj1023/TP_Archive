// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Tellours.h"
#include "Animation/AnimInstance.h"
#include "TOAnimInstance.generated.h"


// 공격 관련 델리게이트
DECLARE_MULTICAST_DELEGATE(FOnNextAttackCheckDelegate);
DECLARE_MULTICAST_DELEGATE(FOnAttackHitCheckDelegate);

DECLARE_MULTICAST_DELEGATE(FSwordAttackSoundDelegate);


// Footstep
DECLARE_MULTICAST_DELEGATE(FFootstepDelegate);
DECLARE_MULTICAST_DELEGATE(FJumpSoundDelegate);

// Skill
DECLARE_MULTICAST_DELEGATE(FShieldEndDelegate);
DECLARE_MULTICAST_DELEGATE(FSkill2EndDelegate);
DECLARE_MULTICAST_DELEGATE(FSkill3EndDelegate);

/**
 * 
 */
UCLASS()
class TELLOURS_API UTOAnimInstance : public UAnimInstance
{
	GENERATED_BODY()
	
// 생성자
public:
	UTOAnimInstance();

	virtual void NativeUpdateAnimation(float DeltaSeconds) override;

private:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Pawn, Meta = (AllowPrivateAccess = true))
		float CurrentPawnSpeed;

	// 점프 체공
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Pawn, Meta = (AllowPrivateAccess = true))
		bool IsInAir;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Pawn, Meta = (AllowPrivateAccess = true))
		bool DashState;

// 캐릭터 움직임 및 공격
public:
	FOnNextAttackCheckDelegate OnNextAttackCheck;
	FOnAttackHitCheckDelegate OnAttackHitCheck;

	FSwordAttackSoundDelegate AttackStart;

	FShieldEndDelegate ShieldEnd;
	FSkill2EndDelegate Skill2End;
	FSkill3EndDelegate Skill3End;

	void PlayAttackMontage();
	void StopAttackMontage();

	void PlayHitAnimation();

	void PlayShieldAnimation();
	void PlaySkill2Animation();
	void PlaySkill3Animation();

private:
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = Attack, Meta = (AllowPrivateAccess = true))
		UAnimMontage* AttackMontage;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = Attack, Meta = (AllowPrivateAccess = true))
		UAnimMontage* HitMontage;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = Attack, Meta = (AllowPrivateAccess = true))
		UAnimMontage* ShieldMontage;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = Attack, Meta = (AllowPrivateAccess = true))
		UAnimMontage* Skill2_Montage;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = Attack, Meta = (AllowPrivateAccess = true))
		UAnimMontage* Skill3_Montage;

	UFUNCTION()
		void AnimNotify_AttackHitCheck();

	UFUNCTION()
		void AnimNotify_NextAttackCheck();

	UFUNCTION()
		void AnimNotify_ShieldEnd();

	UFUNCTION()
		void AnimNotify_Skill2End();

	UFUNCTION()
		void AnimNotify_Skill3dEnd();

	UFUNCTION()
		void AnimNotify_AttackStart();

// Footstep
public:
	FFootstepDelegate Footstep;
	FJumpSoundDelegate JumpSound;

private:
	UFUNCTION()
		void AnimNotify_Footstep();

	UFUNCTION()
		void AnimNotify_JumpSound();

// 캐릭터 사망 애니메이션 및 Widget
protected:
	UPROPERTY()
	TSubclassOf<class UTODeadWidget> DeadWidgetClass;

private:
	UPROPERTY(VisibleAnywhere)
		class UTODeadWidget* DeadWidget;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = Attack, Meta = (AllowPrivateAccess = true))
		UAnimSequence* DeathAnim_1;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = Attack, Meta = (AllowPrivateAccess = true))
		UAnimSequence* DeathAnim_2;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = Attack, Meta = (AllowPrivateAccess = true))
		UAnimSequence* DeathAnim_3;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = Attack, Meta = (AllowPrivateAccess = true))
		UAnimSequence* DeathAnim_4;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = Attack, Meta = (AllowPrivateAccess = true))
		UAnimSequence* DeathAnim_5;

//상태 관련 함수, 변수
public:
	void SetDeadAnim();
	bool GetAir();
	bool IsMontagePlaying(FString Name);

	UFUNCTION()
		void SetMontageJump(FString Name);

private:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Pawn, Meta = (AllowPrivateAccess = true))
		bool IsDead;
};
