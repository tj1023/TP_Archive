// Fill out your copyright notice in the Description page of Project Settings.


#include "TOInventory.h"
#include "UMG.h"
#include "TOPlayerController.h"
#include "TOCharacter.h"
#include "TOCharacterStatComponent.h"

/*
* 기본 생성자
*/
void UTOInventory::NativeConstruct()
{
	Super::NativeConstruct();

	// 아이템 갯수, 버튼, 이미지 초기화
	AInventoryItemCount.Add(Cast<UTextBlock>(GetWidgetFromName(TEXT("T_InventorySlotCount_1"))));
	AInventoryItemCount.Add(Cast<UTextBlock>(GetWidgetFromName(TEXT("T_InventorySlotCount_2"))));
	AInventoryItemCount.Add(Cast<UTextBlock>(GetWidgetFromName(TEXT("T_InventorySlotCount_3"))));
	AInventoryItemCount.Add(Cast<UTextBlock>(GetWidgetFromName(TEXT("T_InventorySlotCount_4"))));
	AInventoryItemCount.Add(Cast<UTextBlock>(GetWidgetFromName(TEXT("T_InventorySlotCount_5"))));

	AInventoryButton.Add(Cast<UButton>(GetWidgetFromName(TEXT("B_InventorySlotButton_1"))));
	AInventoryButton.Add(Cast<UButton>(GetWidgetFromName(TEXT("B_InventorySlotButton_2"))));
	AInventoryButton.Add(Cast<UButton>(GetWidgetFromName(TEXT("B_InventorySlotButton_3"))));
	AInventoryButton.Add(Cast<UButton>(GetWidgetFromName(TEXT("B_InventorySlotButton_4"))));
	AInventoryButton.Add(Cast<UButton>(GetWidgetFromName(TEXT("B_InventorySlotButton_5"))));

	AInventoryImage.Add(Cast<UImage>(GetWidgetFromName(TEXT("ZeroImage_1"))));
	AInventoryImage.Add(Cast<UImage>(GetWidgetFromName(TEXT("ZeroImage_2"))));
	AInventoryImage.Add(Cast<UImage>(GetWidgetFromName(TEXT("ZeroImage_3"))));
	AInventoryImage.Add(Cast<UImage>(GetWidgetFromName(TEXT("ZeroImage_4"))));
	AInventoryImage.Add(Cast<UImage>(GetWidgetFromName(TEXT("ZeroImage_5"))));

	AInventoryButton[0]->OnClicked.Clear();
	AInventoryButton[1]->OnClicked.Clear();
	AInventoryButton[2]->OnClicked.Clear();
	AInventoryButton[3]->OnClicked.Clear();
	AInventoryButton[4]->OnClicked.Clear();

	// 버튼 함수 등록
	AInventoryButton[0]->OnClicked.AddDynamic(this, &UTOInventory::SlotClickEvent0);
	AInventoryButton[1]->OnClicked.AddDynamic(this, &UTOInventory::SlotClickEvent1);
	AInventoryButton[2]->OnClicked.AddDynamic(this, &UTOInventory::SlotClickEvent2);
	AInventoryButton[3]->OnClicked.AddDynamic(this, &UTOInventory::SlotClickEvent3);
	AInventoryButton[4]->OnClicked.AddDynamic(this, &UTOInventory::SlotClickEvent4);

	TOPlayerController = Cast<ATOPlayerController>(GetWorld()->GetFirstPlayerController());
	TOCharacter = Cast<ATOCharacter>(TOPlayerController->GetPawn());

	// 갯수 초기화
	InitInventoryItemCount();

	TOCharacter->CharacterStat->OnItem0AddDelegate.AddLambda([this]() -> void { ItemAdd(0); });
	TOCharacter->CharacterStat->OnItem1AddDelegate.AddLambda([this]() -> void { ItemAdd(1); });
	TOCharacter->CharacterStat->OnItem2AddDelegate.AddLambda([this]() -> void { ItemAdd(2); });
	TOCharacter->CharacterStat->OnItem3AddDelegate.AddLambda([this]() -> void { ItemAdd(3); });
	TOCharacter->CharacterStat->OnItem4AddDelegate.AddLambda([this]() -> void { ItemAdd(4); });
}

void UTOInventory::ItemUse(int32 ItemNum)
{
	if (InventoryItemCount[ItemNum] <= 0)
		return;

	InventoryItemCount[ItemNum]--;
	AInventoryItemCount[ItemNum]->SetText(FText::FromString(FString::FromInt(InventoryItemCount[ItemNum])));
	TOCharacter->CharacterStat->SetInventoryItemCount(InventoryItemCount);

	switch (ItemNum)
	{
	case 0:
		TOCharacter->ItemUse(20.0f);
		break;
	case 1:
		TOCharacter->ItemUse(50.0f);
		break;
	case 2:
		TOCharacter->ItemUse(-20.0f);
		break;
	case 3:
		TOCharacter->ItemUse(-50.0f);
		break;
	}
}

void  UTOInventory::ItemAdd(int32 ItemNum)
{
	if (InventoryItemCount[ItemNum] == 999)
		return;

	InventoryItemCount[ItemNum]++;
	AInventoryItemCount[ItemNum]->SetText(FText::FromString(FString::FromInt(InventoryItemCount[ItemNum])));
	TOCharacter->CharacterStat->SetInventoryItemCount(InventoryItemCount);
	CheckItemCount(ItemNum);
}

void UTOInventory::InitInventoryItemCount()
{
	InventoryItemCount = TOCharacter->CharacterStat->GetInventoryItemCount();

	for (int32 index = 0; index < 5; index++)
	{
		AInventoryItemCount[index]->SetText(FText::FromString(FString::FromInt(InventoryItemCount[index])));
		CheckItemCount(index);
		//if (InventoryItemCount[index] != 0)
		//	AInventoryImage[index]->SetVisibility(ESlateVisibility::Hidden);
	}
}

void UTOInventory::CheckItemCount(int32 ItemNum)
{
	if (InventoryItemCount[ItemNum] == 0)
		AInventoryImage[ItemNum]->SetVisibility(ESlateVisibility::Visible);
	else
		AInventoryImage[ItemNum]->SetVisibility(ESlateVisibility::Hidden);
}

void UTOInventory::SlotClickEvent0()
{
	ItemUse(0);
	CheckItemCount(0);
}

void UTOInventory::SlotClickEvent1()
{
	ItemUse(1);
	CheckItemCount(1);
}

void UTOInventory::SlotClickEvent2()
{
	ItemUse(2);
	CheckItemCount(2);
}

void UTOInventory::SlotClickEvent3()
{
	ItemUse(3);
	CheckItemCount(3);
}

void UTOInventory::SlotClickEvent4()
{
	ItemUse(4);
	CheckItemCount(4);
}
