// Fill out your copyright notice in the Description page of Project Settings.


#include "TOEnemy.h"
#include "TOAIEnemyController.h"
#include "TOEnemyStatComponent.h"
#include "Components/WidgetComponent.h"
#include "TOCharacterWidget.h"
#include "TOEnemySpawner.h"
#include "TOEnemyAnimInstance.h"
#include "DrawDebugHelpers.h"
#include "TOCharacter.h"
#include "TOWeapon.h"


ATOEnemy::ATOEnemy()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// 몬스터 설정
	GetMesh()->SetRelativeLocationAndRotation(FVector(0.0f, 0.0f, -88.0f), FRotator(0.0f, -90.0f, 0.0f));
	GetMesh()->SetAnimationMode(EAnimationMode::AnimationBlueprint);

	//AI 컨트롤러 설정
	AIControllerClass = ATOAIEnemyController::StaticClass();
	AutoPossessAI = EAutoPossessAI::PlacedInWorldOrSpawned;

	//콜리전 설정
	GetCapsuleComponent()->SetCollisionProfileName(TEXT("TOEnemy"));

	// 스탯
	EnemyStat = CreateDefaultSubobject<UTOEnemyStatComponent>(TEXT("ENEMYSTAT"));
	AttackRange = 200;
	AttackRadius = 50;

	// HP바
	HPBarWidget = CreateDefaultSubobject<UWidgetComponent>(TEXT("HPBARWIDGET"));
	HPBarWidget->SetupAttachment(GetMesh());
	HPBarWidget->SetRelativeLocation(FVector(0, 0, 180));
	HPBarWidget->SetWidgetSpace(EWidgetSpace::Screen);
	static ConstructorHelpers::FClassFinder<UUserWidget> UI_HUD(TEXT("/Game/Tellours/Developer/UI/UI_HPBar.UI_HPBar_C"));
	if (UI_HUD.Succeeded())
	{
		HPBarWidget->SetWidgetClass(UI_HUD.Class);
		HPBarWidget->SetDrawSize(FVector2D(150, 50));
	}

	// 공격
	IsAttacking = false;
}

// Called when the game starts or when spawned
void ATOEnemy::BeginPlay()
{
	Super::BeginPlay();

	// 캐릭터 컴포넌트와 HP바 위젯 연결
	auto CharacterWidget = Cast<UTOCharacterWidget>(HPBarWidget->GetUserWidgetObject());
	if (nullptr != CharacterWidget)
	{
		CharacterWidget->BindEnemyStat(EnemyStat);
	}
	SetEnemyType(CurrentEnemyType);
}



/*
* 부드러운 회전, 이동속도 설정
*/
void ATOEnemy::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);

	// 부드러운 회전
	bUseControllerRotationYaw = false;
	GetCharacterMovement()->bUseControllerDesiredRotation = false;
	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->RotationRate = FRotator(0, 480, 0);
}

void ATOEnemy::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	// HP 0 -> 사망모션
	EnemyStat->OnHPIsZero.AddLambda([this]() -> void {
		ABLOG(Warning, TEXT("OnHPIsZero"));
		SetActorEnableCollision(false);
		TOAnim->SetDeadAnim();
		Cast<ATOAIEnemyController>(GetController())->StopAI();

		// 아이템 드랍
		ATOItem* DropedItem = (ATOItem*)GetWorld()->SpawnActor<ATOItem>(GetActorLocation(), FRotator::ZeroRotator);
		DropedItem->ItemDrop();
		});
}



/*
* 공격
*/
void ATOEnemy::Attack()
{
	if (EnemyType::CROW == GetEnemyType())
		return;

	auto AnimInstance = Cast<UTOEnemyAnimInstance>(GetMesh()->GetAnimInstance());
	if (nullptr == AnimInstance) return;

	if (!IsAttacking)
	{
		TOAnim->PlayAttackMontage();
		IsAttacking = true;
	}
}

void ATOEnemy::OnAttackMontageEnded(UAnimMontage* Montage, bool bInterrupted)
{
	IsAttacking = false;
	OnAttackEnd.Broadcast();
}

void ATOEnemy::AttackCheck()
{
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

			if (HitResult.Actor->IsA(ATOCharacter::StaticClass()))
				HitResult.Actor->TakeDamage(EnemyStat->GetAttack(), DamageEvent, GetController(), this);
		}
	}
}



UTOEnemyStatComponent* ATOEnemy::GetEnemyStat()
{
	return EnemyStat;
}



/*
* Damage
*/
float ATOEnemy::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	// 데미지 받기
	TOAnim->IsAttacked = true;

	FTimerHandle DamageTimerHandle;
	GetWorld()->GetTimerManager().SetTimer(DamageTimerHandle, FTimerDelegate::CreateLambda([&]() {TOAnim->IsAttacked = false; }), 2, false);
	float FinalDamage = Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);
	ABLOG(Warning, TEXT("Actor : %s took Damage : %f"), *GetName(), FinalDamage);
	
	if (FinalDamage > 0.0f)
	{
		EnemyStat->SetDamage(FinalDamage);
	}

	return FinalDamage;
}



UTOEnemyAnimInstance* ATOEnemy::GetEnemyAnim()
{
	return TOAnim;
}



/*
* 몬스터 분류
* 주의점 : case를 {}로 묶지않으면 오류발생
*/
EnemyType ATOEnemy::GetEnemyType()
{
	return CurrentEnemyType;
}



void ATOEnemy::SetEnemyType(EnemyType NewEnemyType)
{
	CurrentEnemyType = NewEnemyType;
	switch (CurrentEnemyType)
	{
	case EnemyType::WOLF: {
		USkeletalMesh* SK_Wolf = Cast< USkeletalMesh >(StaticLoadObject(USkeletalMesh::StaticClass(), NULL, TEXT("/Game/AnimalVarietyPack/Wolf/Meshes/SK_Wolf.SK_Wolf")));
		if (SK_Wolf)
		{
			GetMesh()->SetSkeletalMesh(SK_Wolf);
		}

		UClass* Wolf_Anim = LoadObject<UClass>(NULL, TEXT("/Game/Tellours/Developer/Animations/WolfAnimBlueprint.WolfAnimBlueprint_C"));
		if (Wolf_Anim)
		{
			GetMesh()->SetAnimInstanceClass(Wolf_Anim);

			TOAnim = Cast<UTOEnemyAnimInstance>(GetMesh()->GetAnimInstance());
			ABCHECK(nullptr != TOAnim);
			TOAnim->SetMontageType(1);
			TOAnim->OnMontageEnded.AddDynamic(this, &ATOEnemy::OnAttackMontageEnded);
			TOAnim->OnAttackHitCheck.AddUObject(this, &ATOEnemy::AttackCheck);
		}

		GetCharacterMovement()->MaxWalkSpeed = 500;

		break;
	}

	case EnemyType::MANNEQUIN: {
		USkeletalMesh* SK_Mannequin = Cast< USkeletalMesh >(StaticLoadObject(USkeletalMesh::StaticClass(), NULL, TEXT("/Game/OrcaGamesFullAnimBundle/Demo/Mannequin/Character/Mesh/SK_Mannequin.SK_Mannequin")));
		if (SK_Mannequin)
		{
			GetMesh()->SetSkeletalMesh(SK_Mannequin);
		}

		UClass* Mannequin_Anim = LoadObject<UClass>(NULL, TEXT("/Game/Tellours/Developer/Animations/MannequinAnimBlueprint.MannequinAnimBlueprint_C"));
		if (Mannequin_Anim)
		{
			GetMesh()->SetAnimInstanceClass(Mannequin_Anim);

			TOAnim = Cast<UTOEnemyAnimInstance>(GetMesh()->GetAnimInstance());
			ABCHECK(nullptr != TOAnim);
			TOAnim->SetMontageType(2);
			TOAnim->OnMontageEnded.AddDynamic(this, &ATOEnemy::OnAttackMontageEnded);
			TOAnim->OnAttackHitCheck.AddUObject(this, &ATOEnemy::AttackCheck);
		}

		GetCharacterMovement()->MaxWalkSpeed = 500;

		// 무기 추가
		FName WeaponSocket(TEXT("hand_rSocket"));
		auto CurWeapon = GetWorld()->SpawnActor<ATOWeapon>(FVector(-10.0f, 5.0f, 0.0f), FRotator(-180.0f, 0.0f, -20.0f));
		if (nullptr != CurWeapon)
		{
			CurWeapon->AttachToComponent(GetMesh(), FAttachmentTransformRules::SnapToTargetNotIncludingScale, WeaponSocket);
		}

		break;
	}
	// 테마 3의 1번 필드 몬스터 : 까마귀
	case EnemyType::CROW: {
		USkeletalMesh* SK_Mannequin = Cast< USkeletalMesh >(StaticLoadObject(USkeletalMesh::StaticClass(), NULL, TEXT("/Game/AnimalVarietyPack/Crow/Meshes/SK_Crow.SK_Crow")));
		if (SK_Mannequin)
		{
			GetMesh()->SetSkeletalMesh(SK_Mannequin);
		}

		UClass* Mannequin_Anim = LoadObject<UClass>(NULL, TEXT("/Game/AnimalVarietyPack/Crow/Meshes/Crow.Crow_C"));
		if (Mannequin_Anim)
		{
			GetMesh()->SetAnimInstanceClass(Mannequin_Anim);

			TOAnim = Cast<UTOEnemyAnimInstance>(GetMesh()->GetAnimInstance());
			ABCHECK(nullptr != TOAnim);
			TOAnim->OnMontageEnded.AddDynamic(this, &ATOEnemy::OnAttackMontageEnded);
		}
		GetMesh()->SetRelativeScale3D(FVector(3.0f, 3.0f, 3.0f));
		GetCharacterMovement()->MaxWalkSpeed = 300;

		break;
	}
	//테마 3의 2번 필드 몬스터 
	case EnemyType::MANNEQUIN2: {
		USkeletalMesh* SK_Mannequin = Cast< USkeletalMesh >(StaticLoadObject(USkeletalMesh::StaticClass(), NULL, TEXT("/Game/OrcaGamesFullAnimBundle/Demo/Mannequin/Character/Mesh/SK_Mannequin.SK_Mannequin")));
		if (SK_Mannequin)
		{
			GetMesh()->SetSkeletalMesh(SK_Mannequin);
		}
		// 해당 몬스터의 공격력을 높게 설정
		EnemyStat->SetNewLevel(19);

		UClass* Mannequin_Anim = LoadObject<UClass>(NULL, TEXT("/Game/Tellours/Developer/Animations/MannequinAnimBlueprint.MannequinAnimBlueprint_C"));
		if (Mannequin_Anim)
		{
			GetMesh()->SetAnimInstanceClass(Mannequin_Anim);

			TOAnim = Cast<UTOEnemyAnimInstance>(GetMesh()->GetAnimInstance());
			ABCHECK(nullptr != TOAnim);
			TOAnim->SetMontageType(2);
			TOAnim->OnMontageEnded.AddDynamic(this, &ATOEnemy::OnAttackMontageEnded);
			TOAnim->OnAttackHitCheck.AddUObject(this, &ATOEnemy::AttackCheck);
		}

		GetCharacterMovement()->MaxWalkSpeed = 500;

		// 무기 추가
		FName WeaponSocket(TEXT("hand_rSocket"));
		auto CurWeapon = GetWorld()->SpawnActor<ATOWeapon>(FVector(-10.0f, 5.0f, 0.0f), FRotator(-180.0f, 0.0f, -20.0f));
		if (nullptr != CurWeapon)
		{
			CurWeapon->AttachToComponent(GetMesh(), FAttachmentTransformRules::SnapToTargetNotIncludingScale, WeaponSocket);
		}

		break;
	}
	}
}
