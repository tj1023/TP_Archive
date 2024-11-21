// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Tellours.h"
#include "GameFramework/Character.h"
#include "TONPC.generated.h"



/*
* NPC �з��� ���� UENUM ������ ����
*/
UENUM()
enum class NPCType {
	DEER
};



UCLASS()
class TELLOURS_API ATONPC : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ATONPC();

	// �ε巯�� ȸ��
	virtual void PossessedBy(AController* NewController) override;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

// NPC �з�
public:
	void SetNPCType(NPCType NewNPCType);

private:
	UPROPERTY(EditAnywhere, Category = NPC, Meta = (AllowPrivateAccess = true))
		NPCType UserNPCType;

// ��ȣ�ۿ�
public:
	UPROPERTY(VisibleAnywhere, Category = UI)
		class UWidgetComponent* InteractionWidget;

	void SetInteractionUIVisible(bool NewBool);

// ����Ʈ
public:
	bool GetQuestClear();
	void SetQuestClear(bool IsClear);
	bool GetQuestProgress();
	void SetQuestProgress(bool IsProgress);
	void QuestReward();

private:
	bool QuestClear;
	bool QuestProgress;
};
