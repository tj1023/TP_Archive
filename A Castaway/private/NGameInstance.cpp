// Fill out your copyright notice in the Description page of Project Settings.


#include "NGameInstance.h"

UNGameInstance::UNGameInstance()
{
	// 스크립트 데이터
	FString ScriptPath = TEXT("/Game/GameData/Script.Script");
	static ConstructorHelpers::FObjectFinder<UDataTable> DT_Script(*ScriptPath);
	NCHECK(DT_Script.Succeeded());
	ScriptTable = DT_Script.Object;
}

// 11.10 - 필요 시 추가 후 사용
//void UNGameInstance::Init()
//{
//	Super::Init(); 
//
//}

/*
* Script 테이블 행 데이터 반환
*/
FScript* UNGameInstance::GetScriptData(FString ScriptNnum)
{
	return ScriptTable->FindRow<FScript>(*ScriptNnum, TEXT(""));
}