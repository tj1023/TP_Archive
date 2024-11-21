// Fill out your copyright notice in the Description page of Project Settings.


#include "TONPC.h"
#include "Components/WidgetComponent.h"
#include "TOAINPCController.h"
#include "TOItem.h"

// Sets default values
ATONPC::ATONPC()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	SetNPCType(UserNPCType);
	GetMesh()->SetRelativeLocationAndRotation(FVector(0.0f, 0.0f, -88.0f), FRotator(0.0f, -90.0f, 0.0f));
	GetMesh()->SetAnimationMode(EAnimationMode::AnimationBlueprint);

	//AI 컨트롤러 설정
	AIControllerClass = ATOAINPCController::StaticClass();
	AutoPossessAI = EAutoPossessAI::PlacedInWorldOrSpawned;

	// 상호작용UI
	InteractionWidget = CreateDefaultSubobject<UWidgetComponent>(TEXT("INTERACTIONWIDGET"));
	InteractionWidget->SetupAttachment(GetMesh());
	InteractionWidget->SetRelativeLocation(FVector(0, 0, 200));
	InteractionWidget->SetWidgetSpace(EWidgetSpace::Screen);
	static ConstructorHelpers::FClassFinder<UUserWidget> UI_Interaction(TEXT("/Game/Tellours/Developer/UI/UI_Interaction.UI_Interaction_C"));
	if (UI_Interaction.Succeeded())
	{
		InteractionWidget->SetWidgetClass(UI_Interaction.Class);
		InteractionWidget->SetDrawSize(FVector2D(50, 40));
	}
	InteractionWidget->SetVisibility(false);

	// 퀘스트
	QuestClear = false;
	QuestProgress = false;
}

// Called when the game starts or when spawned
void ATONPC::BeginPlay()
{
	Super::BeginPlay();
	
}



/*
* 부드러운 회전
*/
void ATONPC::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);

	// 부드러운 회전
	bUseControllerRotationYaw = false;
	GetCharacterMovement()->bUseControllerDesiredRotation = false;
	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->RotationRate = FRotator(0, 480, 0);
}



/*
* 상호작용 UI
*/
void ATONPC::SetInteractionUIVisible(bool NewBool)
{
	InteractionWidget->SetVisibility(NewBool);
}



/*
* 퀘스트
*/
bool ATONPC::GetQuestClear()
{
	return QuestClear;
}

void ATONPC::SetQuestClear(bool IsClear)
{
	QuestClear = IsClear;
}

bool ATONPC::GetQuestProgress()
{
	return QuestProgress;
}

void ATONPC::SetQuestProgress(bool IsProgress)
{
	QuestProgress = IsProgress;
}

void ATONPC::QuestReward()
{
	ATOItem* DropedItem = (ATOItem*)GetWorld()->SpawnActor<ATOItem>(GetActorLocation() + FVector(10, 0, 0), FRotator::ZeroRotator);
	DropedItem->ItemDrop();
}



/*
* NPC 분류
*/
void ATONPC::SetNPCType(NPCType NewNPCType)
{
	switch (NewNPCType) {

	case NPCType::DEER: {
		USkeletalMesh* SK_Deer = Cast< USkeletalMesh >(StaticLoadObject(USkeletalMesh::StaticClass(), NULL, TEXT("/Game/AnimalVarietyPack/DeerStagAndDoe/Meshes/SK_DeerStag.SK_DeerStag")));
		if (SK_Deer)
		{
			GetMesh()->SetSkeletalMesh(SK_Deer);
		}

		static ConstructorHelpers::FClassFinder<UAnimInstance> Deer_Anim(TEXT("/Game/Tellours/Developer/Animations/DeerAnimBlueprint.DeerAnimBlueprint_C"));
		if (Deer_Anim.Succeeded())
		{
			GetMesh()->SetAnimInstanceClass(Deer_Anim.Class);
		}

		GetCharacterMovement()->MaxWalkSpeed = 200;
		
		break;
	}
	/*case NPCType:: {

	}*/

	}
}
