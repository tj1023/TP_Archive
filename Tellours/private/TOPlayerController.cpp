// Fill out your copyright notice in the Description page of Project Settings.


#include "TOPlayerController.h"
#include "TOHUDWidget.h"
#include "TOSkillWidget.h"
#include "TOInventory.h"
#include "TOScript.h"
#include "TOSaveScript.h"
#include "TOSettingWidget.h"
#include "TOCharacterStatComponent.h"
#include "TOCharacter.h"

ATOPlayerController::ATOPlayerController()
{
	ABLOG_S(Warning);
	// 스킬 창 구성 및 마우스 설정
	static ConstructorHelpers::FClassFinder<UUserWidget> UI_SKILL(TEXT("/Game/Tellours/Developer/UI/UI_SkillTool.UI_SkillTool_C"));
	if (UI_SKILL.Succeeded())
	{
		SkillWidgetClass = UI_SKILL.Class;
	}
	IsSkillButtonClicked = false;
	UISkillVisible = false;

	// 인벤토리
	static ConstructorHelpers::FClassFinder<UUserWidget> UI_Inventory(TEXT("/Game/Tellours/Developer/UI/UI_Inventory.UI_Inventory_C"));
	if (UI_Inventory.Succeeded())
	{
		InventoryClass = UI_Inventory.Class;
	}
	UIInventoryVisible = false;

	// 스크립트
	static ConstructorHelpers::FClassFinder<UUserWidget> UI_Script(TEXT("/Game/Tellours/Developer/UI/UI_Script.UI_Script_C"));
	if (UI_Script.Succeeded())
	{
		ScriptClass = UI_Script.Class;
	}
	UIScriptVisible = false;

	// CheckPoint 스크립트
	static ConstructorHelpers::FClassFinder<UUserWidget> UI_SaveScript(TEXT("/Game/Tellours/Developer/UI/UI_SaveScript.UI_SaveScript_C"));
	if (UI_SaveScript.Succeeded())
	{
		SaveScriptClass = UI_SaveScript.Class;
	}
	UIChekPointScriptVisible = false;

	// 세팅 UI
	static ConstructorHelpers::FClassFinder<UUserWidget> UI_Setting(TEXT("/Game/Tellours/Developer/UI/UI_Setting.UI_Setting_C"));
	if (UI_Setting.Succeeded())
	{
		SettingWidgetClass = UI_Setting.Class;
	}

	// HUD
	static ConstructorHelpers::FClassFinder<UTOHUDWidget> UI_HUD_C(TEXT("/Game/Tellours/Developer/UI/UI_HUD.UI_HUD_C"));
	if (UI_HUD_C.Succeeded())
	{
		HUDWidgetClass = UI_HUD_C.Class;
	}
}



/*
*  기본 함수들
*/
void ATOPlayerController::BeginPlay()
{
	Super::BeginPlay();

	FInputModeGameOnly Mode;
	SetInputMode(Mode);
	bShowMouseCursor = false;

	SkillWidget = CreateWidget<UTOSkillWidget>(this, SkillWidgetClass);
	SkillWidget->AddToViewport();
	SkillWidget->SetVisibility(ESlateVisibility::Collapsed);

	InventoryWidget = CreateWidget<UTOInventory>(this, InventoryClass);
	InventoryWidget->AddToViewport();
	InventoryWidget->SetVisibility(ESlateVisibility::Hidden);

	ScriptWidget = CreateWidget<UTOScript>(this, ScriptClass);
	ScriptWidget->AddToViewport();
	ScriptWidget->SetVisibility(ESlateVisibility::Collapsed);

	SaveScriptWidget = CreateWidget<UTOSaveScript>(this, SaveScriptClass);
	SaveScriptWidget->AddToViewport();
	SaveScriptWidget->SetVisibility(ESlateVisibility::Collapsed);

	SettingWidget = CreateWidget<UTOSettingWidget>(this, SettingWidgetClass);
	SettingWidget->AddToViewport();
	SettingWidget->SetVisibility(ESlateVisibility::Collapsed);

	HUDWidget = CreateWidget<UTOHUDWidget>(this, HUDWidgetClass);
	HUDWidget->AddToViewport();
}



/*
*  스킬 창 구성
*/
void ATOPlayerController::ShowSkillUI()
{
	// 우선순위 체크
	if (UIChekPointScriptVisible)
		return;

	UISkillVisible = true;
	if (UIInventoryVisible)
		CloseInventoryUI();

	// 스크린 사이즈를 구해서, 커서를 가운데로 옮긴다.
	FVector2D ScreenSize = FVector2D(GEngine->GameViewport->Viewport->GetSizeXY());
	SetMouseLocation(ScreenSize.X / 2, ScreenSize.Y / 2);

	// 화면 움직임 input 제거 및 마우스 표현
	SetIgnoreLookInput(true);
	GetWorld()->GetFirstPlayerController()->SetShowMouseCursor(true);
	SetInputMode(FInputModeGameAndUI());

	IsSkillButtonClicked = true;

	// 위젯 보이게 하기
	SkillWidget->SetVisibility(ESlateVisibility::Visible);

	//슬로우 모션 설정
	UGameplayStatics::SetGlobalTimeDilation(GetWorld(), 0.3f);
}

void ATOPlayerController::RemoveSkillUI()
{
	UISkillVisible = false;
	// 화면 움직임 input 추가 및 마우스 표현
	SetIgnoreLookInput(false);
	GetWorld()->GetFirstPlayerController()->SetShowMouseCursor(false);
	SetInputMode(FInputModeGameOnly());

	IsSkillButtonClicked = false;

	// 위젯 지우기
	SkillWidget->SetVisibility(ESlateVisibility::Collapsed);

	//슬로우 모션 해제
	UGameplayStatics::SetGlobalTimeDilation(GetWorld(), 1.0f);
}

void ATOPlayerController::SkillButton_Clicked()
{
	RemoveSkillUI();
}



/*
* 인벤토리
*/
void ATOPlayerController::OpenInventoryUI()
{
	if (UISkillVisible) {
		ABLOG(Warning, TEXT("Skill Is already open"));
		return;
	}

	if (UIInventoryVisible) {
		ABLOG(Warning, TEXT("Inventory Is already open"));
		CloseInventoryUI();
		return;
	}
		
	UIInventoryVisible = true;
	GetWorld()->GetFirstPlayerController()->SetShowMouseCursor(true);
	InventoryWidget->SetVisibility(ESlateVisibility::Visible);
	SetInputMode(FInputModeGameAndUI());
}

void ATOPlayerController::CloseInventoryUI()
{
	if (UIInventoryVisible == false) {
		ABLOG(Warning, TEXT("Inventory Is already close"));
		return;
	}

	UIInventoryVisible = false;
	GetWorld()->GetFirstPlayerController()->SetShowMouseCursor(false);
	InventoryWidget->SetVisibility(ESlateVisibility::Collapsed);
	SetInputMode(FInputModeGameOnly());
}



/*
* Script
*/
void ATOPlayerController::ShowScriptUI()
{
	// 우선순위 체크
	if (UIInventoryVisible)
		CloseInventoryUI();
	if (UISkillVisible)
		RemoveSkillUI();
	UIScriptVisible = true;
	
	// 스크립트 띄우기
	SetPause(true);
	GetWorld()->GetFirstPlayerController()->SetShowMouseCursor(true);
	ScriptWidget->SetVisibility(ESlateVisibility::Visible);
	SetInputMode(FInputModeUIOnly());
}

void ATOPlayerController::CloseScriptUI()
{
	UIScriptVisible = false;
	SetPause(false);
	GetWorld()->GetFirstPlayerController()->SetShowMouseCursor(false);
	ScriptWidget->SetVisibility(ESlateVisibility::Collapsed);
	SetInputMode(FInputModeGameOnly());
}

void ATOPlayerController::ShowSaveScriptUI()
{
	UIChekPointScriptVisible = true;
	ABLOG_S(Warning);
	SaveScriptWidget->SetVisibility(ESlateVisibility::Visible);
	SetInputMode(FInputModeGameOnly());
	
	FTimerHandle SaveScriptTimerHandle;

	GetWorld()->GetTimerManager().SetTimer(SaveScriptTimerHandle, FTimerDelegate::CreateLambda([&]()
		{
			ABLOG_S(Warning);
			UIChekPointScriptVisible = false;
			SaveScriptWidget->SetVisibility(ESlateVisibility::Collapsed);
			GetWorld()->GetTimerManager().ClearTimer(SaveScriptTimerHandle);
		}), 4.0f, false);
}


/*
* Setting UI
*/
void ATOPlayerController::ShowSettingUI()
{
	SetPause(true);
	GetWorld()->GetFirstPlayerController()->SetShowMouseCursor(true);
	SetInputMode(FInputModeGameAndUI());

	SettingWidget->SetVisibility(ESlateVisibility::Visible);
	
}

void ATOPlayerController::RemoveSettingUI()
{
	SetPause(false);
	GetWorld()->GetFirstPlayerController()->SetShowMouseCursor(false);
	SetInputMode(FInputModeGameOnly());

	SettingWidget->SetVisibility(ESlateVisibility::Collapsed);
}



/*
* HUD
*/
UTOHUDWidget* ATOPlayerController::GetHUDWidget() const
{
	return HUDWidget;
}
