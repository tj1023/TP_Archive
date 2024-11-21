// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Tellours.h"
#include "GameFramework/Actor.h"
#include "Blueprint/UserWidget.h"
#include "TOTeleport.generated.h"

UCLASS()
class TELLOURS_API ATOTeleport : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ATOTeleport();

	/*void PostInitializeComponents() override;*/

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

// Level 생성 확인
public:
	enum EActionId
	{
		AID_Loading,
	};

	enum ELinkID
	{
		LID_Link
	};

	FLatentActionInfo LatentActionInfo;

	UFUNCTION() 
		void OnStreamLevelLoaded();

// 텔레포트 관련
public:
	UPROPERTY(VisibleAnywhere, Category = Teleport)
		UStaticMeshComponent* TeleportMesh;

	UFUNCTION()
		void Teleport();

	void SetCurrentLevel(FName CurrentLevelValue);
	void SetTeleportDestinationLevel(FName TeleportDestinationLevelValue);
	void SetTeleportLocation(FVector TeleportLocationValue);
	void SetNeedProgress(int32 NeedProgressValue);

private:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Teleport, meta = (AllowPrivateAccess = "true"))
		FName CurrentLevel;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Teleport, meta = (AllowPrivateAccess = "true"))
		FName TeleportDestinationLevel;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Teleport, meta = (AllowPrivateAccess = "true"))
		FVector TeleportLocation;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Teleport, meta = (AllowPrivateAccess = "true"))
		int32 NeedProgress;

// Light
private:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Light", meta = (AllowPrivateAccess = "true"))
		USpotLightComponent* SpotLightComponent;

// 상호작용
public:
	UPROPERTY(VisibleAnywhere, Category = UI)
		class UWidgetComponent* InteractionWidget;

	void SetInteractionUIVisible(bool NewBool);


// 로딩화면 Test
private:
	UPROPERTY()
		class UUserWidget* TestWidget;

	UPROPERTY()
		TSubclassOf<class UUserWidget> TestWidgetClass;
};
