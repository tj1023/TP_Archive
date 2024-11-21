// Fill out your copyright notice in the Description page of Project Settings.


#include "TOWeapon.h"

// Sets default values
ATOWeapon::ATOWeapon()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	/*
	*  무기 관련 생성자
	*/
	Weapon = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("WEAPON"));
	RootComponent = Weapon;

	static ConstructorHelpers::FObjectFinder<UStaticMesh> SM_WEAPON(TEXT("/Game/Weapon_Pack/Mesh/Weapons/Weapons_Kit/SM_Sword.SM_Sword"));
	if (SM_WEAPON.Succeeded())
	{
		Weapon->SetStaticMesh(SM_WEAPON.Object);
	}
	
	// 콜리전 무시되도록 설정
	Weapon->SetCollisionProfileName(TEXT("NoCollision"));
}

// Called when the game starts or when spawned
void ATOWeapon::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ATOWeapon::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

