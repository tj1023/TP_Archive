// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CapstoneObject.h"
#include "CapstoneSubObject.generated.h"

/**
 *
 */
UCLASS()
class CAPSTONE_API ACapstoneSubObject : public ACapstoneObject
{
	GENERATED_BODY()

public:
	ACapstoneSubObject();

	virtual void SetHumanForm(int32 n) override;
	virtual void SetApparitionForm(int32 n) override;
	virtual int32 GetApparitionKey() override;
	void BathRoom(void);
	void StorageRoom(void);
	void Restaurant(void);
	void LibraryRoom(void);
	void SmallObject(void);
	void BigObject(void);
private:
	// Human Form
	int32 Num_BathRoom_Mesh;
	TArray<UStaticMesh*> BathRoom_Mesh;
	TArray<int32> InGame_BathRoom_Mesh;

	int32 Num_StorageRoom_Mesh;
	TArray<UStaticMesh*> StorageRoom_Mesh;
	TArray<int32> InGame_StorageRoom_Mesh;

	int32 Num_Restaurant_Mesh;
	TArray<UStaticMesh*> Restaurant_Mesh;
	TArray<int32> InGame_Restaurant_Mesh;

	int32 Num_LibraryRoom_Mesh;
	TArray<UStaticMesh*> LibraryRoom_Mesh;
	TArray<int32> InGame_LibraryRoom_Mesh;

	int32 Num_Small_Mesh;
	TArray<UStaticMesh*> Small_Mesh;
	TArray<int32> InGame_Small_Mesh;

	int32 Num_Big_Mesh;
	TArray<UStaticMesh*> Big_Mesh;
	TArray<int32> InGame_Big_Mesh;

	// Key
	int32 MyKey = 0;
};
