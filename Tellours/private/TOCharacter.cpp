


// Fill out your copyright notice in the Description page of Project Settings.

#include "TOCharacter.h"
#include "Components/WidgetComponent.h"
#include "TOAnimInstance.h"
#include "TOWeapon.h"
#include "TOPlayerController.h"
#include "TOCharacterStatComponent.h"
#include "TOCharacterWidget.h"
#include "DrawDebugHelpers.h"
#include "TOItem.h"
#include "TOPlayerState.h"
#include "EngineUtils.h"
#include "TOCheckPoint.h"
#include "TOChest.h"
#include "TOClearPoint.h"
#include "TOFlower.h"
#include "TOInventory.h"
#include "TOHUDWidget.h"
#include "TOTeleport.h"
#include "PhysicalMaterials/PhysicalMaterial.h"
#include "TONPC.h"
#include "TOEnemySpawner.h"
#include "Level2Field1.h"
#include "TOLevel2_Fight.h"


// Sets default values
ATOCharacter::ATOCharacter()
{
	ABLOG_S(Warning);
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	//ĳ���� ���� �� ī�޶� ����.
	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SPRINGARM"));
	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("CAMERA"));

	SpringArm->SetupAttachment(GetCapsuleComponent());
	Camera->SetupAttachment(SpringArm);

	GetMesh()->SetRelativeLocationAndRotation(FVector(0.0f, 0.0f, -88.0f), FRotator(0.0f, -90.f, 0.0f));
	SpringArm->TargetArmLength = 600.0f;
	SpringArm->SetWorldLocationAndRotation(FVector(0, 0, 70), FRotator(-15.0f, 0.0f, 0.0f));
	ArmLengthTo = 600;

	// �⺻ ����Ī ĳ����.
	static ConstructorHelpers::FObjectFinder<USkeletalMesh> SK_Default(TEXT("/Game/OrcaGamesFullAnimBundle/Demo/Mannequin/Character/Mesh/SK_Mannequin.SK_Mannequin"));
	if (SK_Default.Succeeded())
	{
		GetMesh()->SetSkeletalMesh(SK_Default.Object);
	}

	GetMesh()->SetAnimationMode(EAnimationMode::AnimationBlueprint);

	// �⺻ ����Ī ĳ����.
	static ConstructorHelpers::FClassFinder<UAnimInstance> ANIM_TEST(TEXT("/Game/Tellours/Developer/Animations/TestAnimBlueprint.TestAnimBlueprint_C"));
	if (ANIM_TEST.Succeeded())
	{
		GetMesh()->SetAnimInstanceClass(ANIM_TEST.Class);
	}

	// ��Ʈ�� ��� ����
	SetControlMode(0);

	// ĳ���� ������
	GetCharacterMovement()->JumpZVelocity = 1600.0f;
	GetCharacterMovement()->GravityScale = 4.0f;
	IsDashCoolDown = false;
	CanMovementCancle = false;


	// Dash ���� ������.
	IsDashing = false;

	const ConstructorHelpers::FObjectFinder<UCurveFloat> Curve(TEXT("/Game/Tellours/Developer/TimeLine/CF_Dash.CF_Dash"));

	if (Curve.Succeeded())
	{
		ABLOG(Warning, TEXT("SUCCEEDE"));
		DashCurve = Curve.Object;
	}

	if (DashCurve != nullptr)
	{
		DashTimeLineUpdateDelegate.BindUFunction(this, FName("DashStart"));
		DashTimeLineFinishDelegate.BindUFunction(this, FName("DashEnd"));

		DashTimeline.AddInterpFloat(DashCurve, DashTimeLineUpdateDelegate);
		DashTimeline.SetTimelineFinishedFunc(DashTimeLineFinishDelegate);


		float Min = 0.0f;
		float Max = 0.25f;
		DashCurve->GetTimeRange(Min, Max);
		DashTimeline.SetTimelineLength(Max);
	}

	// ����Ʈ ����
	DashEffect = LoadObject<UNiagaraSystem>(nullptr, TEXT("/Game/BlinkAndDashVFX/VFX_Niagara/NS_Dash_Paladin.NS_Dash_Paladin"));
	ShieldEffect = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("EFFECT"));

	static ConstructorHelpers::FObjectFinder<UParticleSystem> SHIELD_EFFECT(TEXT("/Game/InfinityBladeEffects/Effects/FX_Combat_Base/WeaponCombo/P_Cube_Mesh_Test.P_Cube_Mesh_Test"));
	if (SHIELD_EFFECT.Succeeded())
	{
		ShieldEffect->SetTemplate(SHIELD_EFFECT.Object);

		ShieldEffect->bAutoActivate = false;
		ShieldEffect->SetRelativeScale3D(FVector(0.5f));

		ShieldEffect->SetupAttachment(GetMesh(), FName("Root_Socket"));
	}

	// FootStep ����
	static ConstructorHelpers::FObjectFinder<USoundCue> TileSound(TEXT("/Game/Tellours/Developer/Audio/Footsteps/Tile_Cue.Tile_Cue"));
	if (TileSound.Succeeded())
	{
		TileSoundCue = TileSound.Object;
	}

	static ConstructorHelpers::FObjectFinder<USoundCue> CarpetSound(TEXT("/Game/Tellours/Developer/Audio/Footsteps/Carpet_Cue.Carpet_Cue"));
	if (CarpetSound.Succeeded())
	{
		CarpetSoundCue = CarpetSound.Object;
	}

	static ConstructorHelpers::FObjectFinder<USoundCue> DirtSound(TEXT("/Game/Tellours/Developer/Audio/Footsteps/Dirt_Cue.Dirt_Cue"));
	if (DirtSound.Succeeded())
	{
		DirtSoundCue = DirtSound.Object;
	}

	static ConstructorHelpers::FObjectFinder<USoundCue> GrassSound(TEXT("/Game/Tellours/Developer/Audio/Footsteps/Grass_Cue.Grass_Cue"));
	if (GrassSound.Succeeded())
	{
		GrassSoundCue = GrassSound.Object;
	}

	static ConstructorHelpers::FObjectFinder<USoundCue> RockSound(TEXT("/Game/Tellours/Developer/Audio/Footsteps/Rock_Cue.Rock_Cue"));
	if (RockSound.Succeeded())
	{
		RockSoundCue = RockSound.Object;
	}

	static ConstructorHelpers::FObjectFinder<USoundCue> WoodSound(TEXT("/Game/Tellours/Developer/Audio/Footsteps/Wood_Cue.Wood_Cue"));
	if (WoodSound.Succeeded())
	{
		WoodSoundCue = WoodSound.Object;
	}

	static ConstructorHelpers::FObjectFinder<USoundCue> TileJump(TEXT("/Game/Tellours/Developer/Audio/Footsteps/Tile_Jump_Cue.Tile_Jump_Cue"));
	if (TileJump.Succeeded())
	{
		TileJumpCue = TileJump.Object;
	}

	static ConstructorHelpers::FObjectFinder<USoundCue> CarpetJump(TEXT("/Game/Tellours/Developer/Audio/Footsteps/Carpet_Jump_Cue.Carpet_Jump_Cue"));
	if (CarpetJump.Succeeded())
	{
		CarpetJumpCue = CarpetJump.Object;
	}

	static ConstructorHelpers::FObjectFinder<USoundCue> DirtJump(TEXT("/Game/Tellours/Developer/Audio/Footsteps/Dirt_Jump_Cue.Dirt_Jump_Cue"));
	if (DirtJump.Succeeded())
	{
		DirtJumpCue = DirtJump.Object;
	}

	static ConstructorHelpers::FObjectFinder<USoundCue> GrassJump(TEXT("/Game/Tellours/Developer/Audio/Footsteps/Grass_Jump_Cue.Grass_Jump_Cue"));
	if (GrassJump.Succeeded())
	{
		GrassJumpCue = GrassJump.Object;
	}

	static ConstructorHelpers::FObjectFinder<USoundCue> RockJump(TEXT("/Game/Tellours/Developer/Audio/Footsteps/Rock_Jump_Cue.Rock_Jump_Cue"));
	if (RockJump.Succeeded())
	{
		RockJumpCue = RockJump.Object;
	}

	static ConstructorHelpers::FObjectFinder<USoundCue> WoodJump(TEXT("/Game/Tellours/Developer/Audio/Footsteps/Wood_Jump_Cue.Wood_Jump_Cue"));
	if (WoodJump.Succeeded())
	{
		WoodJumpCue = WoodJump.Object;
	}

	//����
	IsAttacking = false;
	MaxCombo = 3;

	static ConstructorHelpers::FObjectFinder<USoundWave> SWORD_ATTACK(TEXT("/Game/Tellours/Developer/Audio/Sword/Sword_Sound.Sword_Sound"));
	if (SWORD_ATTACK.Succeeded())
	{
		SwordAttack = SWORD_ATTACK.Object;
	}

	//ĳ���� ��ų
	IsSkillUIOpened = false;

	// ĳ���� ����
	CharacterStat = CreateDefaultSubobject<UTOCharacterStatComponent>(TEXT("CHARACTERSTAT"));

	// HP��
	/*HPBarWidget = CreateDefaultSubobject<UWidgetComponent>(TEXT("HPBARWIDGET"));
	HPBarWidget->SetupAttachment(GetMesh());
	HPBarWidget->SetRelativeLocation(FVector(0, 0, 180));
	HPBarWidget->SetWidgetSpace(EWidgetSpace::Screen);
	static ConstructorHelpers::FClassFinder<UUserWidget> UI_HUD(TEXT("/Game/Tellours/Developer/UI/UI_HPBar.UI_HPBar_C"));
	if (UI_HUD.Succeeded())
	{
		HPBarWidget->SetWidgetClass(UI_HUD.Class);
		HPBarWidget->SetDrawSize(FVector2D(150, 50));
	}*/

	// Damager �Է�
	GetCapsuleComponent()->SetCollisionProfileName(TEXT("TOCharacter"));
	AttackRange = 200.0f;
	AttackRadius = 50.0f;

	// SettingUI ����
	IsSettingUIOpened = false;

	// InteractionUI
	Lock = false;
	LockItem = nullptr;
	LockCheckPoint = nullptr;
	LockChest = nullptr;
	LockNPC = nullptr;
	LockClear = nullptr;

	// Inventory
	InventoryWidget = CreateDefaultSubobject<UWidgetComponent>(TEXT("INVENTORYWIGDET"));
	InventoryWidget->SetupAttachment(GetMesh());

	Level2Field1On = false;
	Level2_FightOn = false;
}

// Called when the game starts or when spawned
void ATOCharacter::BeginPlay()
{
	Super::BeginPlay();

	// ���� �߰�
	FName WeaponSocket(TEXT("hand_rSocket"));
	auto CurWeapon = GetWorld()->SpawnActor<ATOWeapon>(FVector(-10.0f, 5.0f, 0.0f), FRotator(-180.0f, 0.0f, -20.0f));
	if (nullptr != CurWeapon)
	{
		ABLOG_S(Warning);
		CurWeapon->AttachToComponent(GetMesh(), FAttachmentTransformRules::SnapToTargetNotIncludingScale, WeaponSocket);
	}

	// ĳ���� ������Ʈ�� HP�� ���� ����
	/*auto CharacterWidget = Cast<UTOCharacterWidget>(HPBarWidget->GetUserWidgetObject());
	if (nullptr != CharacterWidget)
	{
		CharacterWidget->BindCharacterStat(CharacterStat);
	}*/

	TOPlayerController2 = Cast<ATOPlayerController>(GetController());
	TOPlayerController2->GetHUDWidget()->BindCharacterStat(CharacterStat);
}

// Called every frame
void ATOCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	// �ε巯�� ī�޶� ��ȯ
	SpringArm->TargetArmLength = FMath::FInterpTo(SpringArm->TargetArmLength, ArmLengthTo, DeltaTime, 3);

	/*ABLOG(Warning, TEXT("X: %0.0f, Y: %0.0f, Z: %0.0f"), GetActorLocation().X, GetActorLocation().Y, GetActorLocation().Z);*/

	//Dash Ÿ�Ӷ��� ����
	DashTimeline.TickTimeline(DeltaTime);

	if (GetWorld()->GetFirstPlayerController()->GetInputKeyTimeDown(EKeys::LeftMouseButton) > 1.0f)
	{
		IsComboInputOn = true;
	}

	// Interaction UI
	InteractionUI();
}

// Called to bind functionality to input
void ATOCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponentRef = PlayerInputComponent;

	// ĳ���� �̵� ����.
	PlayerInputComponent->BindAxis(TEXT("UpDown"), this, &ATOCharacter::UpDown);
	PlayerInputComponent->BindAxis(TEXT("LeftRight"), this, &ATOCharacter::LeftRight);
	PlayerInputComponent->BindAxis(TEXT("LookUp"), this, &ATOCharacter::LookUp);
	PlayerInputComponent->BindAxis(TEXT("Turn"), this, &ATOCharacter::Turn);
	PlayerInputComponent->BindAction(TEXT("Jump"), EInputEvent::IE_Pressed, this, &ATOCharacter::Jump);
	PlayerInputComponent->BindAction(TEXT("Dash"), EInputEvent::IE_Pressed, this, &ATOCharacter::Dash);
	PlayerInputComponent->BindAction(TEXT("Attack"), EInputEvent::IE_Pressed, this, &ATOCharacter::Attack);
	PlayerInputComponent->BindAction(TEXT("ZoomIn"), EInputEvent::IE_Pressed, this, &ATOCharacter::ZoomIn);
	PlayerInputComponent->BindAction(TEXT("ZoomOut"), EInputEvent::IE_Pressed, this, &ATOCharacter::ZoomOut);

	// ĳ���� SkillTool����
	PlayerInputComponent->BindAction(TEXT("SkillTool"), EInputEvent::IE_Pressed, this, &ATOCharacter::EnableSkillTool);

	// �κ��丮, ������ ���
	PlayerInputComponent->BindAction(TEXT("ItemBox"), EInputEvent::IE_Pressed, this, &ATOCharacter::OpenInventory);
	PlayerInputComponent->BindAction(TEXT("ItemUse"), EInputEvent::IE_Pressed, this, &ATOCharacter::Script);

	// ���� ����
	PlayerInputComponent->BindAction(TEXT("CloseUI"), EInputEvent::IE_Pressed, this, &ATOCharacter::CloseInventory);

	// ��ȣ�ۿ�
	PlayerInputComponent->BindAction(TEXT("Interaction"), EInputEvent::IE_Pressed, this, &ATOCharacter::Interaction);

	// Setting �׽�Ʈ
	PlayerInputComponent->BindAction(TEXT("Setting"), EInputEvent::IE_Pressed, this, &ATOCharacter::SettingUI);
}

void ATOCharacter::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	// ĳ���� �ִϸ��̼� ����
	TOAnim = Cast<UTOAnimInstance>(GetMesh()->GetAnimInstance());
	ABCHECK(nullptr != TOAnim);

	TOAnim->OnMontageEnded.AddDynamic(this, &ATOCharacter::OnAttackMontageEnded);

	TOAnim->OnNextAttackCheck.AddLambda([this]() -> void {
		if (!IsComboInputOn)
		{
			TOAnim->StopAttackMontage();
		}
		else
		{
			IsComboInputOn = false;
			CanMovementCancle = false;
		}
	});

	// ĳ���� ���� �Ҹ� ����
	TOAnim->AttackStart.AddLambda([this]() -> void {
		UGameplayStatics::PlaySoundAtLocation(GetWorld(), Cast<USoundBase>(SwordAttack), FVector(GetActorLocation().X, GetActorLocation().Y, GetActorLocation().Z), 0.5f);
	});

	// ĳ���� Footstep ����
	TOAnim->Footstep.AddLambda([this]() -> void {
		PlayFootstepSound();
	});

	TOAnim->JumpSound.AddLambda([this]() -> void {
		PlayJumpSound();
	});

	// ĳ���� Shield ����
	TOAnim->ShieldEnd.AddLambda([this]() -> void {
		GetCharacterMovement()->MaxWalkSpeed = 600.0f;
	});

	TOAnim->Skill3End.AddLambda([this]() -> void {
		GetCharacterMovement()->MaxWalkSpeed = 600.0f;
	});

	// Damage ���� �Լ�
	//TOAnim->OnAttackHitCheck.AddUObject(this, &ATOCharacter::AttackCheck);

	// HP 0 -> ������
	CharacterStat->OnHPIsZero.AddLambda([this]() -> void {

		ABLOG(Warning, TEXT("OnHPIsZero"));
		TOAnim->SetDeadAnim();
		SetActorEnableCollision(false);

		});
}



/*
*  ĳ���� �̵� �� ī�޶� ����.
*/
void ATOCharacter::UpDown(float NewAxisValue)
{
	if (!IsDashing)
	{
		AddMovementInput(FRotationMatrix(FRotator(0.0f, GetControlRotation().Yaw, 0.0f)).GetUnitAxis(EAxis::X), NewAxisValue);
	}

	if (NewAxisValue != 0)
	{
		if (IsAttacking && CanMovementCancle && TOAnim->IsMontagePlaying(FString("Attack")))
		{
			TOAnim->StopAttackMontage();
			GetCharacterMovement()->MaxWalkSpeed = 600.0f;
		}
	}
}

void ATOCharacter::LeftRight(float NewAxisValue)
{
	if (!IsDashing)
	{
		AddMovementInput(FRotationMatrix(FRotator(0.0f, GetControlRotation().Yaw, 0.0f)).GetUnitAxis(EAxis::Y), NewAxisValue);
	}

	if (NewAxisValue != 0)
	{
		if (IsAttacking && CanMovementCancle && TOAnim->IsMontagePlaying(FString("Attack")))
		{
			TOAnim->StopAttackMontage();
			GetCharacterMovement()->MaxWalkSpeed = 600.0f;
		}
	}
}

void ATOCharacter::Jump()
{
	if (!IsDashing && !IsAttacking)
	{
		Super::Jump();
	}
}

void ATOCharacter::LookUp(float NewAxisValue)
{
	AddControllerPitchInput(NewAxisValue);
}

void ATOCharacter::Turn(float NewAxisValue)
{
	AddControllerYawInput(NewAxisValue);
}

void ATOCharacter::ZoomIn()
{
	if (ArmLengthTo >= 200)
		ArmLengthTo -= 40;
}

void ATOCharacter::ZoomOut()
{
	if (ArmLengthTo <= 1200)
		ArmLengthTo += 40;
}

void ATOCharacter::SetControlMode(int32 ControlMode)
{
	SpringArm->bUsePawnControlRotation = true;
	SpringArm->bInheritPitch = true;
	SpringArm->bInheritRoll = true;
	SpringArm->bInheritYaw = true;
	SpringArm->bDoCollisionTest = true;
	bUseControllerRotationYaw = false;

	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->bUseControllerDesiredRotation = false;
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 1440.0f, 0.0f);
}

void ATOCharacter::Dash()
{
	if (!GetCharacterMovement()->IsFalling())
	{
		if (!IsDashCoolDown)
		{
			// Line Trace�� ���� ���� Ȯ��
			FVector LineTraceEnd = GetActorLocation() + GetActorRotation().Vector() * 500.0f;

			//DrawDebugLine(
			//	GetWorld(),
			//	GetActorLocation(),
			//	LineTraceEnd,
			//	FColor(255, 0, 0),
			//	false,
			//	10.f,
			//	0.f,
			//	10.f
			//);

			// ����Ʈ���̽�
			FCollisionQueryParams TraceParameters(NAME_None, false, this);

			FHitResult HitResult;

			bool IsHitResult = GetWorld()->LineTraceSingleByChannel(
				HitResult,
				GetActorLocation(),
				LineTraceEnd,
				ECollisionChannel::ECC_GameTraceChannel1,
				TraceParameters
			);

			if (IsHitResult)
			{
				/*ABLOG(Warning, TEXT("HIT!"));*/
				AActor* ActorHit = HitResult.GetActor();

				if (ActorHit)
				{
					float distance = GetDistanceTo(ActorHit);
					ABLOG(Warning, TEXT("Distance : %.2f"), distance);

					UNiagaraComponent* ActiveDashEffect = UNiagaraFunctionLibrary::SpawnSystemAtLocation(GetWorld(), DashEffect, FVector(GetActorLocation()), FRotator(GetActorRotation()), FVector(distance / 1000.0f, 1.0f, 1.0f), true);
				}
			}
			else
			{
				/*ABLOG(Warning, TEXT("NONE"));*/

				UNiagaraComponent* ActiveDashEffect = UNiagaraFunctionLibrary::SpawnSystemAtLocation(GetWorld(), DashEffect, FVector(GetActorLocation()), FRotator(GetActorRotation()), FVector(0.5f, 1.0f, 1.0f), true);
			}

			//WalkSpeed�� ���ӵ��� �ٲپ� Dash�� �����Ѵ�.
			GetCharacterMovement()->MaxWalkSpeed = 2000.0f;
			GetCharacterMovement()->MaxAcceleration = 20000.0f;

			IsDashing = true;

			DashTimeline.PlayFromStart();


			// Dash��Ÿ�� ����.
			/*IsDashCoolDown = true;

			ABLOG(Warning, TEXT("Dash CoolDown Start"));
			GetWorldTimerManager().SetTimer(TimerHandle, FTimerDelegate::CreateLambda([&]()
				{
					ABLOG(Warning, TEXT("Dash CoolDown End"));
					IsDashCoolDown = false;
				}), 5.0f, false);*/


		}
		else
		{
			ABLOG(Warning, TEXT("Dash CoolDown"));
		}

	}
}

void ATOCharacter::DashStart(float Output)
{
	AddMovementInput(GetCapsuleComponent()->GetForwardVector(), 1.0f, false);
}

void ATOCharacter::DashEnd()
{
	GetCharacterMovement()->MaxWalkSpeed = 600.0f;
	GetCharacterMovement()->MaxAcceleration = 2048.0f;

	IsDashing = false;
}



/*
* Footstep
*/
void ATOCharacter::PlayFootstepSound()
{
	FloorHit = FootstepPhysCheck();

	if (FootstepCheck)
	{
		switch (FloorHit.PhysMaterial->SurfaceType)
		{
			case SurfaceType1:
				UGameplayStatics::PlaySoundAtLocation(GetWorld(), Cast<USoundBase>(TileSoundCue), FVector(GetActorLocation().X, GetActorLocation().Y, GetActorLocation().Z - 150.0f));
				break;
			case SurfaceType2:
				UGameplayStatics::PlaySoundAtLocation(GetWorld(), Cast<USoundBase>(CarpetSoundCue), FVector(GetActorLocation().X, GetActorLocation().Y, GetActorLocation().Z - 150.0f));
				break;
			case SurfaceType3:
				UGameplayStatics::PlaySoundAtLocation(GetWorld(), Cast<USoundBase>(DirtSoundCue), FVector(GetActorLocation().X, GetActorLocation().Y, GetActorLocation().Z - 150.0f));
				break;
			case SurfaceType4:
				UGameplayStatics::PlaySoundAtLocation(GetWorld(), Cast<USoundBase>(GrassSoundCue), FVector(GetActorLocation().X, GetActorLocation().Y, GetActorLocation().Z - 150.0f));
				break;
			case SurfaceType5:
				UGameplayStatics::PlaySoundAtLocation(GetWorld(), Cast<USoundBase>(RockSoundCue), FVector(GetActorLocation().X, GetActorLocation().Y, GetActorLocation().Z - 150.0f));
				break;
			case SurfaceType6:
				UGameplayStatics::PlaySoundAtLocation(GetWorld(), Cast<USoundBase>(WoodSoundCue), FVector(GetActorLocation().X, GetActorLocation().Y, GetActorLocation().Z - 150.0f));
				break;
		}
	}
}

void ATOCharacter::PlayJumpSound()
{
	FloorHit = FootstepPhysCheck();

	if (FootstepCheck)
	{
		switch (FloorHit.PhysMaterial->SurfaceType)
		{
		case SurfaceType1:
			UGameplayStatics::PlaySoundAtLocation(GetWorld(), Cast<USoundBase>(TileJumpCue), FVector(GetActorLocation().X, GetActorLocation().Y, GetActorLocation().Z - 150.0f));
			break;
		case SurfaceType2:
			UGameplayStatics::PlaySoundAtLocation(GetWorld(), Cast<USoundBase>(CarpetJumpCue), FVector(GetActorLocation().X, GetActorLocation().Y, GetActorLocation().Z - 150.0f));
			break;
		case SurfaceType3:
			UGameplayStatics::PlaySoundAtLocation(GetWorld(), Cast<USoundBase>(DirtJumpCue), FVector(GetActorLocation().X, GetActorLocation().Y, GetActorLocation().Z - 150.0f));
			break;
		case SurfaceType4:
			UGameplayStatics::PlaySoundAtLocation(GetWorld(), Cast<USoundBase>(GrassJumpCue), FVector(GetActorLocation().X, GetActorLocation().Y, GetActorLocation().Z - 150.0f));
			break;
		case SurfaceType5:
			UGameplayStatics::PlaySoundAtLocation(GetWorld(), Cast<USoundBase>(RockJumpCue), FVector(GetActorLocation().X, GetActorLocation().Y, GetActorLocation().Z - 150.0f));
			break;
		case SurfaceType6:
			UGameplayStatics::PlaySoundAtLocation(GetWorld(), Cast<USoundBase>(WoodJumpCue), FVector(GetActorLocation().X, GetActorLocation().Y, GetActorLocation().Z - 150.0f));
			break;
		}
	}
}

FHitResult ATOCharacter::FootstepPhysCheck()
{
	FCollisionResponseParams ResponseParams;
	FCollisionQueryParams QueryParams = FCollisionQueryParams::DefaultQueryParam;
	QueryParams.bReturnPhysicalMaterial = true;

	FootstepCheck = GetWorld()->LineTraceSingleByChannel(
		FloorHit,
		GetActorLocation(),
		FVector(GetActorLocation().X, GetActorLocation().Y, GetActorLocation().Z - 150.0f),
		ECollisionChannel::ECC_Visibility,
		QueryParams,
		ResponseParams
	);

	//DrawDebugLine(
	//	GetWorld(),
	//	GetActorLocation(),
	//	FVector(GetActorLocation().X, GetActorLocation().Y, GetActorLocation().Z - 150.0f),
	//	FColor(255, 0, 0),
	//	false,
	//	10.f,
	//	0.f,
	//	10.f
	//);

	return FloorHit;
}

/*
* ���� ���� �Լ�
*/
void ATOCharacter::Attack()
{
	if (!TOAnim->GetAir())
	{
		if (IsAttacking)
		{
			ABLOG(Warning, TEXT("SetIsComboInput"));

			GetCharacterMovement()->MaxWalkSpeed = 0.0f;

			IsComboInputOn = true;
		}
		else
		{
			// �ִϸ��̼��� �����Ѵ�
			TOAnim->PlayAttackMontage();

			GetCharacterMovement()->MaxWalkSpeed = 0.0f;

			CanMovementCancle = false;

			IsAttacking = true;
		}
	}
	else
	{
		//UAnimationAsset* test = nullptr;
		//// TEST
		//static ConstructorHelpers::FObjectFinder<UAnimationAsset> AirAttack(TEXT("/Game/Tellours/Developer/Animations/Shield_Blocking.Shield_Blocking"));
		//if (AirAttack.Succeeded())
		//{
		//	test = AirAttack.Object;
		//}

		//GetMesh()->PlayAnimation(test, false);
	}
}

void ATOCharacter::OnAttackMontageEnded(UAnimMontage* Montage, bool bInterrupted)
{
	IsAttacking = false;
}



/*
* Damage
*/
void ATOCharacter::AttackCheck()
{
	GetCharacterMovement()->MaxWalkSpeed = 600.0f;
	CanMovementCancle = true;

	FHitResult HitResult;
	FCollisionQueryParams Params(NAME_None, false, this);
	bool bResult = GetWorld()->SweepSingleByChannel(
		HitResult,
		GetActorLocation(),
		GetActorLocation() + GetActorForwardVector() * AttackRange,
		FQuat::Identity,
		ECollisionChannel::ECC_GameTraceChannel2,
		FCollisionShape::MakeSphere(AttackRadius),
		Params);

#if ENABLE_DRAW_DEBUG
	FVector TraceVec = GetActorForwardVector() * AttackRange;
	FVector Center = GetActorLocation() + TraceVec * 0.5f;
	float HalfHeight = AttackRange * 0.5f + AttackRadius;
	FQuat CapsuleRot = FRotationMatrix::MakeFromZ(TraceVec).ToQuat();
	FColor DrawColor = bResult ? FColor::Green : FColor::Red;
	float DebugLifeTime = 5.0f;

	DrawDebugCapsule(GetWorld(),
		Center,
		HalfHeight,
		AttackRadius,
		CapsuleRot,
		DrawColor,
		false,
		DebugLifeTime);
#endif

	if (bResult)
	{
		if (HitResult.Actor.IsValid())
		{
			ABLOG(Warning, TEXT("Hit Actor Name : %s"), *HitResult.Actor->GetName());

			FDamageEvent DamageEvent;
			HitResult.Actor->TakeDamage(CharacterStat->GetAttack(), DamageEvent, GetController(), this); //GetFinalAttackDamage()
		}
	}
}

UTOCharacterStatComponent* ATOCharacter::GetCharacterStatComponent()
{
	return CharacterStat;
}

float ATOCharacter::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	if (TOAnim->IsMontagePlaying(FString("Shield")))
	{
		TOAnim->SetMontageJump(FString("Shield"));

		return 0.0f;
	}
	else
	{
		// �������� �Դ� �ִϸ��̼� ���
		TOAnim->PlayHitAnimation();

		GetCharacterMovement()->MaxWalkSpeed = 600.0f;

		float FinalDamage = Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);
		ABLOG(Warning, TEXT("Actor : %s took Damage : %f"), *GetName(), FinalDamage);
		CharacterStat->SetDamage(FinalDamage);

		return FinalDamage;
	}
	/*if (CurrentState == ECharacterState::DEAD)
	{
		if (EventInstigator->IsPlayerController())
		{
			auto instigator = Cast<ATOPlayerController>(EventInstigator);
			ABCHECK(nullptr != instigator, 0.0f);
			instigator->NPCKill(this);
		}
	}*/
}



/*
*  ĳ���� ��ų ����
*/
void ATOCharacter::EnableSkillTool()
{
	const auto TOPlayerController = Cast<ATOPlayerController>(GetWorld()->GetPlayerControllerIterator()->Get());
	/*const auto TOPlayerController = Cast<ATOPlayerController>(GetWorld()->GetFirstPlayerController());*/
	SetIsSkillUIOpened();

	if (IsSkillUIOpened)
	{
		TOPlayerController->ShowSkillUI();
	}
	else
	{
		TOPlayerController->RemoveSkillUI();
	}
}

void ATOCharacter::SetIsSkillUIOpened()
{
	IsSkillUIOpened = !IsSkillUIOpened;
}



/*
* �κ��丮
*/
void ATOCharacter::OpenInventory()
{
	ABLOG_S(Warning);

	const auto TOPlayerController = Cast<ATOPlayerController>(GetWorld()->GetPlayerControllerIterator()->Get());
	TOPlayerController->OpenInventoryUI();
}

// ���� ����
void ATOCharacter::CloseInventory()
{
	const auto TOPlayerController = Cast<ATOPlayerController>(GetWorld()->GetPlayerControllerIterator()->Get());
	TOPlayerController->CloseInventoryUI();
}

void ATOCharacter::ItemUse(float HP)
{
	CharacterStat->AddHP(HP);
}



/*
* ������ �ݱ�
*/
void ATOCharacter::ItemPickUp(ATOItem* Item)
{
	ABLOG_S(Warning);
	switch (Item->GetItemType())
	{
	case ItemType::SWORD: {
		CharacterStat->UpgradeAttack(1);
		CharacterStat->AddInventoryItemCount(0);
		break;
	}
	case ItemType::POTION: {
		CharacterStat->SetMP(CharacterStat->GetCurrentMP() + 20);
		CharacterStat->AddInventoryItemCount(1);
		break;
	}
	case ItemType::KEY: {
		CharacterStat->AddInventoryItemCount(2);
		break;
	}
	case ItemType::MAP: {
		CharacterStat->AddInventoryItemCount(3);
		break;
	}
	case ItemType::FLOWER: {
		CharacterStat->AddHP(20);
		break;
	}
	}
	Item->Destroy();
}



/*
* ��ȣ�ۿ�
*/
void ATOCharacter::Interaction()
{
	ABLOG_S(Warning);

	// ������ �ݱ�
	if (LockItem != nullptr)
	{
		ItemPickUp(LockItem);
		Lock = false;
		LockItem->SetInteractionUIVisible(false);
		LockItem = nullptr;
		return;
	}

	// üũ����Ʈ ���̺�
	else if (LockCheckPoint != nullptr)
	{
		auto TOPlayerState = Cast<ATOPlayerState>(GetPlayerState());
		const auto TOPlayerController = Cast<ATOPlayerController>(GetWorld()->GetFirstPlayerController());
		TOPlayerState->SavePlayerData(LockCheckPoint->GetLevel()->GetOuter()->GetName());
		LockCheckPoint->SavedGame();
		TOPlayerController->ShowSaveScriptUI();
		return;
	}

	// ���� ����
	else if (LockChest != nullptr)
	{
		LockChest->ChestOpen(this);
		Lock = false;
		LockChest->SetInteractionUIVisible(false);
		LockChest = nullptr;
		return;
	}

	// Teleport
	else if (LockTeleport != nullptr)
	{
		Lock = false;
		LockTeleport->SetInteractionUIVisible(false);
		LockTeleport->Teleport();
		LockTeleport = nullptr;
		return;
	}

	// NPC
	else if (LockNPC != nullptr)
	{
		// ����Ʈ ����
		if(!(LockNPC->GetQuestClear()))
		{
			Lock = false;
			LockNPC->SetInteractionUIVisible(false);
			LockNPC->SetQuestProgress(true);

			ATOEnemySpawner* EnemySpawner = (ATOEnemySpawner*)GetWorld()->SpawnActor<ATOEnemySpawner>(GetActorLocation(), FRotator::ZeroRotator);
			EnemySpawner->SetSpawnType(EnemyType::WOLF);
			EnemySpawner->SetSpawnNum(4);
			EnemySpawner->SetMotherNPC(LockNPC);

			LockNPC = nullptr;

			return;
		}
		// ����Ʈ ����
		else
		{
			Lock = false;
			LockNPC->SetInteractionUIVisible(false);
			LockNPC->SetQuestProgress(true);

			LockNPC->SetQuestProgress(false);
			LockNPC->QuestReward();

			LockNPC = nullptr;

			return;
		}
	}

	// ClearPoint
	else if (LockClear != nullptr)
	{
		Lock = false;
		LockClear->SetInteractionUIVisible(false);
		LockClear->CheckPointCondition();
		LockClear = nullptr;
		return;
	}

	// �׸�2 Flower
	else if (LockFlower != nullptr)
	{
		Lock = false;
		LockFlower->SetInteractionUIVisible(false);
		CharacterStat->AddInventoryItemCount(4);
		LockFlower = nullptr;
		return;
	}

	// Level2Field1
	else if (LockLevel2Field1 != nullptr)
	{
		Level2Field1On = true;
		Lock = false;
		LockLevel2Field1->SetInteractionUIVisible(false);
		LockLevel2Field1->Phase1();
		LockLevel2Field1 = nullptr;
		return;
	}

	// TOLevel2_Fight
	else if (LockLevel2_Fight != nullptr)
	{
		Level2_FightOn = true;
		Lock = false;
		LockLevel2_Fight->SetInteractionUIVisible(false);
		LockLevel2_Fight->StartPhase();
		LockLevel2_Fight = nullptr;
		return;
	}
}

// ��ȣ�ۿ� ���� ����, UI ����
void ATOCharacter::InteractionUI()
{
	// ������
	for (ATOItem* Item : TActorRange<ATOItem>(GetWorld()))
	{
		if ((GetActorLocation() - Item->GetActorLocation()).Size() <= 200 && !Lock)
		{
			Lock = true;
			Item->SetInteractionUIVisible(true);
			LockItem = Item;
			return;
		}
	}
	if ((LockItem != nullptr) && (GetActorLocation() - LockItem->GetActorLocation()).Size() > 200)
	{
		Lock = false;
		LockItem->SetInteractionUIVisible(false);
		LockItem = nullptr;
	}


	// üũ����Ʈ
	for (ATOCheckPoint* CheckPoint : TActorRange<ATOCheckPoint>(GetWorld()))
	{
		if ((GetActorLocation() - CheckPoint->GetActorLocation()).Size() <= 200 && !Lock)
		{
			Lock = true;
			CheckPoint->SetInteractionUIVisible(true);
			LockCheckPoint = CheckPoint;
			return;
		}
	}
	if ((LockCheckPoint != nullptr) && (GetActorLocation() - LockCheckPoint->GetActorLocation()).Size() > 200)
	{
		Lock = false;
		LockCheckPoint->SetInteractionUIVisible(false);
		LockCheckPoint = nullptr;
	}

	// ����
	for (ATOChest* Chest : TActorRange<ATOChest>(GetWorld()))
	{
		if ((GetActorLocation() - Chest->GetActorLocation()).Size() <= 200 && !Lock)
		{
			if (!(Chest->GetIsOpened()))
			{
				Lock = true;
				Chest->SetInteractionUIVisible(true);
				LockChest = Chest;
				return;
			}
		}
	}
	if ((LockChest != nullptr) && (GetActorLocation() - LockChest->GetActorLocation()).Size() > 200)
	{
		Lock = false;
		LockChest->SetInteractionUIVisible(false);
		LockChest = nullptr;
	}

	// �ڷ���Ʈ
	for (ATOTeleport* Teleport : TActorRange<ATOTeleport>(GetWorld()))
	{
		if ((GetActorLocation() - Teleport->GetActorLocation()).Size() <= 200 && !Lock)
		{
			Lock = true;
			Teleport->SetInteractionUIVisible(true);
			LockTeleport = Teleport;
			return;
		}
	}
	if ((LockTeleport != nullptr) && (GetActorLocation() - LockTeleport->GetActorLocation()).Size() > 200)
	{
		Lock = false;
		LockTeleport->SetInteractionUIVisible(false);
		LockTeleport = nullptr;
	}

	// NPC
	for (ATONPC* NPC : TActorRange<ATONPC>(GetWorld()))
	{
		// ����Ʈ ������ or Ŭ����� �ش� NPC UI ��Ȱ��ȭ
		if (NPC->GetQuestClear() != NPC->GetQuestProgress()) continue;

		if ((GetActorLocation() - NPC->GetActorLocation()).Size() <= 200 && !Lock)
		{
			Lock = true;
			NPC->SetInteractionUIVisible(true);
			LockNPC = NPC;
			return;
		}
	}
	if ((LockNPC != nullptr) && (GetActorLocation() - LockNPC->GetActorLocation()).Size() > 200)
	{
		Lock = false;
		LockNPC->SetInteractionUIVisible(false);
		LockNPC = nullptr;
	}

	// ClearPoint
	for (ATOClearPoint* ClearPoint : TActorRange<ATOClearPoint>(GetWorld()))
	{
		if ((GetActorLocation() - ClearPoint->GetActorLocation()).Size() <= 200 && !Lock)
		{
			Lock = true;
			ClearPoint->SetInteractionUIVisible(true);
			LockClear = ClearPoint;
			return;
		}
	}
	if ((LockClear != nullptr) && (GetActorLocation() - LockClear->GetActorLocation()).Size() > 200)
	{
		Lock = false;
		LockClear->SetInteractionUIVisible(false);
		LockClear = nullptr;
	}

	// �׸�2 Flower
	for (ATOFlower* Flower : TActorRange<ATOFlower>(GetWorld()))
	{
		if ((GetActorLocation() - Flower->GetActorLocation()).Size() <= 200 && !Lock)
		{
			Lock = true;
			Flower->SetInteractionUIVisible(true);
			LockFlower = Flower;
			return;
		}
	}
	if ((LockFlower != nullptr) && (GetActorLocation() - LockFlower->GetActorLocation()).Size() > 200)
	{
		Lock = false;
		LockFlower->SetInteractionUIVisible(false);
		LockFlower = nullptr;
	}

	// Level2Field1
	if (Level2Field1On) return;
	for (ALevel2Field1* Level2Field1 : TActorRange<ALevel2Field1>(GetWorld()))
	{
		if ((GetActorLocation() - Level2Field1->GetActorLocation()).Size() <= 200 && !Lock)
		{
			Lock = true;
			Level2Field1->SetInteractionUIVisible(true);
			LockLevel2Field1 = Level2Field1;
			return;
		}
	}
	if ((LockLevel2Field1 != nullptr) && (GetActorLocation() - LockLevel2Field1->GetActorLocation()).Size() > 200)
	{
		Lock = false;
		LockLevel2Field1->SetInteractionUIVisible(false);
		LockLevel2Field1 = nullptr;
	}

	// TOLevel2_Fight
	if (Level2_FightOn) return;
	for (ATOLevel2_Fight* Level2_Fight : TActorRange<ATOLevel2_Fight>(GetWorld()))
	{
		if ((GetActorLocation() - Level2_Fight->GetActorLocation()).Size() <= 200 && !Lock)
		{
			Lock = true;
			Level2_Fight->SetInteractionUIVisible(true);
			LockLevel2_Fight = Level2_Fight;
			return;
		}
	}
	if ((LockLevel2_Fight != nullptr) && (GetActorLocation() - LockLevel2_Fight->GetActorLocation()).Size() > 200)
	{
		Lock = false;
		LockLevel2_Fight->SetInteractionUIVisible(false);
		LockLevel2_Fight = nullptr;
	}
}

/*
* Script
*/
// Ű���� 1 ������ �� ��ũ��Ʈ�� �������� ����
void ATOCharacter::Script()
{
	const auto TOPlayerController = Cast<ATOPlayerController>(GetWorld()->GetFirstPlayerController()); 
	TOPlayerController->ShowScriptUI();
}



/*
* Setting
*/
void ATOCharacter::SettingUI()
{
	const auto TOPlayerController = Cast<ATOPlayerController>(GetWorld()->GetFirstPlayerController());
	if (!IsSettingUIOpened)
	{
		TOPlayerController->ShowSettingUI();

		ABLOG(Warning, TEXT("IsSettingUIOpened"));
		IsSettingUIOpened = !IsSettingUIOpened;
	}
	else
	{
		ABLOG(Warning, TEXT("IsSettingUI"));
		TOPlayerController->RemoveSettingUI();

		IsSettingUIOpened = !IsSettingUIOpened;
	}
}



/*
*  Effect
*/
void ATOCharacter::ShowEffect()
{
	ShieldEffect->ActivateSystem(true);

	/*FTimerHandle WaitHandle;
	GetWorld()->GetTimerManager().SetTimer(WaitHandle, FTimerDelegate::CreateLambda([&]()
		{
			ShieldEffect->ActivateSystem(false);
		}), 1.0f, false);*/
}
