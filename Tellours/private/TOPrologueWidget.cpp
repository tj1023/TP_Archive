// Fill out your copyright notice in the Description page of Project Settings.


#include "TOPrologueWidget.h"
#include "TOGameInstance.h"
#include "EngineUtils.h"
#include "Animation/SkeletalMeshActor.h"
#include "Components/Button.h"
#include "Components/EditableTextBox.h"
#include "TOSaveGame.h"
#include "TOPlayerState.h"

void UTOPrologueWidget::NativeConstruct()
{
	StartButton = Cast<UButton>(GetWidgetFromName(TEXT("btnStart")));
	ABCHECK(nullptr != StartButton);

	StartButton->OnClicked.AddDynamic(this, &UTOPrologueWidget::OnStartClicked);
}

void UTOPrologueWidget::OnStartClicked()
{
	UTOSaveGame* NewPlayerData = NewObject<UTOSaveGame>();
	NewPlayerData->Level = 1;

	auto TOPlayerState = GetDefault<ATOPlayerState>();
	if (UGameplayStatics::SaveGameToSlot(NewPlayerData, TOPlayerState->SaveSlotName, 0))
	{
		UGameplayStatics::OpenLevel(GetWorld(), TEXT("HTJ"));
	}
	else
	{
		ABLOG(Error, TEXT("SaveGame Error!"));
	}
}
