// 플레이어의 진행 상황 기록

#pragma once

#include "Tellours.h"
#include "GameFramework/PlayerState.h"
#include "TOPlayerState.generated.h"

/**
 * 
 */
UCLASS()
class TELLOURS_API ATOPlayerState : public APlayerState
{
	GENERATED_BODY()

public:
	ATOPlayerState();

	void InitPlayerData();
	void SavePlayerData(FString LevelName);

	FString SaveSlotName;

private:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = SaveData, Meta = (AllowPrivateAccess = "true"))
		FName MapName;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = SaveData, Meta = (AllowPrivateAccess = "true"))
		int32 Progress;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = SaveData, Meta = (AllowPrivateAccess = "true"))
		FVector PlayerLocation;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = SaveData, Meta = (AllowPrivateAccess = "true"))
		int32 HP;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = SaveData, Meta = (AllowPrivateAccess = "true"))
		int32 Level;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = SaveData, Meta = (AllowPrivateAccess = "true"))
		TArray<int32> InventoryItemCount;

// 맵 시작 레벨 및 진행도 설정
public:
	UFUNCTION()
		void OnStreamLevelLoaded();

	UFUNCTION()
		int32 GetProgress();

private:
	FLatentActionInfo LatentActionInfo;
};
