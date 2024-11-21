// Fill out your copyright notice in the Description page of Project Settings.


#include "TOFirstBoss.h"
#include "Components/WidgetComponent.h"
#include "TOCharacterWidget.h"
#include "TOBossStatComponent.h"
#include "TOBossAnimInstance.h"
#include "TOItem.h"
#include "TOChest.h"

// Sets default values
ATOFirstBoss::ATOFirstBoss()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	USkeletalMesh* FirstBoss = Cast< USkeletalMesh >(StaticLoadObject(USkeletalMesh::StaticClass(), NULL, TEXT("/Game/AnimalVarietyPack/Pig/Meshes/SK_Pig.SK_Pig")));
	if (FirstBoss)
	{
		GetMesh()->SetSkeletalMesh(FirstBoss);
	}

	GetCharacterMovement()->MaxWalkSpeed = 700;
	GetMesh()->SetWorldScale3D(FVector(3.0f, 3.0f, 3.0f));

	// AnimInstance
	GetMesh()->SetAnimationMode(EAnimationMode::AnimationBlueprint);
	static ConstructorHelpers::FClassFinder<UAnimInstance> PIG_ANIM(TEXT("/Game/Tellours/Developer/Animations/PigAnimBlueprint.PigAnimBlueprint_C"));
	if (PIG_ANIM.Succeeded())
	{
		GetMesh()->SetAnimInstanceClass(PIG_ANIM.Class);
	}

	// Attack
	IsAttacking = false;
	SetAttackRange(200.0f);
	SetAttackRadius(50.0f);
	

	// 몬스터 설정
	GetMesh()->SetRelativeLocationAndRotation(FVector(-295.0f, 0.0f, -88.0f), FRotator(0.0f, -90.0f, 0.0f));

	//AI 컨트롤러 설정
	AIControllerClass = ATOBossController::StaticClass();
	AutoPossessAI = EAutoPossessAI::PlacedInWorldOrSpawned;

	//콜리전 설정
	GetMesh()->SetCollisionProfileName(TEXT("TOBoss"));

	// 스탯
	BossStat = CreateDefaultSubobject<UTOBossStatComponent>(TEXT("BOSSSTAT"));

	// HP바
	HPBarWidget = CreateDefaultSubobject<UWidgetComponent>(TEXT("HPBARWIDGET"));
	HPBarWidget->SetupAttachment(GetMesh());
	HPBarWidget->SetRelativeLocation(FVector(0, 0, 110));
	HPBarWidget->SetWidgetSpace(EWidgetSpace::Screen);
	static ConstructorHelpers::FClassFinder<UUserWidget> UI_HUD(TEXT("/Game/Tellours/Developer/UI/UI_HPBar.UI_HPBar_C"));
	if (UI_HUD.Succeeded())
	{
		HPBarWidget->SetWidgetClass(UI_HUD.Class);
		HPBarWidget->SetDrawSize(FVector2D(150, 50));
	}

}

// Called when the game starts or when spawned
void ATOFirstBoss::BeginPlay()
{
	Super::BeginPlay();

	auto CharacterWidget = Cast<UTOCharacterWidget>(HPBarWidget->GetUserWidgetObject());
	if (nullptr != CharacterWidget)
	{
		CharacterWidget->BindBossStat(BossStat);
	}
	SetPhase();
}



/*
* 부드러운 회전, 이동속도 설정
*/
void ATOFirstBoss::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);

	// 부드러운 회전
	bUseControllerRotationYaw = false;
	GetCharacterMovement()->bUseControllerDesiredRotation = false;
	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->RotationRate = FRotator(0, 480, 0);
}

void ATOFirstBoss::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	BossAnim = Cast<UTOBossAnimInstance>(GetMesh()->GetAnimInstance());
	TOBossController = Cast<ATOBossController>(GetController());

	ABCHECK(nullptr != BossAnim);	
	BossAnim->OnMontageEnded.AddDynamic(this, &ATOFirstBoss::OnAttackMontageEnded);
	BossAnim->OnAttackHitCheck.AddUObject(this, &ATOFirstBoss::AttackCheck);

	// HP 0 -> 사망모션
	BossStat->OnHPIsZero.AddLambda([this]() -> void {
		ABLOG(Warning, TEXT("Dead State"))
		BossAnim->SetDeadAnim();
		SetActorEnableCollision(false);
		GetWorld()->SpawnActor<ATOItem>(GetActorLocation() + FVector::UpVector * 50, FRotator::ZeroRotator);
		TOBossController->StopAI();

		GetWorld()->GetTimerManager().SetTimer(DestroyTimerHandle, FTimerDelegate::CreateLambda([&]()
			{
				this->Destroy();
				GetWorld()->GetTimerManager().ClearTimer(DestroyTimerHandle);
				GetWorld()->SpawnActor<ATOChest>();
			}), 3.0f, false);
	});
}

void ATOFirstBoss::SetPhase()
{
	// 페이즈 변동에 따른 애니메이션 변동
	int32 Phase = BossStat->GetPhase();

	switch (Phase)
	{
		case 0:
		{
			ABLOG(Warning, TEXT("Phase Change0"));
			TOBossController->Phase_0_function();
			BossAnim->SetPhase0();
			break;
		}
		case 1:
		case 2:
		{
			ABLOG(Warning, TEXT("Phase Change1"));
			TOBossController->Phase_1_function();
			BossAnim->SetPhase1();
			SetAttackRange(200.0f);
			SetAttackRadius(50.0f);

			// WakeUp Motion delay timer
			FTimerHandle PhaseChangeTimerHandle;
			GetWorld()->GetTimerManager().SetTimer(PhaseChangeTimerHandle, FTimerDelegate::CreateLambda([&]()
			{
				ABLOG_S(Warning);
				BossAnim->SetPhaseZeroEnd();
				GetWorld()->GetTimerManager().ClearTimer(PhaseChangeTimerHandle);
			}), 1.0f, false);

			break;
		}
		case 3:
		{
			ABLOG(Warning, TEXT("Phase Change2"));
			TOBossController->Phase_2_function();
			BossAnim->SetPhase2();
			SetAttackRange(500.0f);
			SetAttackRadius(50.0f);
		}
	}
}

int32 ATOFirstBoss::GetPhase()
{
	return BossStat->GetPhase();
}

float ATOFirstBoss::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	// 데미지 받기
	float FinalDamage = Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);
	ABLOG(Warning, TEXT("Actor : %s took Damage : %f"), *GetName(), FinalDamage);
	BossStat->SetDamage(FinalDamage);
	SetPhase();

	return FinalDamage;
}

void ATOFirstBoss::Attack()
{
	// In Testing, if no error then remove this section
	// 
	//auto BossAnimInstance = Cast<UTOBossAnimInstance>(GetMesh()->GetAnimInstance());
	//if (nullptr == BossAnimInstance)
	//	return;
	//if(BossStat->GetPhase() == 1)
	//	BossAnimInstance->PlayAttackMontage();
	//else if (BossStat->GetPhase() == 2)
	//{
	//	BossAnimInstance->PlayAttackMontage();
	//	// forward Animation
	//	FTimerHandle AttackMotionTimerHandle;
	//	GetWorld()->GetTimerManager().SetTimer(AttackMotionTimerHandle, FTimerDelegate::CreateLambda([&]()
	//		{
	//			BossAnim->StopMontage();
	//			SetActorLocation(GetActorLocation() + GetActorForwardVector() * AttackRange * 2.65f);
	//			GetWorld()->GetTimerManager().ClearTimer(AttackMotionTimerHandle);
	//			OnAttackEnd.Broadcast();
	//		}), 2.3f, false);
	//}

	// test
	if (nullptr == BossAnim)
		return;
	/*if (BossStat->GetPhase() == 1)*/
		BossAnim->PlayAttackMontage();
	//else if (BossStat->GetPhase() == 2)
	//{
	//	SetActorEnableCollision(false);
	//	BossAnim->PlayAttackMontage();
	//	// forward Animation
	//	
	//	GetWorld()->GetTimerManager().SetTimer(AttackMotionTimerHandle, FTimerDelegate::CreateLambda([&]()
	//		{
	//			BossAnim->StopMontage();
	//			SetActorLocation(GetActorLocation() + GetActorForwardVector() * AttackRange * 2.65f);
	//			GetWorld()->GetTimerManager().ClearTimer(AttackMotionTimerHandle);
	//			OnAttackEnd.Broadcast();
	//			SetActorEnableCollision(true);
	//		}), 2.3f, false);
	//}
}

void ATOFirstBoss::SetAttackRange(float NewAttackRange)
{
	AttackRange = NewAttackRange;
}

void ATOFirstBoss::SetAttackRadius(float NewAttackRadius)
{
	AttackRadius = NewAttackRadius;
}

void ATOFirstBoss::OnAttackMontageEnded(UAnimMontage* Montage, bool bInterrupted)
{
	IsAttacking = false;
	OnAttackEnd.Broadcast();
}

void ATOFirstBoss::AttackCheck()
{
	FHitResult HitResult;
	FCollisionQueryParams Params(NAME_None, false, this);
	bool bResult = GetWorld()->SweepSingleByChannel(
		HitResult,
		GetActorLocation() + FVector(0.0f, 0.0f, -30.0f),
		GetActorLocation() + GetActorForwardVector() * AttackRange + FVector(0.0f, 0.0f, -30.0f),
		FQuat::Identity,
		ECollisionChannel::ECC_GameTraceChannel2,
		FCollisionShape::MakeSphere(AttackRadius),
		Params);

	if (bResult)
	{
		if (HitResult.Actor.IsValid())
		{
			FDamageEvent DamageEvent;
			HitResult.Actor->TakeDamage(BossStat->GetAttack(), DamageEvent, GetController(), this);

			ACharacter* HitCharacter = Cast<ACharacter>(HitResult.GetActor());
			FVector Force = GetActorForwardVector() + FVector(0, 0, 1);
			HitCharacter->GetCharacterMovement()->Launch(Force*1000);

			//FVector Force = GetActorForwardVector() + FVector(0, 0, 1);
			//HitResult.GetComponent()->SetSimulatePhysics(true);
			//HitResult.GetComponent()->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics); // 또는 ECollisionEnabled::PhysicsOnly
			//HitResult.GetComponent()->SetMassOverrideInKg(NAME_None, 1000.0f);
			//HitResult.GetComponent()->AddForce(Force);
		}
	}
}