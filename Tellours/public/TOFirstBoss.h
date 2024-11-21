// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Tellours.h"
#include "GameFramework/Character.h"
#include "TOBossAnimInstance.h"
#include "TOBossController.h"
#include "TOFirstBoss.generated.h"


DECLARE_MULTICAST_DELEGATE(FOnAttackEndDelegate);

UCLASS()
class TELLOURS_API ATOFirstBoss : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ATOFirstBoss();

	// 부드러운 회전, 이동속도 설정
	virtual void PossessedBy(AController* NewController) override;
	virtual void PostInitializeComponents() override;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;



/*
* 기본 제어 변수
*/
private:
	UPROPERTY()
		ATOBossController* TOBossController;


/*
* Enemy 스탯
*/
public:
	UPROPERTY(VisibleAnywhere, Category = Stat)
		class UTOBossStatComponent* BossStat;

	UPROPERTY(VisibleAnywhere, Category = UI)
		class UWidgetComponent* HPBarWidget;

/*
* Damage
*/
public:
	virtual float TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, AActor* DamageCauser) override;



/*
* 타이머
*/
public:
	FTimerHandle AttackMotionTimerHandle;
	FTimerHandle DestroyTimerHandle;
	//FTimerHandle EnemyDeadTimeHandle = { };
	//FTimerHandle EnemySpawnTimeHandle = { };



/*
* 페이즈 관련 함수
*/
public:
	int32 GetPhase();
	void SetPhase();



/*
* 공격
*/
public:
	void Attack();
	void AttackCheck();
	void SetAttackRange(float NewAttackRange);
	void SetAttackRadius(float NewAttackRadius);
	FOnAttackEndDelegate OnAttackEnd;
private:
	UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly, Category = Attack, Meta = (AllowPrivateAccess = true))
		bool IsAttacking;

	UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly, Category = Attack, Meta = (AllowPrivateAccess = true))
		float AttackRange;
	
	UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly, Category = Attack, Meta = (AllowPrivateAccess = true))
		float AttackRadius;

	UFUNCTION()
		void OnAttackMontageEnded(UAnimMontage* Montage, bool bInterrupted);

	UPROPERTY()
		class UTOBossAnimInstance* BossAnim;

};
