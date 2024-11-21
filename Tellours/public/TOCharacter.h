// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Tellours.h"
#include "GameFramework/Character.h"
#include "NiagaraFunctionLibrary.h"
#include "NiagaraComponent.h"
#include "Components/TimeLineComponent.h"
#include "TOItem.h"
#include "TOCharacter.generated.h"


UCLASS()
class TELLOURS_API ATOCharacter : public ACharacter
{
	GENERATED_BODY()

	// �⺻ ���� �����ڵ�.
public:
	ATOCharacter();

protected:
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	virtual void PostInitializeComponents() override;


	// ĳ���� �̵� �� ī�޶�.
public:
	bool CanMovementCancle;
	float DashDistance;

	UPROPERTY(VisibleAnywhere, Category = Camera)
	USpringArmComponent* SpringArm;

	UPROPERTY(VisibleAnywhere, Category = Camera)
	UCameraComponent* Camera;

	UPROPERTY()
	UInputComponent* PlayerInputComponentRef;

	UPROPERTY(VisibleAnywhere, Category = Effect)
	UNiagaraSystem* DashEffect;

protected:
	float ArmLengthTo;

private:
	UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly, Category = Attack, Meta = (AllowPrivateAccess = true))
	bool IsDashCoolDown;

	void UpDown(float NewAxisValue);
	void LeftRight(float NewAxisValue);
	void Jump() override;
	void LookUp(float NewAxisValue);
	void Turn(float NewAxisValue);;
	void ZoomIn();
	void ZoomOut();

	void SetControlMode(int32 ControlMode);

	// Dash ���� ����
public:
	UPROPERTY(EditAnywhere)
	UCurveFloat* DashCurve;

private:
	bool IsDashing;

	FOnTimelineFloat DashTimeLineUpdateDelegate;
	FOnTimelineEvent DashTimeLineFinishDelegate;

	FTimeline DashTimeline;

	UFUNCTION()
	void DashStart(float Output);

	UFUNCTION()
	void DashEnd();

	void Dash();

	// ĳ���� ���� �� �ִϸ��̼�
public:
	UPROPERTY()
	class UTOAnimInstance* TOAnim;

private:
	UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly, Category = Attack, Meta = (AllowPrivateAccess = true))
	bool IsAttacking;

	UPROPERTY(VisibleInstanceOnly, BluePrintReadOnly, Category = Attack, Meta = (AllowPrivateAccess = true))
	bool IsComboInputOn;

	UPROPERTY(VisibleInstanceOnly, BluePrintReadOnly, Category = Attack, Meta = (AllowPrivateAccess = true))
	int32 CurrentCombo;

	UPROPERTY(VisibleInstanceOnly, BluePrintReadOnly, Category = Attack, Meta = (AllowPrivateAccess = true))
	int32 MaxCombo;

	UFUNCTION()
	void OnAttackMontageEnded(UAnimMontage* Montage, bool bInterrupted);

	// ���� ���콺 Ŭ��
	void Attack();

	// ĳ���� �ִϸ��̼ǿ� ���� ����Ʈ
public:
	void ShowEffect();

private:
	UPROPERTY(VisibleAnywhere, Category = Effect)
	UParticleSystemComponent* ShieldEffect;

	// ĳ���� Footstep
public:
	void PlayFootstepSound();
	void PlayJumpSound();
	FHitResult FootstepPhysCheck();

private:
	bool FootstepCheck;
	FHitResult FloorHit;

	class USoundCue* TileSoundCue;
	class USoundCue* CarpetSoundCue;
	class USoundCue* DirtSoundCue;
	class USoundCue* GrassSoundCue;
	class USoundCue* RockSoundCue;
	class USoundCue* WoodSoundCue;

	class USoundCue* TileJumpCue;
	class USoundCue* CarpetJumpCue;
	class USoundCue* DirtJumpCue;
	class USoundCue* GrassJumpCue;
	class USoundCue* RockJumpCue;
	class USoundCue* WoodJumpCue;

	class USoundWave* SwordAttack;


	// ĳ���� ��ų ����
public:
	UPROPERTY(VisibleAnywhere, Category = UI)
	class UWidgetComponent* SkillWidget;

	UFUNCTION()
	void SetIsSkillUIOpened();

private:
	FTimerHandle TimerHandle;
	bool IsSkillUIOpened;

	void EnableSkillTool();

	// ĳ���� ���
public:
	UPROPERTY(VisibleAnywhere, Category = Weapon)
	UStaticMeshComponent* Weapon;

	UPROPERTY(VisibleAnywhere, Category = Armor)
	UStaticMeshComponent* Armor;

	// ĳ���� ����
public:
	UPROPERTY(VisibleAnywhere, Category = Stat)
	class UTOCharacterStatComponent* CharacterStat;

	UPROPERTY(VisibleAnywhere, Category = UI)
	class UWidgetComponent* HPBarWidget;

	UTOCharacterStatComponent* GetCharacterStatComponent();

private:
	UPROPERTY()
	class ATOPlayerController* TOPlayerController2;

	// Damage 
public:
	virtual float TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, AActor* DamageCauser) override;

private:
	UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly, Category = Attack, Meta = (AllowPrivateAccess = true))
	float AttackRange;

	UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly, Category = Attack, Meta = (AllowPrivateAccess = true))
	float AttackRadius;

	void AttackCheck();

	// �κ��丮
public:
	UPROPERTY(VisibleAnywhere, Category = UI)
	class UWidgetComponent* InventoryWidget;

	void OpenInventory();
	void CloseInventory();

	// ������
public:
	void ItemUse(float HP);
	void ItemPickUp(ATOItem* Item);

	// ��ȣ�ۿ�
public:
	void Interaction();
	void InteractionUI();

private:
	// ��ȣ�ۿ� Ÿ�� ����
	bool Lock;
	bool Level2Field1On;
	bool Level2_FightOn;
	class ATOItem* LockItem;
	class ATOCheckPoint* LockCheckPoint;
	class ATOChest* LockChest;
	class ATOTeleport* LockTeleport;
	class ATONPC* LockNPC;
	class ATOFlower* LockFlower;
	class ATOClearPoint* LockClear;
	class ALevel2Field1* LockLevel2Field1;
	class ATOLevel2_Fight* LockLevel2_Fight;

	// Script
public:
	void Script();

	// Setting UI
public:
	void SettingUI();

	bool IsSettingUIOpened;
};
