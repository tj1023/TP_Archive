// Fill out your copyright notice in the Description page of Project Settings.


#include "NGameInstance.h"

UNGameInstance::UNGameInstance()
{
	// ��ũ��Ʈ ������
	FString ScriptPath = TEXT("/Game/GameData/Script.Script");
	static ConstructorHelpers::FObjectFinder<UDataTable> DT_Script(*ScriptPath);
	NCHECK(DT_Script.Succeeded());
	ScriptTable = DT_Script.Object;
}

// 11.10 - �ʿ� �� �߰� �� ���
//void UNGameInstance::Init()
//{
//	Super::Init(); 
//
//}

/*
* Script ���̺� �� ������ ��ȯ
*/
FScript* UNGameInstance::GetScriptData(FString ScriptNnum)
{
	return ScriptTable->FindRow<FScript>(*ScriptNnum, TEXT(""));
}