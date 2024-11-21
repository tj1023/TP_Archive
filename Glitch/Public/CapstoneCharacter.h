// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "EngineMinimal.h"
#include "CapstoneGameInstance.h"
#include "CapstoneSubsystem.h"
#include "CharacterBody.h"
#include "SanityRecovery.h"
#include "Components/TimelineComponent.h"
#include "Engine/PostProcessVolume.h"
#include "Sound/SoundCue.h"
#include "GameFramework/Character.h"
#include "CapstoneCharacter.generated.h"

class UInputComponent;
class USkeletalMeshComponent;
class USceneComponent;
class UCameraComponent;
class UAnimMontage;
class USoundBase;

UCLASS(config=Game)
class ACapstoneCharacter : public ACharacter
{
	GENERATED_BODY()

	/** Pawn mesh: 1st person view (arms; seen only by self) */
	UPROPERTY(VisibleDefaultsOnly, Category = Mesh)
	USkeletalMeshComponent* Mesh1P;

	/** First person camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	UCameraComponent* FirstPersonCameraComponent;

public:
	ACapstoneCharacter();

protected:
	virtual void BeginPlay();

protected:
	/** Handles moving forward/backward */
	void MoveForward(float Val);
	/** Handles stafing movement, left and right */
	void MoveRight(float Val);

protected:
	// APawn interface
	virtual void SetupPlayerInputComponent(UInputComponent* InputComponent) override;
	// End of APawn interface

public:
	/** Returns Mesh1P subobject **/
	USkeletalMeshComponent* GetMesh1P() const { return Mesh1P; }
	/** Returns FirstPersonCameraComponent subobject **/
	UCameraComponent* GetFirstPersonCameraComponent() const { return FirstPersonCameraComponent; }

private:
	// bool InteractionOn;

	APostProcessVolume* MainPostProcessVolume;
	FPostProcessSettings* settings;

	FOnTimelineFloat BlankCallback;
	FOnTimelineEvent BlankTimelineFinish;
	UPROPERTY()
	UTimelineComponent* BlankTimeline;
	UPROPERTY(EditAnywhere, Category = "Timeline")
	UCurveFloat* BlankCurve;

	UFUNCTION()
	void BlankInterpReturn(float value);
	UFUNCTION()
	void BlankFinish();

protected:
	void Apparition();

	void Footstep();
	bool CanFootstep;
	float FootstepValue;
	float FVolume = 1.0f;
	class USoundCue* WoodCue;
	class USoundCue* CarpetCue;

public:
	UPROPERTY(EditAnywhere)
	ACharacterBody* BodyMesh;

	void FSoundp();
	void FSoundd();
	void FSoundq();
	virtual void Tick(float DeltaTime) override;
	void CheckDead();
// 상호작용
public:
	void Interaction();
	void InteractionCheck();

private:
	class ACapstoneObject* CheckedObject = nullptr;
	class ADoor* CheckedDoor = nullptr;
	class AFireplace* CheckedFireplace = nullptr;
	class ASanityRecovery* CheckedSanityRecovery = nullptr;
	class ACharacterBody* CheckedBody = nullptr;

	FHitResult HitActor;
	

	UGameInstance* CapstoneGameInstance;
	UCapstoneSubsystem* CapstoneGameSubsystem;

	/*
	* UI
	*/
public:
	void SettingUI();
	// void EndingUI();

	float GetSanity();
	void SetSanity(float value);

	UPROPERTY(BlueprintReadWrite)
	float Sanity = 100;

	UPROPERTY(BlueprintReadWrite)
	bool ApparitionMode;

private:
	UPROPERTY()
	class ACapstoneController* CapstoneController;

	UPROPERTY()
	class UCapstoneSettingUI* SettingWidget = nullptr;

	bool IsClear = false;
};

