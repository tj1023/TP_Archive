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
	// 이 코드들은 캐릭터 테스트 코드임. 제거예정
	UPROPERTY(VisibleAnywhere, Category = TEST)
		UStaticMeshComponent* MeshComponent;
	// 이 코드들은 캐릭터 테스트 코드임. 제거예정

	// StatComponent
	UPROPERTY(VisibleAnywhere, Category = Stat)
		class UNCharacterStatComponent* CharacterStat;

	void SetDamage(int32 joy, int32 sad, int32 fear, int32 anger);
	void SetDamage1();
	// 카메라 움직임 테스트 함수
	void Test1(void);
	void Test2(void);

	// 게임 시스템 테스트 코드
	UPROPERTY(VisibleAnywhere, Category = System)
	class UNGameSystemComponent* GameSystem;
	// 게임 시스템 테스트 코드

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

// 상호작용
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

// 스크립트
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

// Bottle 재생성 타이머
public:
	FTimerHandle BottleSpawnTimeHandle = { };

// 수영
public:
	void CollisionFunction();

// 분기
public:
	void ResetActivityInfo();
private:
	int32 branch = 0;
};

