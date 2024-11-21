// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"

#include "CapstoneHUDWidget.h"

#include "CapstoneObject.generated.h"

UENUM(BlueprintType)
enum class ERoomType : uint8 {
	MAINROOM UMETA(DisplayName = "MainRoom"),
	BATHROOM UMETA(DisplayName = "BathRoom"),
	STORAGE UMETA(DisplayName = "Storage"),
	RESTAURANT UMETA(DisplayName = "Restaurant"),
	LIBRARY UMETA(DisplayName = "Library"),
	SMALL UMETA(DisplayName = "SmallObject"),
	BIG UMETA(DisplayName = "BigObject"),
	TEST UMETA(DisplayName = "TestObject")
};

UCLASS()
class CAPSTONE_API ACapstoneObject : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ACapstoneObject();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

public:
	UPROPERTY(VisibleAnywhere, Category = Mesh)
	UStaticMeshComponent* Mesh;

// 상호작용 UI
public:
	UPROPERTY(VisibleAnywhere, Category = UI)
	class UWidgetComponent* InteractionWidget;

	void Interaction();
	void SetInteractionUIVisible(bool NewBool);

public:
	virtual void SetHumanForm(int32 n) {};
	virtual void SetApparitionForm(int32 n) {};
	virtual int32 GetApparitionKey() { return 0; };
	void RandForm();
	void SetApparitionMode(bool Mode);
	int32 GetHumanForm();
	int32 GetApparitionForm();
	int32 GetKey();
	UPROPERTY(EditAnywhere, Category = RoomType)
		ERoomType TypeName;

protected:
	UPROPERTY(EditAnywhere, Category = Variable)
	int32 MaxForm;

private:
	int32 HumanForm;
	int32 ApparitionForm;
	bool ApparitionMode;
	int32 Key;
	UCapstoneHUDWidget* HUDWidget;
};
