// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Tellours.h"
#include "GameFramework/Actor.h"
#include "Level2Field1.generated.h"


//DECLARE_MULTICAST_DELEGATE(Phase1EndDelegate);
//DECLARE_MULTICAST_DELEGATE(Phase2EndDelegate);
//DECLARE_MULTICAST_DELEGATE(Phase3EndDelegate);


UCLASS()
class TELLOURS_API ALevel2Field1 : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ALevel2Field1();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

// Äù½ºÆ®
public:
	UPROPERTY(VisibleAnywhere, Category = Item)
		UStaticMeshComponent* TV;

	UPROPERTY(VisibleAnywhere, Category = UI)
		class UWidgetComponent* InteractionWidget;

	bool Phase1End;
	bool Phase2End;
	bool Phase3End;

	bool GetPhase1End();
	bool GetPhase2End();
	bool GetPhase3End();

	void SetInteractionUIVisible(bool NewBool);

	void Phase1();
	void Phase2();
	void Phase3();

	/*Phase1EndDelegate Phase1End;
	Phase2EndDelegate Phase2End;
	Phase3EndDelegate Phase3End;*/
};
