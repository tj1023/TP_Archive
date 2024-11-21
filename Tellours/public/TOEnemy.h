// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Tellours.h"
#include "GameFramework/Character.h"
#include "TOEnemyAnimInstance.h"
#include "TOEnemy.generated.h"


/*
* Enemy 분류를 위한 UENUM 열거형 선언
*/
UENUM()
enum class EnemyType {
	WOLF,
	MANNEQUIN,
	CROW,
	MANNEQUIN2
};

DECLARE_MULTICAST_DELEGATE(FOnAttackEndDelegate);

UCLASS()
class TELLOURS_API ATOEnemy : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ATOEnemy();

	// 부드러운 회전, 이동속도 설정
	virtual void PossessedBy(AController* NewController) override;

	virtual void PostInitializeComponents() override;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;



/*
* 몬스터 분류
*/
public:
	void SetEnemyType(EnemyType NewEnemyType);
	EnemyType GetEnemyType();

	UPROPERTY(EditAnywhere, Category = Type, Meta = (AllowPrivateAccess = true))
	EnemyType CurrentEnemyType;

/*
* Enemy 스탯
*/
public:
	UPROPERTY(VisibleAnywhere, Category = Stat)
		class UTOEnemyStatComponent* EnemyStat;

	UPROPERTY(VisibleAnywhere, Category = UI)
		class UWidgetComponent* HPBarWidget;

	UTOEnemyStatComponent* GetEnemyStat();


/*
* 공격
*/
public:
	UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly, Category = Attack, Meta = (AllowPrivateAccess = true))
		float AttackRange;

	UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly, Category = Attack, Meta = (AllowPrivateAccess = true))
		float AttackRadius;

	FOnAttackEndDelegate OnAttackEnd;
	
	void Attack();
	void AttackCheck();
	UTOEnemyAnimInstance* GetEnemyAnim();

	UFUNCTION()
		void OnAttackMontageEnded(UAnimMontage* Montage, bool bInterrupted);

private:
	UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly, Category = Attack, Meta = (AllowPrivateAccess = true))
		bool IsAttacking;

	UPROPERTY()
		class UTOEnemyAnimInstance* TOAnim;



/*
* Damage
*/
public:
	virtual float TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, AActor* DamageCauser) override;



/*
* 스폰 관련 타이머
*/
public:
	FTimerHandle EnemyDeadTimeHandle = { };
	FTimerHandle EnemySpawnTimeHandle = { };
};
