// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Tellours.h"
#include "GameFramework/Actor.h"
#include "TOFireball.generated.h"

UCLASS()
class TELLOURS_API ATOFireball : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ATOFireball();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;


// Particle
public:
	UPROPERTY(VisibleAnywhere, Category = Fireball)
		USphereComponent* Fireball;

	UPROPERTY(VisibleAnywhere, Category = Effect)
		UParticleSystemComponent* FireballEffect;

	UPROPERTY(VisibleAnywhere, Category = Effect)
		UParticleSystem* FireballHitEffect;

protected:
	virtual void NotifyHit(UPrimitiveComponent* MyComp, AActor* Other, UPrimitiveComponent* OtherComp, bool bSelfMoved, FVector HitLocation, FVector HitNormal, FVector NormalImpulse, const FHitResult& Hit) override;

private:
	float SkillLength;

	FVector StartVector;
};
