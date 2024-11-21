// Copyright Epic Games, Inc. All Rights Reserved.

#include "CapstoneCharacter.h"
#include "Animation/AnimInstance.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include <DrawDebugHelpers.h>
#include "EngineUtils.h"
#include "CapstoneObject.h"
#include "CapstoneSettingUI.h"
#include "CapstoneController.h"
#include "CapstoneHUDWidget.h"
#include "Door.h"
#include "Fireplace.h"

#include "PhysicalMaterials/PhysicalMaterial.h"

DEFINE_LOG_CATEGORY_STATIC(LogFPChar, Warning, All);

//////////////////////////////////////////////////////////////////////////
// ACapstoneCharacter

ACapstoneCharacter::ACapstoneCharacter()
{
	// Set size for collision capsule
	GetCapsuleComponent()->InitCapsuleSize(55.f, 96.0f);

	// Create a CameraComponent	
	FirstPersonCameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("FirstPersonCamera"));
	FirstPersonCameraComponent->SetupAttachment(GetCapsuleComponent());
	FirstPersonCameraComponent->SetRelativeLocation(FVector(-39.56f, 1.75f, 64.f)); // Position the camera
	FirstPersonCameraComponent->bUsePawnControlRotation = true;

	// Create a mesh component that will be used when being viewed from a '1st person' view (when controlling this pawn)
	Mesh1P = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("CharacterMesh1P"));
	Mesh1P->SetOnlyOwnerSee(true);
	Mesh1P->SetupAttachment(FirstPersonCameraComponent);
	Mesh1P->bCastDynamicShadow = false;
	Mesh1P->CastShadow = false;
	Mesh1P->SetRelativeRotation(FRotator(1.9f, -19.19f, 5.2f));
	Mesh1P->SetRelativeLocation(FVector(-0.5f, -4.4f, -155.7f));

	ApparitionMode = false;
	MainPostProcessVolume = nullptr;
	settings = nullptr;

	BlankTimeline = CreateDefaultSubobject<UTimelineComponent>(TEXT("BlankTimeline"));
	BlankCallback.BindUFunction(this, FName("BlankInterpReturn"));
	BlankTimelineFinish.BindUFunction(this, FName("BlankFinish"));

	static ConstructorHelpers::FObjectFinder<UCurveFloat> curve(TEXT("/Game/Assets/CV_Blank.CV_Blank"));
	if (curve.Succeeded())
	{
		BlankCurve = curve.Object;
	}

	static ConstructorHelpers::FObjectFinder<USoundCue> WoodSound(TEXT("/Game/HorrorEngine/Audio/Footsteps/Wood_Cue.Wood_Cue"));
	if (WoodSound.Succeeded())
	{
		WoodCue = WoodSound.Object;
	}

	static ConstructorHelpers::FObjectFinder<USoundCue> CarpetSound(TEXT("/Game/HorrorEngine/Audio/Footsteps/Carpet_Cue.Carpet_Cue"));
	if (CarpetSound.Succeeded())
	{
		CarpetCue = CarpetSound.Object;
	}

	CanFootstep = true;
	FootstepValue = 0.4f;
}

void ACapstoneCharacter::BeginPlay()
{
	// Call the base class  
	Super::BeginPlay();

	for (TActorIterator<APostProcessVolume> Actor(GetWorld()); Actor; ++Actor)
	{
		if (Actor->ActorHasTag("TEST"))
		{
			MainPostProcessVolume = *Actor;
			settings = (FPostProcessSettings*)MainPostProcessVolume->GetProperties().Settings;
			break;
		}
	}

	BlankTimeline->SetLooping(false);
	BlankTimeline->AddInterpFloat(BlankCurve, BlankCallback);
	BlankTimeline->SetTimelineFinishedFunc(BlankTimelineFinish);
	BlankTimeline->SetTimelineLength(1.0f);

	CapstoneGameInstance = GetWorld()->GetGameInstance();
	CapstoneGameSubsystem = CapstoneGameInstance->GetSubsystem<UCapstoneSubsystem>();
	CapstoneGameSubsystem->GetAppartionState(false);
	CapstoneController = Cast<ACapstoneController>(GetController());

	// input mode ����
	FInputModeGameOnly InputMode;
	CapstoneController->SetInputMode(InputMode);
}

void ACapstoneCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	InteractionCheck();

	CapstoneController->GetHUDWidget()->SetSPBarPercent(Sanity);
	if (ApparitionMode) {
		Sanity -= 0.005;
		if (Sanity <= 0.0f) {
			CapstoneController->ShowFalseEndingUI();
		}
	}

	// Footstep
	if ((GetVelocity().X > 2.0f || GetVelocity().X < -2.0f || GetVelocity().Y > 2.0f || GetVelocity().Y < -2.0f) && GetVelocity().Z == 0.0f && CanFootstep)
	{
		CanFootstep = false;
		Footstep();
	}
}

//////////////////////////////////////////////////////////////////////////
// Input

void ACapstoneCharacter::SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent)
{
	// set up gameplay key bindings
	check(PlayerInputComponent);

	// Bind movement events
	PlayerInputComponent->BindAxis("MoveForward", this, &ACapstoneCharacter::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &ACapstoneCharacter::MoveRight);
	PlayerInputComponent->BindAxis("Turn", this, &APawn::AddControllerYawInput);
	PlayerInputComponent->BindAxis("LookUp", this, &APawn::AddControllerPitchInput);

	// ��ü��Ż
	PlayerInputComponent->BindAction("Apparition", IE_Pressed, this, &ACapstoneCharacter::Apparition);

	// ��ȣ�ۿ�
	PlayerInputComponent->BindAction("Interaction", IE_Pressed, this, &ACapstoneCharacter::Interaction);

	// Setting UI
	PlayerInputComponent->BindAction("Setting", IE_Pressed, this, &ACapstoneCharacter::SettingUI);
	// Ending UI
	// PlayerInputComponent->BindAction("EndTest", IE_Pressed, this, &ACapstoneCharacter::EndingUI);

}

void ACapstoneCharacter::MoveForward(float Value)
{
	if (Value != 0.0f)
	{
		// add movement in that direction
		AddMovementInput(GetActorForwardVector(), Value);
	}
}

void ACapstoneCharacter::MoveRight(float Value)
{
	if (Value != 0.0f)
	{
		// add movement in that direction
		AddMovementInput(GetActorRightVector(), Value);
	}
}

void ACapstoneCharacter::Interaction()
{
	if (CheckedObject != nullptr) {
		CheckedObject->Interaction();
	}

	if (CheckedDoor != nullptr) {
		CheckedDoor->Interaction();
	}

	if (CheckedFireplace != nullptr) {
		CheckedFireplace->Interaction();
	}

	if (CheckedSanityRecovery != nullptr) {
		CheckedSanityRecovery->Interaction();
	}
}

void ACapstoneCharacter::InteractionCheck()
{
	FCollisionQueryParams TraceParameters(NAME_None, false, this);

	FVector A = GetWorld()->GetFirstPlayerController()->PlayerCameraManager->GetCameraLocation();
	FVector B = GetWorld()->GetFirstPlayerController()->PlayerCameraManager->GetActorForwardVector();

	GetWorld()->LineTraceSingleByChannel(
		HitActor,
		A,
		FVector(A + B * 300.0f),
		ECollisionChannel::ECC_GameTraceChannel1,
		TraceParameters
	);

	if (HitActor.Actor.IsValid() && HitActor.Actor->IsA(ACapstoneObject::StaticClass())) {
		CheckedObject = Cast<ACapstoneObject>(HitActor.Actor);

		if (!ApparitionMode)
			CapstoneController->GetHUDWidget()->SetInteractionUI(true);
	}
	else if (CheckedObject != nullptr) {
		if (!ApparitionMode)
		{
			CheckedObject->SetInteractionUIVisible(false);
			CapstoneController->GetHUDWidget()->SetInteractionUI(false);
			CheckedObject = nullptr;
		}
	}

	if (HitActor.Actor.IsValid() && HitActor.Actor->IsA(ADoor::StaticClass())) {
		CheckedDoor = Cast<ADoor>(HitActor.Actor);
		CapstoneController->GetHUDWidget()->SetInteractionUI(true);
	}
	else if (CheckedDoor != nullptr)
	{
		CheckedDoor->SetInteractionUIVisible(false);
		CapstoneController->GetHUDWidget()->SetInteractionUI(false);
		CheckedDoor = nullptr;
	}

	if (HitActor.Actor.IsValid() && HitActor.Actor->IsA(AFireplace::StaticClass())) {
		CheckedFireplace = Cast<AFireplace>(HitActor.Actor);
		CapstoneController->GetHUDWidget()->SetInteractionUI(true);
	}
	else if (CheckedFireplace != nullptr) {
		CheckedFireplace->SetInteractionUIVisible(false);
		CapstoneController->GetHUDWidget()->SetInteractionUI(false);
		CheckedFireplace = nullptr;
	}

	if (HitActor.Actor.IsValid() && HitActor.Actor->IsA(ASanityRecovery::StaticClass())) {
		CheckedSanityRecovery = Cast<ASanityRecovery>(HitActor.Actor);
		CapstoneController->GetHUDWidget()->SetInteractionUI(true);
	}
	else if (CheckedSanityRecovery != nullptr) {
		CheckedSanityRecovery->SetInteractionUIVisible(false);
		CapstoneController->GetHUDWidget()->SetInteractionUI(false);
		CheckedSanityRecovery = nullptr;
	}

	if (HitActor.Actor.IsValid() && HitActor.Actor->IsA(ACharacterBody::StaticClass())) {
		CheckedBody = Cast<ACharacterBody>(HitActor.Actor);

		if (ApparitionMode)
			CapstoneController->GetHUDWidget()->SetApparitionUI(true);
	}
	else if (CheckedBody != nullptr) {
		if (ApparitionMode)
		{
			CapstoneController->GetHUDWidget()->SetApparitionUI(false);
			CheckedBody = nullptr;
		}
	}
}



void ACapstoneCharacter::Apparition()
{
	if (ApparitionMode)			// TRUE
	{
		if (HitActor.Actor == BodyMesh)
		{
			BlankTimeline->PlayFromStart();

			DisableInput(GetWorld()->GetFirstPlayerController());

			FTimerHandle TimerHandle;
			GetWorld()->GetTimerManager().SetTimer(TimerHandle, FTimerDelegate::CreateLambda([&]() {
				MainPostProcessVolume->bEnabled = false;

				SetActorLocation(FVector(BodyMesh->GetActorLocation().X, BodyMesh->GetActorLocation().Y, GetActorLocation().Z));
				GetWorld()->GetFirstPlayerController()->SetControlRotation(FRotator(BodyMesh->GetActorRotation().Pitch, BodyMesh->GetActorRotation().Yaw, BodyMesh->GetActorRotation().Roll));
				BodyMesh->Destroy();
				CapstoneController->GetHUDWidget()->SetApparitionUI(false);

				ApparitionMode = false;
				CapstoneGameSubsystem->GetAppartionState(ApparitionMode);
				}), 0.5f, false);
		}
		else
		{
			if (IsValid(CapstoneController->GetHUDWidget()))
				CapstoneController->GetHUDWidget()->ShowDialog(FString("Body doesn't exist!"));
		}
	}
	else						// FALSE
	{
		if (HitActor.Actor.IsValid())
		{
			if (IsValid(CapstoneController->GetHUDWidget()))
				CapstoneController->GetHUDWidget()->ShowDialog(FString("BLOCKING! CANT Apparition!"));
		}
		else if (Sanity > 10)
		{
			MainPostProcessVolume->bEnabled = true;

			DisableInput(GetWorld()->GetFirstPlayerController());

			BlankTimeline->PlayFromStart();

			FTimerHandle TimerHandle;
			GetWorld()->GetTimerManager().SetTimer(TimerHandle, FTimerDelegate::CreateLambda([&]() {
				BodyMesh = (ACharacterBody*)GetWorld()->SpawnActor<ACharacterBody>(FVector(GetActorLocation().X, GetActorLocation().Y, GetActorLocation().Z), GetActorRotation());
				SetActorLocation(GetActorLocation() + GetActorForwardVector() * 95.0f);

				FHitResult HitResult;
				FCollisionQueryParams CollisionParams;
				CollisionParams.AddIgnoredActor(BodyMesh);

				bool bHit = GetWorld()->LineTraceSingleByChannel(HitResult, BodyMesh->GetActorLocation(), BodyMesh->GetActorLocation() - FVector(0, 0, 10000), ECC_Visibility, CollisionParams);

				if (bHit)
				{
					BodyMesh->SetActorLocation(FVector(HitResult.Location.X, HitResult.Location.Y, HitResult.Location.Z + 135.0f));
				}

				ApparitionMode = true;
				CapstoneGameSubsystem->GetAppartionState(ApparitionMode);
				}), 0.5f, false);

			Sanity -= 10;
		}
	}
}

void ACapstoneCharacter::BlankInterpReturn(float value)
{
	settings->AutoExposureBias = value;
}

void ACapstoneCharacter::BlankFinish()
{
	EnableInput(GetWorld()->GetFirstPlayerController());
}

void ACapstoneCharacter::SettingUI()
{
	CapstoneController->ShowESC();
}

float ACapstoneCharacter::GetSanity()
{
	return Sanity;
}

void ACapstoneCharacter::SetSanity(float value)
{
	Sanity = value;
}

void ACapstoneCharacter::CheckDead()
{
	if (Sanity <= 0.0f)
		CapstoneController->ShowFalseEndingUI();
}

void ACapstoneCharacter::Footstep()
{
	FCollisionResponseParams ResponseParams;
	FCollisionQueryParams QueryParams = FCollisionQueryParams::DefaultQueryParam;
	QueryParams.bReturnPhysicalMaterial = true;
	FHitResult CheckPhysics;

	GetWorld()->LineTraceSingleByChannel(
		CheckPhysics,
		GetActorLocation(),
		FVector(GetActorLocation().X, GetActorLocation().Y, GetActorLocation().Z - 150.0f),
		ECollisionChannel::ECC_Visibility,
		QueryParams,
		ResponseParams
	);

	if (CheckPhysics.IsValidBlockingHit())
	{
		switch (CheckPhysics.PhysMaterial->SurfaceType)
		{
		case SurfaceType1:
			UGameplayStatics::PlaySoundAtLocation(GetWorld(), Cast<USoundBase>(WoodCue), FVector(GetActorLocation().X, GetActorLocation().Y, GetActorLocation().Z - 150.0f), FVolume);
			break;
		case SurfaceType2:
			UGameplayStatics::PlaySoundAtLocation(GetWorld(), Cast<USoundBase>(CarpetCue), FVector(GetActorLocation().X, GetActorLocation().Y, GetActorLocation().Z - 150.0f), FVolume);
			break;
		default:
			break;
		}
	}


	FTimerHandle FootstepHandle;
	GetWorld()->GetTimerManager().SetTimer(FootstepHandle, FTimerDelegate::CreateLambda([&]() {
		CanFootstep = true;
		}), FootstepValue, false);
}

void ACapstoneCharacter::FSoundp()
{
	if (FVolume < 0.1f)
		FVolume = 0.1f;
	else
		FVolume = FVolume + 0.1f;

	FVolume = FVolume >= 1.0f ? 1.0f : FVolume;
	CapstoneController->SettingUISetText(FVolume);
}
void ACapstoneCharacter::FSoundd()
{
	FVolume = FVolume - 0.1f;
	
	FVolume = FVolume < 0.1f ? 0.01f : FVolume;
	CapstoneController->SettingUISetText(FVolume);
}

void ACapstoneCharacter::FSoundq()
{
	FVolume = 0.01f;
	CapstoneController->SettingUISetText(FVolume);
}