// Fill out your copyright notice in the Description page of Project Settings.


#include "CharacterBody.h"
#include "Components/BoxComponent.h"

// Sets default values
ACharacterBody::ACharacterBody()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	Capsule = CreateDefaultSubobject<UCapsuleComponent>(TEXT("CapsuleComponent"));
	SK_Body = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("CharacterBodyMesh"));
	SetRootComponent(Capsule);
	Capsule->InitCapsuleSize(55.f, 135.0f);

	SK_Body->SetupAttachment(Capsule);

	static ConstructorHelpers::FObjectFinder<USkeletalMesh> MeshAsset(TEXT("SkeletalMesh'/Game/Assets/Body/Sad_Idle.Sad_Idle'"));
	if (MeshAsset.Succeeded())
	{
		SK_Body->SetSkeletalMesh(MeshAsset.Object);
		SK_Body->SetRelativeLocationAndRotation(FVector(0.0f, 0.0f, -135.0f), FRotator(0.0f, -90.f, 0.0f));
	}

	static ConstructorHelpers::FObjectFinder<UAnimSequence> Idle(TEXT("AnimSequence'/Game/Assets/Body/Sad_Idle_Anim.Sad_Idle_Anim'"));
	if (Idle.Succeeded())
	{
		Anim_Idle = Idle.Object;
	}

	Capsule->SetCollisionProfileName(TEXT("BlockAll"));
}

// Called when the game starts or when spawned
void ACharacterBody::BeginPlay()
{
	Super::BeginPlay();
	
	SK_Body->SetWorldScale3D(FVector(1.3f, 1.3f, 1.3f));
	SK_Body->PlayAnimation(Anim_Idle, true);
}

// Called every frame
void ACharacterBody::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

