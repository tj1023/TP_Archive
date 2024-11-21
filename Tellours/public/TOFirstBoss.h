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

	// �ε巯�� ȸ��, �̵��ӵ� ����
	virtual void PossessedBy(AController* NewController) override;
	virtual void PostInitializeComponents() override;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;



/*
* �⺻ ���� ����
*/
private:
	UPROPERTY()
		ATOBossController* TOBossController;


/*
* Enemy ����
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
* Ÿ�̸�
*/
public:
	FTimerHandle AttackMotionTimerHandle;
	FTimerHandle DestroyTimerHandle;
	//FTimerHandle EnemyDeadTimeHandle = { };
	//FTimerHandle EnemySpawnTimeHandle = { };



/*
* ������ ���� �Լ�
*/
public:
	int32 GetPhase();
	void SetPhase();



/*
* ����
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
