// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/CapsuleComponent.h"
#include "CharacterBody.generated.h"

UCLASS()
class CAPSTONE_API ACharacterBody : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ACharacterBody();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(VisibleDefaultsOnly, Category = Mesh)
	USkeletalMeshComponent* SK_Body;

	UPROPERTY(EditAnywhere, Category = "Animation")
	UAnimSequence* Anim_Idle;

	UPROPERTY(EditAnywhere)
	UCapsuleComponent* Capsule;
};
