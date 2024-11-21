// Fill out your copyright notice in the Description page of Project Settings.


#include "TOFireball.h"

// Sets default values
ATOFireball::ATOFireball()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Fireball = CreateDefaultSubobject<USphereComponent>(TEXT("FIREBALL"));

	RootComponent = Fireball;

	FireballEffect = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("EFFECT"));
	FireballHitEffect = CreateDefaultSubobject<UParticleSystem>(TEXT("HITEFFECT"));

	static ConstructorHelpers::FObjectFinder<UParticleSystem> FIREBALL_EFFECT(TEXT("/Game/InfinityBladeEffects/Effects/FX_Ambient/Fire/P_Lava_Splashes.P_Lava_Splashes"));
	if (FIREBALL_EFFECT.Succeeded())
	{
		FireballEffect->SetTemplate(FIREBALL_EFFECT.Object);

		FireballEffect->SetRelativeScale3D(FVector(0.25f));

		FireballEffect->SetupAttachment(Fireball);
	}


	static ConstructorHelpers::FObjectFinder<UParticleSystem> FIREBALL_HIT_EFFECT(TEXT("/Game/Realistic_Starter_VFX_Pack_Vol2/Particles/Explosion/P_Explosion_Big_B.P_Explosion_Big_B"));
	if (FIREBALL_HIT_EFFECT.Succeeded())
	{
		FireballHitEffect = FIREBALL_HIT_EFFECT.Object;
	}

	


	SkillLength = 600.0f;

	Fireball->SetCollisionProfileName(TEXT("TOSkill"));

	Fireball->CanCharacterStepUpOn = ECB_No;
}

// Called when the game starts or when spawned
void ATOFireball::BeginPlay()
{
	Super::BeginPlay();
	
	StartVector = GetActorLocation();
}

// Called every frame
void ATOFireball::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	SetActorLocation(GetActorLocation() + (GetActorForwardVector() * 600.0f * DeltaTime));

	float Distance = FVector::Distance(StartVector, GetActorLocation());
	if (Distance >= SkillLength)
	{
		Destroy();
	}
}

void ATOFireball::NotifyHit(UPrimitiveComponent* MyComp, AActor* Other, UPrimitiveComponent* OtherComp, bool bSelfMoved, FVector HitLocation, FVector HitNormal, FVector NormalImpulse, const FHitResult& Hit)
{
	UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), FireballHitEffect, GetActorLocation(), GetActorRotation(), FVector(0.25f));

	FDamageEvent DamageEvent;
	Other->TakeDamage(50.0f, DamageEvent, GetWorld()->GetFirstPlayerController(), this);
	
	Destroy();
}

