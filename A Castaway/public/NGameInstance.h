// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "ProjectN.h"
#include "Engine/DataTable.h"
#include "Engine/GameInstance.h"
#include "NGameInstance.generated.h"


/*
* 스크립트 csv 로드
*/
USTRUCT(BlueprintType)
struct FScript : public FTableRowBase
{
	GENERATED_BODY()

public:
	FScript() : Text(""), A1(""), Joy1(0), Sad1(0), Fear1(0), Anger1(0), NextScriptNum1(0), A2(""), Joy2(0), Sad2(0), Fear2(0), Anger2(0), NextScriptNum2(0), Fix(0) {}
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
		FString Text;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
		FString A1;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
		float Joy1;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
		float Sad1;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
		float Fear1;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
		float Anger1;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
		int32 NextScriptNum1;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
		FString A2;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
		float Joy2;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
		float Sad2;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
		float Fear2;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
		float Anger2;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
		int32 NextScriptNum2;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
		int32 Fix;
};

/**
 *
 */
UCLASS()
class PROJECTN_API UNGameInstance : public UGameInstance
{
	GENERATED_BODY()

public:
	UNGameInstance();

	FScript* GetScriptData(FString ScriptNnum);

	// 11.10 - 필요 시 추가 후 사용
	//virtual void Init() override;

private:
	UPROPERTY()
		class UDataTable* ScriptTable;
};