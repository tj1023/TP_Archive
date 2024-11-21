// Fill out your copyright notice in the Description page of Project Settings.


#include "NCharacter.h"
#include "EngineUtils.h"
#include "Sound/SoundCue.h"
#include "NCharacterStatComponent.h"
#include "NAnimInstance.h"
#include "NPlayerState.h"
#include "NBottle.h"
#include "NPlayerController.h"
#include "NScript.h"
#include "NTabUI.h"
#include "NGameSystemComponent.h"
#include "NHUDWidget.h"
#include "NPlayerState.h"
#include "NCoconut.h"
#include "NExercise.h"
#include "NWhistle.h"
#include "Engine/World.h"
#include "GameFramework/PlayerController.h"
#include "GameFramework/SpringArmComponent.h"
#include "DrawDebugHelpers.h"
#include "Camera/CameraActor.h"

enum ProgressNum
{
	TUTORIAL, MAIN, SUB_1, SUB_2, SUB_3, SUB_4, SUB_5, SUB_6, SUB_7, SUB_8, SUB_9, SUB_10, SUB_11, SUB_12, SUB_13, SUB_14, SUB_15, SUB_16, SUB_17, SUB_18, SUB_19, SUB_20, SUB_21, SUB_22, SUB_23, SUB_24, SUB_25, SUB_26
};

#define TUTORIAL_LEN 4
#define EARLY_STORY_SIZE 3

// Sets default values
ANCharacter::ANCharacter()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	MeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshComponent"));
	MeshComponent->SetupAttachment(GetRootComponent());

	static ConstructorHelpers::FObjectFinder<USkeletalMesh> SK_Default(TEXT("/Game/Assets/Character/NCharacter.NCharacter"));
	if (SK_Default.Succeeded())
	{
		GetMesh()->SetSkeletalMesh(SK_Default.Object);
		GetMesh()->SetRelativeLocationAndRotation(FVector(0.0f, 0.0f, -88.0f), FRotator(0.0f, -90.f, 0.0f));
		GetMesh()->SetWorldScale3D(FVector(1.5f, 1.5f, 1.5f));
	}

	GetMesh()->SetAnimationMode(EAnimationMode::AnimationBlueprint);

	static ConstructorHelpers::FClassFinder<UAnimInstance> ANIM(TEXT("/Game/Assets/Character/NCharacter_BP.NCharacter_BP_C"));
	if (ANIM.Succeeded())
	{
		GetMesh()->SetAnimInstanceClass(ANIM.Class);
	}

	static ConstructorHelpers::FObjectFinder<USoundCue> DirtSound(TEXT("/Game/Assets/Sound/SQ_Dirt_Walk.SQ_Dirt_Walk"));
	if (DirtSound.Succeeded())
	{
		DirtSoundCue = DirtSound.Object;
	}

	CanMoving = true;

	//StatComponent
	CharacterStat = CreateDefaultSubobject<UNCharacterStatComponent>(TEXT("CHARACTERSTAT"));

	// PostInitializeComponents() �Լ��� �־�� �ϴ� �ڵ�
	CharacterStat->EmotionZero.AddLambda([this]() -> void {

		FTimerHandle Delay = { };

		GetWorld()->GetTimerManager().SetTimer(Delay, FTimerDelegate::CreateLambda([&]() {

			if (CharacterStat->GetEmotion(0) == 0)
			{
				Controller->ShowDieUI(0);
			}
			else if (CharacterStat->GetEmotion(0) == 100)
			{
				Controller->ShowDieUI(4);
			}
			else if (CharacterStat->GetEmotion(1) == 0)
			{
				Controller->ShowDieUI(1);
			}
			else if (CharacterStat->GetEmotion(1) == 100)
			{
				Controller->ShowDieUI(5);
			}
			else if (CharacterStat->GetEmotion(2) == 0)
			{
				Controller->ShowDieUI(2);
			}
			else if (CharacterStat->GetEmotion(2) == 100)
			{
				Controller->ShowDieUI(6);
			}
			else if (CharacterStat->GetEmotion(3) == 0)
			{
				Controller->ShowDieUI(3);
			}
			else if (CharacterStat->GetEmotion(3) == 100)
			{
				Controller->ShowDieUI(7);
			}

			}), 4.5, false);

		NLOG(Warning, TEXT("EmotionIsZero"));
		NAnim = Cast<UNAnimInstance>(GetMesh()->GetAnimInstance());
		NAnim->SetDeadAnim();
		SetActorEnableCollision(false);

		ResetActivityInfo();
		});

	GameSystem = CreateDefaultSubobject<UNGameSystemComponent>(TEXT("GAMESYSTEM"));

	SaveProgress = 1;


	// ��ȣ�ۿ�
	Lock = false;
	LockBottle = nullptr;
	LockCoconut = nullptr;
	LockExercise = nullptr;
	LockWhistle = nullptr;

	// ��ũ��Ʈ
	IsScriptOpened = false;

	// TabUI
	IsTabUIOpened = false;
}

void ANCharacter::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	NAnim = Cast<UNAnimInstance>(GetMesh()->GetAnimInstance());

	NAnim->Footstep.AddLambda([this]() -> void {
		UGameplayStatics::PlaySoundAtLocation(GetWorld(), Cast<USoundBase>(DirtSoundCue), FVector(GetActorLocation().X, GetActorLocation().Y, GetActorLocation().Z - 150.0f));
		});
}

// Called when the game starts or when spawned
void ANCharacter::BeginPlay()
{
	Super::BeginPlay();

	GetCharacterMovement()->bUseControllerDesiredRotation = true;
	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 720.0f, 0.0f);
	GetCharacterMovement()->MaxWalkSpeed = 300.0f;

	Controller = Cast<ANPlayerController>(GetWorld()->GetFirstPlayerController());
	Controller->GetHUDWidget()->BindCharacterStat(CharacterStat);
	Controller->GetHUDWidget()->UpdateCharacterStat();
	Controller->GetHUDWidget()->UpdateStatusEffect();

	auto NGameSystemComponent = FindComponentByClass<UNGameSystemComponent>();
	NGameSystemComponent->StartSystem(CharacterStat);

}

// Called every frame
void ANCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (DirectionToMove.SizeSquared() > 0.0f)
	{
		GetController()->SetControlRotation(FRotationMatrix::MakeFromX(DirectionToMove).Rotator());
		AddMovementInput(DirectionToMove);
	}

	// ��ȣ�ۿ� ��� Ž��
	InteractionLock();

	// ���� ��ġ Ž��
	CollisionFunction();
}

// Called to bind functionality to input
void ANCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis(TEXT("UpDown"), this, &ANCharacter::UpDown);
	PlayerInputComponent->BindAxis(TEXT("LeftRight"), this, &ANCharacter::LeftRight);
	// ��ȣ�ۿ�
	PlayerInputComponent->BindAction(TEXT("Interaction"), EInputEvent::IE_Pressed, this, &ANCharacter::Interaction);
	PlayerInputComponent->BindAction(TEXT("Q"), EInputEvent::IE_Pressed, this, &ANCharacter::Q);
	// Tab
	PlayerInputComponent->BindAction(TEXT("Tab"), EInputEvent::IE_Pressed, this, &ANCharacter::TabUI);
	// test code
	PlayerInputComponent->BindAction(TEXT("TEST1"), EInputEvent::IE_Pressed, this, &ANCharacter::Test1);
	PlayerInputComponent->BindAction(TEXT("TEST2"), EInputEvent::IE_Pressed, this, &ANCharacter::SetDamage1);
	// ESC
	PlayerInputComponent->BindAction(TEXT("ESC"), EInputEvent::IE_Pressed, this, &ANCharacter::ESCUI);
}

/*
*  ĳ���� �̵�
*/
void ANCharacter::UpDown(float NewAxisValue)
{
	NAnim = Cast<UNAnimInstance>(GetMesh()->GetAnimInstance());
	if (NAnim->GetIsDead())
		return;
	if (NAnim->GetExercise())
		return;
	if (NAnim->GetWhistle())
		return;
	if (CanMoving)
	{
		DirectionToMove.X = NewAxisValue;
	}
}

void ANCharacter::LeftRight(float NewAxisValue)
{
	NAnim = Cast<UNAnimInstance>(GetMesh()->GetAnimInstance());
	if (NAnim->GetIsDead())
		return;
	if (NAnim->GetExercise())
		return;
	if (NAnim->GetWhistle())
		return;
	if (CanMoving)
	{
		DirectionToMove.Y = NewAxisValue;
	}
}

/*
* ��ȣ�ۿ�
*/
void ANCharacter::Q()
{
	if (IsScriptOpened) {
		const auto NPlayerController = Cast<ANPlayerController>(GetWorld()->GetFirstPlayerController());
		CurrentScript = NPlayerController->GetScriptWidget()->GetCurrentScript();

		// TUTORIAL OR OTHER
		if (CharacterStat->GetProgress(TUTORIAL) < TUTORIAL_LEN)
		{

			CharacterStat->SetProgress(CurrentScript->NextScriptNum1, TUTORIAL);
		}
		else
		{
			if (RecentBottle == MAIN)
			{
				CharacterStat->SetProgress(CurrentScript->NextScriptNum1, RecentBottle);
			}
			else
			{
				// -1 �� �ƴ� ��� ����, -1 �ϰ�� ���� Script�� ���൵�� ������.
				if (CurrentScript->NextScriptNum1 != -1)
				{
					CharacterStat->SetProgress(CurrentScript->NextScriptNum1, RecentBottle);
				}
			}
		}

		// ���� ��ġ ����		
		SetDamage(CurrentScript->Joy1, CurrentScript->Sad1, CurrentScript->Anger1, CurrentScript->Fear1);
		// ���� ��ũ��Ʈ ���� ����
		CharacterStat->SetSurvivalDays(CharacterStat->GetSurvivalDays() + 1);
		Controller->GetHUDWidget()->UpdateScriptCount(CharacterStat->GetSurvivalDays());

		ScriptClose();
		IsScriptOpened = false;
	}
}

void ANCharacter::Interaction()
{
	if (!IsScriptOpened) {
		if (LockBottle != nullptr && LockBottle != PreBottle)
		{
			switch (LockBottle->GetValue())
			{
			case TUTORIAL:
				ScriptSet("T" + FString::FromInt(CharacterStat->GetProgress(TUTORIAL)));
				break;

			case MAIN:
				ScriptSet("M" + FString::FromInt(CharacterStat->GetProgress(MAIN)));
				RecentBottle = MAIN;
				MainXCount = 0;
				break;

			default:
				ScriptSet("S" + FString::FromInt(LockBottle->GetValue() - 2) + "-" + FString::FromInt(CharacterStat->GetProgress(LockBottle->GetValue())));
				RecentBottle = LockBottle->GetValue();
				MainXCount++;
				break;
			}

			ScriptOpen();
			IsScriptOpened = true;

			// ��ũ��Ʈ �ٽ� ���� ����
			PreBottle = LockBottle;

			Lock = false;
			LockBottle = nullptr;

			return;
		}
		// ���ڳ� �Ա�
		else if (LockCoconut != nullptr)
		{
			// ���������� ���� 50�� ������ �ִ� 10 ����
			for (int i = 0; i < 4; i++) {
				if (CharacterStat->GetEmotion(i) <= 40)
					CharacterStat->ChangeEmotion(10, i);
				else if (CharacterStat->GetEmotion(i) >= 60)
					CharacterStat->ChangeEmotion(-10, i);
				else
					CharacterStat->SetEmotion(50, i);
			}
			LockCoconut->Destroy();
			Lock = false;
			LockCoconut = nullptr;
			IsCoconut = false;
			return;
		}
		// � ���
		else if (LockExercise != nullptr)
		{
			NLOG(Warning, TEXT("Exercise Interaction"));
			// animation play
			NAnim->SetExercise();
			FTimerHandle ExerciseTimeHandle = { };
			GetWorld()->GetTimerManager().SetTimer(ExerciseTimeHandle, FTimerDelegate::CreateLambda([&]() {NAnim->SetExercise(); }), 2.5, false);

			// ���������� ���� 50�� ������ �ִ� 10 ����
			for (int i = 0; i < 4; i++) {
				if (CharacterStat->GetEmotion(i) <= 40)
					CharacterStat->ChangeEmotion(10, i);
				else if (CharacterStat->GetEmotion(i) >= 60)
					CharacterStat->ChangeEmotion(-10, i);
				else
					CharacterStat->SetEmotion(50, i);
			}
			LockExercise->Destroy();
			Lock = false;
			LockExercise = nullptr;
			CanExercise = false;
			return;
		}
		// ���Ķ� ���
		else if (LockWhistle != nullptr)
		{
			NLOG(Warning, TEXT("Whistle Interaction"));
			// animation play
			NAnim->SetWhistle();
			FTimerHandle WhistleTimeHandle = { };
			GetWorld()->GetTimerManager().SetTimer(WhistleTimeHandle, FTimerDelegate::CreateLambda([&]() {NAnim->SetWhistle(); }), 2.5, false);

			// ���������� ���� 50�� ������ �ִ� 10 ����
			for (int i = 0; i < 4; i++) {
				if (CharacterStat->GetEmotion(i) <= 40)
					CharacterStat->ChangeEmotion(10, i);
				else if (CharacterStat->GetEmotion(i) >= 60)
					CharacterStat->ChangeEmotion(-10, i);
				else
					CharacterStat->SetEmotion(50, i);
			}
			LockWhistle->Destroy();
			Lock = false;
			LockWhistle = nullptr;
			CanWhistle = false;
			return;
		}
		// ���ڳ� ����
		else
		{
			if (!IsCoconut && CanCoconut) {
				FVector tree = FVector(900, 25, 0);
				if ((GetActorLocation() - tree).Size() <= 175) {
					GetWorld()->SpawnActor<ANCoconut>(FVector(830, -100, 450), FRotator::ZeroRotator);
					IsCoconut = true;
					//CanCoconut = false;
				}
			}
		}
	}
	else
	{
		const auto NPlayerController = Cast<ANPlayerController>(GetWorld()->GetFirstPlayerController());
		CurrentScript = NPlayerController->GetScriptWidget()->GetCurrentScript();

		// TUTORIAL OR OTHER
		if (CharacterStat->GetProgress(TUTORIAL) < TUTORIAL_LEN)
		{

			CharacterStat->SetProgress(CurrentScript->NextScriptNum2, TUTORIAL);
		}
		else
		{
			if (RecentBottle == MAIN)
			{
				CharacterStat->SetProgress(CurrentScript->NextScriptNum2, RecentBottle);
			}
			else
			{
				// -1 �� �ƴ� ��� ����, -1 �ϰ�� ���� Script�� ���൵�� ������.
				if (CurrentScript->NextScriptNum2 != -1)
				{
					CharacterStat->SetProgress(CurrentScript->NextScriptNum2, RecentBottle);
				}
			}
		}

		// ���� ��ġ ����
		SetDamage(CurrentScript->Joy2, CurrentScript->Sad2, CurrentScript->Anger1, CurrentScript->Fear1);
		// ���� ��ũ��Ʈ ���� ����
		CharacterStat->SetSurvivalDays(CharacterStat->GetSurvivalDays() + 1);
		Controller->GetHUDWidget()->UpdateScriptCount(CharacterStat->GetSurvivalDays());

		ScriptClose();
		IsScriptOpened = false;
	}
}

void ANCharacter::InteractionLock()
{
	// Bottle ��ȣ�ۿ�
	for (ANBottle* Bottle : TActorRange<ANBottle>(GetWorld()))
	{
		if ((GetActorLocation() - Bottle->GetActorLocation()).Size() <= 300 && !Lock)
		{
			Lock = true;
			LockBottle = Bottle;
			return;
		}
	}
	if ((LockBottle != nullptr) && (GetActorLocation() - LockBottle->GetActorLocation()).Size() > 300)
	{
		Lock = false;
		LockBottle = nullptr;
	}

	// Coconut ��ȣ�ۿ�
	for (ANCoconut* Coconut : TActorRange<ANCoconut>(GetWorld()))
	{
		if ((GetActorLocation() - Coconut->GetActorLocation()).Size() <= 150 && !Lock)
		{
			Lock = true;
			LockCoconut = Coconut;
			return;
		}
	}
	if ((LockCoconut != nullptr) && (GetActorLocation() - LockCoconut->GetActorLocation()).Size() > 300)
	{
		Lock = false;
		LockCoconut = nullptr;
	}

	// � ��ȣ�ۿ�
	for (ANExercise* Exercise : TActorRange<ANExercise>(GetWorld()))
	{
		if ((GetActorLocation() - Exercise->GetActorLocation()).Size() <= 150 && !Lock)
		{
			Lock = true;
			LockExercise = Exercise;
			return;
		}
	}
	if ((LockExercise != nullptr) && (GetActorLocation() - LockExercise->GetActorLocation()).Size() > 300)
	{
		Lock = false;
		LockExercise = nullptr;
	}

	// ���Ķ� ��ȣ�ۿ�
	for (ANWhistle* Whistle : TActorRange<ANWhistle>(GetWorld()))
	{
		if ((GetActorLocation() - Whistle->GetActorLocation()).Size() <= 150 && !Lock)
		{
			Lock = true;
			LockWhistle = Whistle;
			return;
		}
	}
	if ((LockWhistle != nullptr) && (GetActorLocation() - LockWhistle->GetActorLocation()).Size() > 300)
	{
		Lock = false;
		LockWhistle = nullptr;
	}
}

// ���� ��ġ ����
void ANCharacter::SetDamage(int32 joy, int32 sad, int32 fear, int32 anger)
{
	CharacterStat->ChangeEmotion(joy, 0);
	CharacterStat->ChangeEmotion(sad, 1);
	CharacterStat->ChangeEmotion(fear, 2);
	CharacterStat->ChangeEmotion(anger, 3);
	NLOG(Warning, TEXT("E Emotion is %d, %d, %d, %d"), CharacterStat->GetEmotion(0), CharacterStat->GetEmotion(1), CharacterStat->GetEmotion(2), CharacterStat->GetEmotion(3));
}
// test code
void ANCharacter::SetDamage1()
{
	CharacterStat->ChangeEmotion(-30, 3);

	NLOG(Warning, TEXT("E Emotion is %d, %d, %d, %d"), CharacterStat->GetEmotion(0), CharacterStat->GetEmotion(1), CharacterStat->GetEmotion(2), CharacterStat->GetEmotion(3));
}

/*
* ��ũ��Ʈ
*/
void ANCharacter::ScriptOpen()
{
	NLOG(Warning, TEXT("Selected Script is this! -> %d"), RecentBottle);

	const auto NPlayerController = Cast<ANPlayerController>(GetWorld()->GetFirstPlayerController());
	NPlayerController->ShowScript();

	CanMoving = false;
}

void ANCharacter::ScriptClose()
{
	const auto NPlayerController = Cast<ANPlayerController>(GetWorld()->GetFirstPlayerController());
	NPlayerController->CloseScript();

	CanMoving = true;

	// �� ������
	if (CharacterStat->GetProgress(TUTORIAL) < TUTORIAL_LEN)
	{
		if (CharacterStat->GetProgress(TUTORIAL) % 2 == 0)
		{
			GameSystem->SpawnTutorialBottle(0);
		}
		else
		{
			GameSystem->SpawnTutorialBottle(1);
		}
	}
	else
	{
		// ���� ��ũ��Ʈ�� ����, Ư��Ȱ�� �ر�
		if (branch == 1) {
			if (MainXCount == 0)
			{
				// 1�� �� ���� - �� ������ 1�ܰ� �غ�


				// ���ڳ� ��� Ȱ��ȭ
				
			}
			else if (MainXCount == 2)
			{
				// �ĵ��Ҹ� ��� Ȱ��ȭ
				

			}
			else if(MainXCount == 6) {
				GameSystem->FixValue(1);
				GameSystem->DestroyOtherBottle();
			}
		}
		else if (branch == 2) {
			if (MainXCount == 0)
			{
				// 2�� �� ���� - �� ������ 2�ܰ� �غ�, ���� �ر�
				for (TActorIterator<AActor> Actor(GetWorld()); Actor; ++Actor)
				{
					if (Actor->ActorHasTag("blockingBox1"))
					{
						Actor->Destroy();
					}
				}
				NLOG(Warning, TEXT("TriggerBox1 deleted!!!"));

			}
			else if (MainXCount == 2)
			{
				// 2�б� ���� 2ȸ ���� �� � �ر�
				CanExercise = true;
				ANExercise* SpawnedActor = (ANExercise *)GetWorld()->SpawnActor<ANExercise>(FVector(460.0f, 130.0f, 190.0f), FRotator::ZeroRotator);
				NLOG(Warning, TEXT("Exercise Open"));
			}
			else if (MainXCount == 4)
			{
				// ���Ķ� ��� ����
				CanWhistle = true;
				ANWhistle* SpawnedActor = (ANWhistle*)GetWorld()->SpawnActor<ANWhistle>(FVector(650.0f, -300.0f, 100.0f), FRotator::ZeroRotator);
				NLOG(Warning, TEXT("Whistle Open"));
			}
			else if(MainXCount == 8) {
				GameSystem->FixValue(1);
				GameSystem->DestroyOtherBottle();
			}
		}
		else if (branch == 3) {
			if (MainXCount == 0)
			{
				// ���� ���� 1��
				std::srand(static_cast<unsigned int>(std::time(0)));
				CharacterStat->SetStatusEffect(true, std::rand() % 4);
				Controller->GetHUDWidget()->UpdateStatusEffect();
				NLOG(Warning, TEXT("Random statusEffect On"));
			}
			else if (MainXCount == 1)
			{
				// �г�Ƽ ���� 1��
				std::srand(static_cast<unsigned int>(std::time(0)));
				CharacterStat->SetStatusDeffect(true, std::rand() % 4);
				NLOG(Warning, TEXT("Random status Deffect On 1"));
			}
			else if (MainXCount == 4)
			{
				// �г�Ƽ ���� 1��
				int emotionNum = std::rand() % 4;
				while (!CharacterStat->GetStatusDeffect(emotionNum))
					emotionNum = std::rand() % 4;

				CharacterStat->SetStatusDeffect(true, emotionNum);
				NLOG(Warning, TEXT("Random status Deffect On 2"));
			}
			else if (MainXCount == 6) {
				GameSystem->FixValue(1);
				GameSystem->DestroyOtherBottle();
			}
		}

		// ��ũ��Ʈ ����, �� �ϳ��� ������ ��
		CurrentScript = NPlayerController->GetScriptWidget()->GetCurrentScript();
		if (CurrentScript->Fix == 1 || CurrentScript->Fix == 2) {
			GameSystem->FixValue(LockBottle->GetValue());	// �ش� ��ũ��Ʈ ��ȣ �����ͼ� ����
			GameSystem->DestroyOtherBottle();				// ���� �� ����
		}

		// �� �ð��� ��ȯ
		GetWorld()->GetTimerManager().SetTimer(BottleSpawnTimeHandle, FTimerDelegate::CreateLambda([&]() {GameSystem->SpawnBottle(); }), 2.5, false);
	}

	for (int i = 0; i < SCRIPT_LEN; i++)
	{
		NLOG(Warning, TEXT("%d - %d"), i, CharacterStat->GetProgress(i));
	}
	NLOG(Warning, TEXT("current branch : %d"), branch);
	NLOG(Warning, TEXT("MainXCount : %d"), MainXCount);

	// MAIN�� 3 ����ɶ����� ����
	if (CharacterStat->GetProgress(MAIN) / 3 == SaveProgress && CharacterStat->GetProgress(MAIN) != 0 && CharacterStat->GetProgress(TUTORIAL) == TUTORIAL_LEN)
	{
		auto NPlayerState = Cast<ANPlayerState>(GetPlayerState());

		NPlayerState->SavePlayerData();

		NLOG(Warning, TEXT("Save COMPLETE"));

		SaveProgress++;
	}

	// ���� ���� �� �� ������
	for (ANBottle* Bottle : TActorRange<ANBottle>(GetWorld()))
		if (Bottle != LockBottle && Bottle->GetValue() != 0)
			Bottle->GoDown();
	LockBottle->GoBack();

	// �б� ����
	switch (CharacterStat->GetProgress(MAIN))
	{
	case 0:
		if (CharacterStat->GetProgress(0) == 4 && branch == 0) {
			branch = 1;
			ResetActivityInfo();
		}
		break;
	case 3:
		branch = 2;
		ResetActivityInfo();
		break;
	case 6:
		branch = 3;
		ResetActivityInfo();
		break;
	default:
		break;
	}
}

void ANCharacter::ScriptSet(FString ScriptName)
{
	const auto NPlayerController = Cast<ANPlayerController>(GetWorld()->GetFirstPlayerController());
	NPlayerController->SetScript(ScriptName);
}

// Tab
void ANCharacter::TabUI(void)
{
	const auto NPlayerController = Cast<ANPlayerController>(GetWorld()->GetFirstPlayerController());

	//NLOG(Warning, TEXT("Input Tab"));
	if (IsTabUIOpened == false)
	{
		NPlayerController->ShowTab();
		IsTabUIOpened = true;
	}
	else
	{
		NPlayerController->CloseTab();
		IsTabUIOpened = false;
	}
}

// ESC
void ANCharacter::ESCUI(void)
{
	const auto NPlayerController = Cast<ANPlayerController>(GetWorld()->GetFirstPlayerController());
	NPlayerController->ShowESCUI();
}

// ���� ����
void ANCharacter::Test1(void)
{
	NLOG(Warning, TEXT("Test1"));

	// �����̻� ȿ�� on�� ���ؼ� �Ʒ� ������ �߰��ؾ� ��.
	CharacterStat->SetStatusEffect(true, 3);
	Controller->UpdateUI();

	// ��Ȱ��ȭ - ���� ����
	/*AActor* CurrentViewTarget = Controller->GetViewTarget();
	if (CurrentViewTarget && CurrentViewTarget->IsA<ACameraActor>())
	{
		ACameraActor* WorldMapCamera = Cast<ACameraActor>(CurrentViewTarget);
		if (WorldMapCamera)
		{
			WorldMapCamera->SetActorLocation(FVector(-521.0f, 0.0f, 1340.0f));
		}
	}*/
}

// ��Ȱ��ȭ - ���� ����
void ANCharacter::Test2(void)
{
	NLOG(Warning, TEXT("Test2"));

	//AActor* CurrentViewTarget = Controller->GetViewTarget();
	//if (CurrentViewTarget && CurrentViewTarget->IsA<ACameraActor>())
	//{
	//	ACameraActor* WorldMapCamera = Cast<ACameraActor>(CurrentViewTarget);
	//	if (WorldMapCamera)
	//	{
	//		WorldMapCamera->SetActorLocation(FVector(-921.0f, 0.0f, 1740.0f));
	//	}
	//}
}



void ANCharacter::CollisionFunction()
{
	FHitResult HitResult;
	FVector StartLocation = GetActorLocation() + FVector(0.0f, 0.0f, 100.0f);
	FVector EndLocation = StartLocation + FVector(0.0f, 0.0f, -200.0f);

	FCollisionQueryParams CollisionParams;
	CollisionParams.AddIgnoredActor(this);

	// Perform the line trace
	bool bHit = GetWorld()->LineTraceSingleByChannel(HitResult, StartLocation, EndLocation, ECC_Visibility, CollisionParams);

	if (bHit)
	{
		AActor* HitActor = HitResult.GetActor();

		ECollisionChannel CollisionChannel = UCollisionProfile::Get()->ConvertToCollisionChannel(ECollisionEnabled::QueryOnly, ECC_GameTraceChannel1);

		UPrimitiveComponent* HitComponent = HitResult.GetComponent();
		FCollisionResponseContainer ResponseContainer = HitComponent->GetCollisionResponseToChannel(ECC_GameTraceChannel1);

		// Ÿ�Կ� ���� �ٸ� ��� ����
		if (ResponseContainer.GetResponse(ECC_GameTraceChannel1) == ECR_Ignore)
		{
			// �� ��� ������
			NAnim->SetLandAnim();

		}
		else if (ResponseContainer.GetResponse(ECC_GameTraceChannel1) == ECR_Block)
		{
			// �ٴ� ��� ���� ��
			NAnim->SetOceanAnim();
		}
		else
		{
			// ����
			UE_LOG(LogTemp, Warning, TEXT("No hit"));
		}
	}
}

void ANCharacter::ResetActivityInfo() {
	MainXCount = 0;
	CanCoconut = true;
	if (branch >= 3) {
		CanExercise = true;
		CanWhistle = true;
	}
}