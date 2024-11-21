// Fill out your copyright notice in the Description page of Project Settings.


#include "TOSkillWidget.h"
#include "UMG.h"
#include "TOPlayerController.h"
#include "TOCharacter.h"
#include "TOAnimInstance.h"
#include "TOFireball.h"

/*
* 기본 생성자
*/
void UTOSkillWidget::NativeConstruct()
{
	Super::NativeConstruct();

	TOAnim = Cast<UTOAnimInstance>(GetWorld()->GetFirstPlayerController()->GetCharacter()->GetMesh()->GetAnimInstance());

	bIsButtonCallbackEnabled = true;
	IsShield_CoolDown = false;
	IsSkill_1_CoolDown = false;
	IsSkill_2_CoolDown = false;
	IsSkill_3_CoolDown = false;
	IsSkill_4_CoolDown = false;

	Button_Background = Cast<UButton>(GetWidgetFromName(TEXT("Skill_Background")));
	Button_Shield = Cast<UButton>(GetWidgetFromName(TEXT("Button_Center")));
	Button_Skill_1 = Cast<UButton>(GetWidgetFromName(TEXT("Button_1")));
	Button_Skill_2 = Cast<UButton>(GetWidgetFromName(TEXT("Button_2")));
	Button_Skill_3 = Cast<UButton>(GetWidgetFromName(TEXT("Button_3")));
	Button_Skill_4 = Cast<UButton>(GetWidgetFromName(TEXT("Button_4")));

	BindButtonClickEvents();

	TOPlayerController = Cast<ATOPlayerController>(GetWorld()->GetFirstPlayerController());
	TOCharacter = Cast<ATOCharacter>(TOPlayerController->GetPawn());
	CharacterStat = TOCharacter->GetCharacterStatComponent();
}


/*
* 스킬 창 On일 시, 마우스 움직임 확인 후 스킬을 지정.
*/
void UTOSkillWidget::BindButtonClickEvents()
{
	Button_Background->OnClicked.Clear();
	Button_Shield->OnClicked.Clear();
	Button_Skill_1->OnClicked.Clear();
	Button_Skill_2->OnClicked.Clear();
	Button_Skill_3->OnClicked.Clear();
	Button_Skill_4->OnClicked.Clear();

	Button_Background->OnClicked.AddDynamic(this, &UTOSkillWidget::ButtonClicked_Background);
	Button_Shield->OnClicked.AddDynamic(this, &UTOSkillWidget::ButtonClicked_Shield);
	Button_Skill_1->OnClicked.AddDynamic(this, &UTOSkillWidget::ButtonClicked_Skill_1);
	Button_Skill_2->OnClicked.AddDynamic(this, &UTOSkillWidget::ButtonClicked_Skill_2);
	Button_Skill_3->OnClicked.AddDynamic(this, &UTOSkillWidget::ButtonClicked_Skill_3);
	Button_Skill_4->OnClicked.AddDynamic(this, &UTOSkillWidget::ButtonClicked_Skill_4);
}

void UTOSkillWidget::ButtonClicked_Background()
{
	// 배경이 눌렸을 시 UI 끄기
	TOCharacter->SetIsSkillUIOpened();
	TOPlayerController->SkillButton_Clicked();
}

void UTOSkillWidget::ButtonClicked_Shield()
{
	if (!IsShield_CoolDown)
	{
		TOCharacter->SetIsSkillUIOpened();
		TOPlayerController->SkillButton_Clicked();

		IsShield_CoolDown = true;

		ABLOG(Warning, TEXT("Shield Skill CoolDown Start"));
		GetWorld()->GetTimerManager().SetTimer(TimerHandle_Shield, FTimerDelegate::CreateLambda([&]()
			{
				ABLOG(Warning, TEXT("Shield Skill CoolDown End"));
				IsShield_CoolDown = false;
			}), 5.0f, false);
		CharacterStat->SetMP(CharacterStat->GetCurrentMP() - 10);
	}
	else
	{
		ABLOG(Warning, TEXT("Shield Skill CoolDown"));
	}
}

void UTOSkillWidget::ButtonClicked_Skill_1() 
{
	if (!IsSkill_1_CoolDown)
	{
		TOCharacter->SetIsSkillUIOpened();
		TOPlayerController->SkillButton_Clicked();

		FActorSpawnParameters SpawnParams;
		SpawnParams.Owner = TOCharacter;

		FVector FireballLocation = TOCharacter->GetActorLocation() + TOCharacter->GetActorForwardVector() * 50.0f;

		GetWorld()->SpawnActor<ATOFireball>(ATOFireball::StaticClass(), FireballLocation, TOCharacter->GetActorRotation(), SpawnParams);

		IsSkill_1_CoolDown = true;

		ABLOG(Warning, TEXT("Skill 1 CoolDown Start"));
		GetWorld()->GetTimerManager().SetTimer(TimerHandle_SKill_1, FTimerDelegate::CreateLambda([&]()
			{
				ABLOG(Warning, TEXT("Skill 1 CoolDown End"));
				IsSkill_1_CoolDown = false;
			}), 5.0f, false);
		CharacterStat->SetMP(CharacterStat->GetCurrentMP() - 10);
	}
	else
	{
		ABLOG(Warning, TEXT("Skill 1 CoolDown"));
	}

}

void UTOSkillWidget::ButtonClicked_Skill_2()
{
	if (!IsSkill_2_CoolDown)
	{
		TOCharacter->SetIsSkillUIOpened();
		TOPlayerController->SkillButton_Clicked();

		IsSkill_2_CoolDown = true;

		TOCharacter->GetCharacterMovement()->MaxWalkSpeed = 100.0f;
		TOAnim->PlaySkill2Animation();

		ABLOG(Warning, TEXT("Skill 2 CoolDown Start"));
		GetWorld()->GetTimerManager().SetTimer(TimerHandle_SKill_2, FTimerDelegate::CreateLambda([&]()
			{
				ABLOG(Warning, TEXT("Skill 2 CoolDown End"));
				IsSkill_2_CoolDown = false;
			}), 5.0f, false);
		CharacterStat->SetMP(CharacterStat->GetCurrentMP() - 10);
	}
	else
	{
		ABLOG(Warning, TEXT("Skill 2 CoolDown"));
	}
}

void UTOSkillWidget::ButtonClicked_Skill_3()
{
	if (!IsSkill_3_CoolDown)
	{
		TOCharacter->SetIsSkillUIOpened();
		TOPlayerController->SkillButton_Clicked();

		IsSkill_3_CoolDown = true;

		TOCharacter->GetCharacterMovement()->MaxWalkSpeed = 100.0f;
		TOAnim->PlaySkill3Animation();

		ABLOG(Warning, TEXT("Skill 3 CoolDown Start"));
		GetWorld()->GetTimerManager().SetTimer(TimerHandle_SKill_3, FTimerDelegate::CreateLambda([&]()
			{
				ABLOG(Warning, TEXT("Skill 3 CoolDown End"));
				IsSkill_3_CoolDown = false;
			}), 5.0f, false);
		CharacterStat->SetMP(CharacterStat->GetCurrentMP() - 10);
	}
	else
	{
		ABLOG(Warning, TEXT("Skill 3 CoolDown"));
	}
}

void UTOSkillWidget::ButtonClicked_Skill_4()
{
	if (!IsSkill_4_CoolDown)
	{
		TOCharacter->SetIsSkillUIOpened();
		TOPlayerController->SkillButton_Clicked();

		IsSkill_4_CoolDown = true;

		TOCharacter->GetCharacterMovement()->MaxWalkSpeed = 0.0f;
		TOCharacter->ShowEffect();

		TOAnim->PlayShieldAnimation();

		ABLOG(Warning, TEXT("Skill 4 CoolDown Start"));
		GetWorld()->GetTimerManager().SetTimer(TimerHandle_SKill_4, FTimerDelegate::CreateLambda([&]()
			{
				ABLOG(Warning, TEXT("Skill 4 CoolDown End"));
				IsSkill_4_CoolDown = false;
			}), 5.0f, false);
		CharacterStat->SetMP(CharacterStat->GetCurrentMP() - 10);
	}
	else
	{
		ABLOG(Warning, TEXT("Skill 4 CoolDown"));
	}
}