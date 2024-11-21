// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "CapstoneCharacter.h"
#include "CapstoneGhost.generated.h"

UCLASS()
class CAPSTONE_API ACapstoneGhost : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ACapstoneGhost();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void TouchCharacter();

	UPROPERTY(EditAnywhere, Category = "Animation")
	UAnimSequence* Anim_Idle;

	class USoundCue* DisappearSound;
};
