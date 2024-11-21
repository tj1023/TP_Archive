// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Tellours.h"
#include "Blueprint/UserWidget.h"
#include "TOCharacterWidget.generated.h"

/**
 * 
 */
UCLASS()
class TELLOURS_API UTOCharacterWidget : public UUserWidget
{
	GENERATED_BODY()
	
protected:
	virtual void NativeConstruct() override;
	
// Ω∫≈» πŸ¿ŒµÂ	
public:
	void BindCharacterStat(class UTOCharacterStatComponent* NewCharacterStat);
	void BindEnemyStat(class UTOEnemyStatComponent* NewEnemyStat);
	void BindBossStat(class UTOBossStatComponent* NewBossStat);

protected:
	void UpdateHPWidget();

private:
	TWeakObjectPtr<class UTOCharacterStatComponent> CurrentCharacterStat;
	TWeakObjectPtr<class UTOEnemyStatComponent> CurrentEnemyStat;
	TWeakObjectPtr<class UTOBossStatComponent> CurrentBossStat;

	UPROPERTY()
		class UProgressBar* HPProgressBar;
};
