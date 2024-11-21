// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "ProjectN.h"
#include "GameFramework/Character.h"
#include "NPlayerController.h"
#include "NBottle.h"
#include "NCharacter.generated.h"

UCLASS()
class PROJECTN_API ANCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ANCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	virtual void PostInitializeComponents() override;

private:
	ANPlayerController* Controller;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

public:
	// �� �ڵ���� ĳ���� �׽�Ʈ �ڵ���. ���ſ���
	UPROPERTY(VisibleAnywhere, Category = TEST)
		UStaticMeshComponent* MeshComponent;
	// �� �ڵ���� ĳ���� �׽�Ʈ �ڵ���. ���ſ���

	// StatComponent
	UPROPERTY(VisibleAnywhere, Category = Stat)
		class UNCharacterStatComponent* CharacterStat;

	void SetDamage(int32 joy, int32 sad, int32 fear, int32 anger);
	void SetDamage1();
	// ī�޶� ������ �׽�Ʈ �Լ�
	void Test1(void);
	void Test2(void);

	// ���� �ý��� �׽�Ʈ �ڵ�
	UPROPERTY(VisibleAnywhere, Category = System)
	class UNGameSystemComponent* GameSystem;
	// ���� �ý��� �׽�Ʈ �ڵ�

private:
	int32 SaveProgress;

public:
	void UpDown(float NewAxisValue);
	void LeftRight(float NewAxisValue);
	
private:
	UPROPERTY()
		class UNAnimInstance* NAnim;

	bool CanMoving;
	FVector DirectionToMove = FVector::ZeroVector;

//FootStep
private:
	class USoundCue* DirtSoundCue;

// ��ȣ�ۿ�
public:
	void Interaction();
	void InteractionLock();
	void Q();

private:
	bool Lock;
	class ANBottle* LockBottle;
	class ANBottle* PreBottle;
	class ANCoconut* LockCoconut;
	class ANExercise* LockExercise;
	class ANWhistle* LockWhistle;

	bool IsCoconut = false;
	bool CanCoconut = false;
	bool CanExercise = false;
	bool CanWhistle = false;

// ��ũ��Ʈ
public:
	void ScriptOpen();
	void ScriptClose();
	void ScriptSet(FString ScriptName);

private:
	UPROPERTY()
		class UNScript* ScriptWidget = nullptr;

	bool IsScriptOpened;
	struct FScript* CurrentScript = nullptr;
	int32 RecentBottle = 0;
	int32 MainXCount = 0;

// Tab
public:
	void TabUI(void);
private:
	UPROPERTY()
	class UNTabUI* TabWidget = nullptr;
	bool IsTabUIOpened;

// ESC
public:
	void ESCUI(void);

// Bottle ����� Ÿ�̸�
public:
	FTimerHandle BottleSpawnTimeHandle = { };

// ����
public:
	void CollisionFunction();

// �б�
public:
	void ResetActivityInfo();
private:
	int32 branch = 0;
};

