// Fill out your copyright notice in the Description page of Project Settings.


#include "CapstoneGhost.h"
#include "GhostAIController.h"
#include "CapstoneCharacter.h"
#include "CharacterBody.h"

// Sets default values
ACapstoneGhost::ACapstoneGhost()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	GetMesh()->SetRelativeLocationAndRotation(FVector(0.0f, 0.0f, -88.0f), FRotator(0.0f, -90.0f, 0.0f));
	static ConstructorHelpers::FObjectFinder<USkeletalMesh> SK_Ghost(TEXT("/Game/Assets/Ghost/source/SKM_Ghost.SKM_Ghost"));
	if (SK_Ghost.Succeeded())
		GetMesh()->SetSkeletalMesh(SK_Ghost.Object);

	AIControllerClass = AGhostAIController::StaticClass();
	AutoPossessAI = EAutoPossessAI::PlacedInWorldOrSpawned;

	// 애니메이션
	static ConstructorHelpers::FObjectFinder<UAnimSequence> Anim(TEXT("/Game/Assets/Ghost/source/ANIM_Ghost.ANIM_Ghost"));
	if (Anim.Succeeded())
		Anim_Idle = Anim.Object;

	static ConstructorHelpers::FObjectFinder<USoundCue> DisappearSC(TEXT("/Game/HumanVocalizations/voice_male_b_breath_sigh_06_Cue.voice_male_b_breath_sigh_06_Cue"));
	if (DisappearSC.Succeeded())
		DisappearSound = DisappearSC.Object;
}

// Called when the game starts or when spawned
void ACapstoneGhost::BeginPlay()
{
	Super::BeginPlay();
	
	GetMesh()->PlayAnimation(Anim_Idle, true);
}

// Called every frame
void ACapstoneGhost::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	TouchCharacter();
}

void ACapstoneGhost::TouchCharacter()
{
	auto Character = Cast<ACapstoneCharacter>(GetWorld()->GetFirstPlayerController()->GetPawn());

	if ((GetActorLocation() - Character->GetActorLocation()).Size() < 100) {
		UGameplayStatics::PlaySoundAtLocation(this, DisappearSound, GetActorLocation(), 1.0f);
		Character->SetSanity(Character->GetSanity() - 30);
		Character->CheckDead();

		UCapstoneSubsystem* CapstoneSubsystem = GetWorld()->GetGameInstance()->GetSubsystem<UCapstoneSubsystem>();
		TArray<FVector> CorLoc = CapstoneSubsystem->GetCorLoc();

		while (1) {
			int RandIdx = FMath::RandRange(0, CorLoc.Num()-1);
			if ((CorLoc[RandIdx] - GetActorLocation()).Size() > 3000) {
				SetActorLocation(CorLoc[RandIdx] + FVector::UpVector * 300);
				break;
			}
		}
		return;
	}

	for (TActorIterator<ACharacterBody> Body(GetWorld()); Body; ++Body) {
		if ((GetActorLocation() - Body->GetActorLocation()).Size() < 200) {
			UGameplayStatics::PlaySoundAtLocation(this, DisappearSound, GetActorLocation(), 1.0f);
			Character->SetSanity(Character->GetSanity() - 30);

			UCapstoneSubsystem* CapstoneSubsystem = GetWorld()->GetGameInstance()->GetSubsystem<UCapstoneSubsystem>();
			TArray<FVector> CorLoc = CapstoneSubsystem->GetCorLoc();

			while (1) {
				int RandIdx = FMath::RandRange(0, CorLoc.Num()-1);
				if ((CorLoc[RandIdx] - GetActorLocation()).Size() > 3000) {
					SetActorLocation(CorLoc[RandIdx] + FVector::UpVector * 300);
					break;
				}
			}
			return;
		}
	}
}
