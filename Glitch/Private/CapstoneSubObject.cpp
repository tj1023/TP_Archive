// Fill out your copyright notice in the Description page of Project Settings.


#include "CapstoneSubObject.h"

ACapstoneSubObject::ACapstoneSubObject()
{
	Num_BathRoom_Mesh = 26;
	Num_StorageRoom_Mesh = 26;
	Num_Restaurant_Mesh = 26;
	Num_LibraryRoom_Mesh = 26;
	Num_Small_Mesh = 13;
	Num_Big_Mesh = 14;

	MyKey = FMath::RandRange(1, MaxForm - 1);
	// init func
	BathRoom();
	StorageRoom();
	Restaurant();
	LibraryRoom();
	SmallObject();
	BigObject();
}


void ACapstoneSubObject::SetHumanForm(int32 n)
{
	UStaticMesh* SM_Mesh;
	if (TypeName == ERoomType::BATHROOM)
	{
		SM_Mesh = BathRoom_Mesh[InGame_BathRoom_Mesh[n]];

		if (SM_Mesh)
		{
			Mesh->SetStaticMesh(SM_Mesh);
			Mesh->SetWorldScale3D(FVector(1.2f, 1.2f, 1.2f));
		}
	}
	else if (TypeName == ERoomType::STORAGE)
	{
		SM_Mesh = StorageRoom_Mesh[InGame_StorageRoom_Mesh[n]];

		if (SM_Mesh)
		{
			Mesh->SetStaticMesh(SM_Mesh);
			Mesh->SetWorldScale3D(FVector(1.2f, 1.2f, 1.2f));
		}
	}
	else if (TypeName == ERoomType::RESTAURANT)
	{
		SM_Mesh = Restaurant_Mesh[InGame_Restaurant_Mesh[n]];

		if (SM_Mesh)
		{
			Mesh->SetStaticMesh(SM_Mesh);
			Mesh->SetWorldScale3D(FVector(1.2f, 1.2f, 1.2f));
		}
	}
	else if (TypeName == ERoomType::LIBRARY)
	{
		SM_Mesh = LibraryRoom_Mesh[InGame_LibraryRoom_Mesh[n]];

		if (SM_Mesh)
		{
			Mesh->SetStaticMesh(SM_Mesh);
			Mesh->SetWorldScale3D(FVector(1.2f, 1.2f, 1.2f));
		}
	}
	else if (TypeName == ERoomType::MAINROOM)
	{
		SM_Mesh = BathRoom_Mesh[InGame_BathRoom_Mesh[n]];

		if (SM_Mesh)
		{
			Mesh->SetStaticMesh(SM_Mesh);
			Mesh->SetWorldScale3D(FVector(1.2f, 1.2f, 1.2f));
		}
	}
	else if (TypeName == ERoomType::SMALL)
	{
		SM_Mesh = Small_Mesh[InGame_Small_Mesh[n]];

		if (SM_Mesh)
		{
			Mesh->SetStaticMesh(SM_Mesh);
			Mesh->SetWorldScale3D(FVector(1.2f, 1.2f, 1.2f));
		}
	}
	else if (TypeName == ERoomType::BIG)
	{
		SM_Mesh = Big_Mesh[InGame_Big_Mesh[n]];

		if (SM_Mesh)
		{
			Mesh->SetStaticMesh(SM_Mesh);
			Mesh->SetWorldScale3D(FVector(1.2f, 1.2f, 1.2f));
		}
	}
	else if (TypeName == ERoomType::TEST)
	{
		SM_Mesh = Cast<UStaticMesh>(StaticLoadObject(UStaticMesh::StaticClass(), NULL, TEXT("/Game/SICKA_mansion/StaticMeshes/SM_BrooklynChairSingle.SM_BrooklynChairSingle")));

		if (SM_Mesh)
		{
			Mesh->SetStaticMesh(SM_Mesh);
			Mesh->SetWorldScale3D(FVector(1.2f, 1.2f, 1.2f));
		}
	}
}

void ACapstoneSubObject::SetApparitionForm(int32 n)
{
	UStaticMesh* SM_Mesh;

	if (TypeName == ERoomType::BATHROOM)
	{
		SM_Mesh = BathRoom_Mesh[InGame_BathRoom_Mesh[n]];

		if (SM_Mesh)
		{
			Mesh->SetStaticMesh(SM_Mesh);
			Mesh->SetWorldScale3D(FVector(1.2f, 1.2f, 1.2f));
		}
	}
	else if (TypeName == ERoomType::STORAGE)
	{
		SM_Mesh = StorageRoom_Mesh[InGame_StorageRoom_Mesh[n]];

		if (SM_Mesh)
		{
			Mesh->SetStaticMesh(SM_Mesh);
			Mesh->SetWorldScale3D(FVector(1.2f, 1.2f, 1.2f));
		}
	}
	else if (TypeName == ERoomType::RESTAURANT)
	{
		SM_Mesh = Restaurant_Mesh[InGame_Restaurant_Mesh[n]];

		if (SM_Mesh)
		{
			Mesh->SetStaticMesh(SM_Mesh);
			Mesh->SetWorldScale3D(FVector(1.2f, 1.2f, 1.2f));
		}
	}
	else if (TypeName == ERoomType::LIBRARY)
	{
		SM_Mesh = LibraryRoom_Mesh[InGame_LibraryRoom_Mesh[n]];

		if (SM_Mesh)
		{
			Mesh->SetStaticMesh(SM_Mesh);
			Mesh->SetWorldScale3D(FVector(1.2f, 1.2f, 1.2f));
		}
	}
	else if (TypeName == ERoomType::MAINROOM)
	{
		SM_Mesh = BathRoom_Mesh[InGame_BathRoom_Mesh[n]];

		if (SM_Mesh)
		{
			Mesh->SetStaticMesh(SM_Mesh);
			Mesh->SetWorldScale3D(FVector(1.2f, 1.2f, 1.2f));
		}
	}
	else if (TypeName == ERoomType::SMALL)
	{
		SM_Mesh = Small_Mesh[InGame_Small_Mesh[n]];

		if (SM_Mesh)
		{
			Mesh->SetStaticMesh(SM_Mesh);
			Mesh->SetWorldScale3D(FVector(1.2f, 1.2f, 1.2f));
		}
	}
	else if (TypeName == ERoomType::BIG)
	{
		SM_Mesh = Big_Mesh[InGame_Big_Mesh[n]];

		if (SM_Mesh)
		{
			Mesh->SetStaticMesh(SM_Mesh);
			Mesh->SetWorldScale3D(FVector(1.2f, 1.2f, 1.2f));
		}
	}
	else if (TypeName == ERoomType::TEST)
	{
		SM_Mesh = Cast<UStaticMesh>(StaticLoadObject(UStaticMesh::StaticClass(), NULL, TEXT("/Game/SICKA_mansion/StaticMeshes/SM_BrooklynChairSingle.SM_BrooklynChairSingle")));

		if (SM_Mesh)
		{
			Mesh->SetStaticMesh(SM_Mesh);
			Mesh->SetWorldScale3D(FVector(1.2f, 1.2f, 1.2f));
		}
	}
}

int32 ACapstoneSubObject::GetApparitionKey()
{
	return MyKey;
}

void ACapstoneSubObject::BathRoom(void)
{
	// init array
	InGame_BathRoom_Mesh.Init(0, 7);

	// Human Form 일때 나왔으면 하는 메쉬들 리스트.
	// BathRoom_Mesh.Add(Cast<UStaticMesh>(StaticLoadObject(UStaticMesh::StaticClass(), NULL, TEXT("매쉬 주소")))); 
	// 형식으로 붙여넣고, Num_BathRoom_Mesh를 증가시킬 것(필수)
	BathRoom_Mesh.Add(Cast<UStaticMesh>(StaticLoadObject(UStaticMesh::StaticClass(), NULL, TEXT("/Game/Victorian_House/Meshes/DecorativeElements/Mesh_Newspapers.Mesh_Newspapers"))));
	BathRoom_Mesh.Add(Cast<UStaticMesh>(StaticLoadObject(UStaticMesh::StaticClass(), NULL, TEXT("/Game/SICKA_mansion/StaticMeshes/SM_Candlesticktrihead.SM_Candlesticktrihead"))));
	BathRoom_Mesh.Add(Cast<UStaticMesh>(StaticLoadObject(UStaticMesh::StaticClass(), NULL, TEXT("/Game/SICKA_mansion/StaticMeshes/SM_CupidStatue.SM_CupidStatue"))));
	BathRoom_Mesh.Add(Cast<UStaticMesh>(StaticLoadObject(UStaticMesh::StaticClass(), NULL, TEXT("/Game/SICKA_mansion/StaticMeshes/SM_MansionLamp.SM_MansionLamp"))));
	BathRoom_Mesh.Add(Cast<UStaticMesh>(StaticLoadObject(UStaticMesh::StaticClass(), NULL, TEXT("/Game/SICKA_mansion/StaticMeshes/SM_SteampunkGear1.SM_SteampunkGear1"))));
	BathRoom_Mesh.Add(Cast<UStaticMesh>(StaticLoadObject(UStaticMesh::StaticClass(), NULL, TEXT("/Game/SICKA_mansion/StaticMeshes/SM_WingedLion.SM_WingedLion"))));
	BathRoom_Mesh.Add(Cast<UStaticMesh>(StaticLoadObject(UStaticMesh::StaticClass(), NULL, TEXT("/Game/SICKA_mansion/StaticMeshes/SM_StandBox.SM_StandBox"))));
	BathRoom_Mesh.Add(Cast<UStaticMesh>(StaticLoadObject(UStaticMesh::StaticClass(), NULL, TEXT("/Game/SICKA_mansion/StaticMeshes/SM_Bottle4.SM_Bottle4"))));
	BathRoom_Mesh.Add(Cast<UStaticMesh>(StaticLoadObject(UStaticMesh::StaticClass(), NULL, TEXT("/Game/SICKA_mansion/StaticMeshes/SM_BreadCreamSliced.SM_BreadCreamSliced"))));
	BathRoom_Mesh.Add(Cast<UStaticMesh>(StaticLoadObject(UStaticMesh::StaticClass(), NULL, TEXT("/Game/SICKA_mansion/StaticMeshes/SM_BookPile7.SM_BookPile7"))));
	BathRoom_Mesh.Add(Cast<UStaticMesh>(StaticLoadObject(UStaticMesh::StaticClass(), NULL, TEXT("/Game/SICKA_mansion/StaticMeshes/SM_Candlestickfourside.SM_Candlestickfourside"))));
	BathRoom_Mesh.Add(Cast<UStaticMesh>(StaticLoadObject(UStaticMesh::StaticClass(), NULL, TEXT("/Game/SICKA_mansion/StaticMeshes/SM_Plate.SM_Plate"))));
	BathRoom_Mesh.Add(Cast<UStaticMesh>(StaticLoadObject(UStaticMesh::StaticClass(), NULL, TEXT("/Game/SICKA_mansion/StaticMeshes/SM_WoodMannequin.SM_WoodMannequin"))));
	BathRoom_Mesh.Add(Cast<UStaticMesh>(StaticLoadObject(UStaticMesh::StaticClass(), NULL, TEXT("/Game/SICKA_mansion/StaticMeshes/SM_TravelCase_Basic.SM_TravelCase_Basic"))));
	BathRoom_Mesh.Add(Cast<UStaticMesh>(StaticLoadObject(UStaticMesh::StaticClass(), NULL, TEXT("/Game/SICKA_mansion/StaticMeshes/SM_PaintingMedium.SM_PaintingMedium"))));
	BathRoom_Mesh.Add(Cast<UStaticMesh>(StaticLoadObject(UStaticMesh::StaticClass(), NULL, TEXT("/Game/SICKA_mansion/StaticMeshes/SM_TillFrame_Pack1.SM_TillFrame_Pack1"))));
	BathRoom_Mesh.Add(Cast<UStaticMesh>(StaticLoadObject(UStaticMesh::StaticClass(), NULL, TEXT("/Game/SICKA_mansion/StaticMeshes/SM_SteampunkGear3.SM_SteampunkGear3"))));
	BathRoom_Mesh.Add(Cast<UStaticMesh>(StaticLoadObject(UStaticMesh::StaticClass(), NULL, TEXT("/Game/SICKA_mansion/StaticMeshes/SM_SteampunkGear2.SM_SteampunkGear2"))));
	BathRoom_Mesh.Add(Cast<UStaticMesh>(StaticLoadObject(UStaticMesh::StaticClass(), NULL, TEXT("/Game/SICKA_mansion/StaticMeshes/SM_RoundBread.SM_RoundBread"))));
	BathRoom_Mesh.Add(Cast<UStaticMesh>(StaticLoadObject(UStaticMesh::StaticClass(), NULL, TEXT("/Game/SICKA_mansion/StaticMeshes/SM_Gramophone.SM_Gramophone"))));
	BathRoom_Mesh.Add(Cast<UStaticMesh>(StaticLoadObject(UStaticMesh::StaticClass(), NULL, TEXT("/Game/SICKA_mansion/StaticMeshes/SM_Globe.SM_Globe"))));
	BathRoom_Mesh.Add(Cast<UStaticMesh>(StaticLoadObject(UStaticMesh::StaticClass(), NULL, TEXT("/Game/SICKA_mansion/StaticMeshes/SM_KnightArmorPoseCloth.SM_KnightArmorPoseCloth"))));
	BathRoom_Mesh.Add(Cast<UStaticMesh>(StaticLoadObject(UStaticMesh::StaticClass(), NULL, TEXT("/Game/SICKA_mansion/StaticMeshes/SM_FireToolsStickHolder.SM_FireToolsStickHolder"))));
	BathRoom_Mesh.Add(Cast<UStaticMesh>(StaticLoadObject(UStaticMesh::StaticClass(), NULL, TEXT("/Game/SICKA_mansion/StaticMeshes/SM_CurtainFlower_Gurad.SM_CurtainFlower_Gurad"))));
	BathRoom_Mesh.Add(Cast<UStaticMesh>(StaticLoadObject(UStaticMesh::StaticClass(), NULL, TEXT("/Game/SICKA_mansion/StaticMeshes/SM_CarpaneseChairMaster.SM_CarpaneseChairMaster"))));
	BathRoom_Mesh.Add(Cast<UStaticMesh>(StaticLoadObject(UStaticMesh::StaticClass(), NULL, TEXT("/Game/SICKA_mansion/StaticMeshes/SM_Bottle1.SM_Bottle1"))));
	// Num_BathRoom_Mesh = 26

	InGame_BathRoom_Mesh[0] = FMath::RandRange(0, Num_BathRoom_Mesh - 1);
	InGame_BathRoom_Mesh[MyKey] = InGame_BathRoom_Mesh[0];
	int CurIndex;
	for (int32 i = 1; i < 7; i++)
	{
		if (i == MyKey)
			continue;

		do {
			CurIndex = FMath::RandRange(0, Num_BathRoom_Mesh - 1);
		} while (InGame_BathRoom_Mesh.Contains(CurIndex));

		InGame_BathRoom_Mesh[i] = CurIndex;
	}
}
void ACapstoneSubObject::StorageRoom(void)
{
	// init array
	InGame_StorageRoom_Mesh.Init(0, 7);

	// Human Form 일때 나왔으면 하는 메쉬들 리스트.
	// StorageRoom_Mesh.Add(Cast<UStaticMesh>(StaticLoadObject(UStaticMesh::StaticClass(), NULL, TEXT("매쉬 주소")))); 
	// 형식으로 붙여넣고, Num_StorageRoom_Mesh를 증가시킬 것(필수)
	StorageRoom_Mesh.Add(Cast<UStaticMesh>(StaticLoadObject(UStaticMesh::StaticClass(), NULL, TEXT("/Game/Victorian_House/Meshes/DecorativeElements/Mesh_Newspapers.Mesh_Newspapers"))));
	StorageRoom_Mesh.Add(Cast<UStaticMesh>(StaticLoadObject(UStaticMesh::StaticClass(), NULL, TEXT("/Game/SICKA_mansion/StaticMeshes/SM_Candlesticktrihead.SM_Candlesticktrihead"))));
	StorageRoom_Mesh.Add(Cast<UStaticMesh>(StaticLoadObject(UStaticMesh::StaticClass(), NULL, TEXT("/Game/SICKA_mansion/StaticMeshes/SM_CupidStatue.SM_CupidStatue"))));
	StorageRoom_Mesh.Add(Cast<UStaticMesh>(StaticLoadObject(UStaticMesh::StaticClass(), NULL, TEXT("/Game/SICKA_mansion/StaticMeshes/SM_MansionLamp.SM_MansionLamp"))));
	StorageRoom_Mesh.Add(Cast<UStaticMesh>(StaticLoadObject(UStaticMesh::StaticClass(), NULL, TEXT("/Game/SICKA_mansion/StaticMeshes/SM_SteampunkGear1.SM_SteampunkGear1"))));
	StorageRoom_Mesh.Add(Cast<UStaticMesh>(StaticLoadObject(UStaticMesh::StaticClass(), NULL, TEXT("/Game/SICKA_mansion/StaticMeshes/SM_WingedLion.SM_WingedLion"))));
	StorageRoom_Mesh.Add(Cast<UStaticMesh>(StaticLoadObject(UStaticMesh::StaticClass(), NULL, TEXT("/Game/SICKA_mansion/StaticMeshes/SM_StandBox.SM_StandBox"))));
	StorageRoom_Mesh.Add(Cast<UStaticMesh>(StaticLoadObject(UStaticMesh::StaticClass(), NULL, TEXT("/Game/SICKA_mansion/StaticMeshes/SM_Bottle4.SM_Bottle4"))));
	StorageRoom_Mesh.Add(Cast<UStaticMesh>(StaticLoadObject(UStaticMesh::StaticClass(), NULL, TEXT("/Game/SICKA_mansion/StaticMeshes/SM_BreadCreamSliced.SM_BreadCreamSliced"))));
	StorageRoom_Mesh.Add(Cast<UStaticMesh>(StaticLoadObject(UStaticMesh::StaticClass(), NULL, TEXT("/Game/SICKA_mansion/StaticMeshes/SM_BookPile7.SM_BookPile7"))));
	StorageRoom_Mesh.Add(Cast<UStaticMesh>(StaticLoadObject(UStaticMesh::StaticClass(), NULL, TEXT("/Game/SICKA_mansion/StaticMeshes/SM_Candlestickfourside.SM_Candlestickfourside"))));
	StorageRoom_Mesh.Add(Cast<UStaticMesh>(StaticLoadObject(UStaticMesh::StaticClass(), NULL, TEXT("/Game/SICKA_mansion/StaticMeshes/SM_Plate.SM_Plate"))));
	StorageRoom_Mesh.Add(Cast<UStaticMesh>(StaticLoadObject(UStaticMesh::StaticClass(), NULL, TEXT("/Game/SICKA_mansion/StaticMeshes/SM_WoodMannequin.SM_WoodMannequin"))));
	StorageRoom_Mesh.Add(Cast<UStaticMesh>(StaticLoadObject(UStaticMesh::StaticClass(), NULL, TEXT("/Game/SICKA_mansion/StaticMeshes/SM_TravelCase_Basic.SM_TravelCase_Basic"))));
	StorageRoom_Mesh.Add(Cast<UStaticMesh>(StaticLoadObject(UStaticMesh::StaticClass(), NULL, TEXT("/Game/SICKA_mansion/StaticMeshes/SM_PaintingMedium.SM_PaintingMedium"))));
	StorageRoom_Mesh.Add(Cast<UStaticMesh>(StaticLoadObject(UStaticMesh::StaticClass(), NULL, TEXT("/Game/SICKA_mansion/StaticMeshes/SM_TillFrame_Pack1.SM_TillFrame_Pack1"))));
	StorageRoom_Mesh.Add(Cast<UStaticMesh>(StaticLoadObject(UStaticMesh::StaticClass(), NULL, TEXT("/Game/SICKA_mansion/StaticMeshes/SM_SteampunkGear3.SM_SteampunkGear3"))));
	StorageRoom_Mesh.Add(Cast<UStaticMesh>(StaticLoadObject(UStaticMesh::StaticClass(), NULL, TEXT("/Game/SICKA_mansion/StaticMeshes/SM_SteampunkGear2.SM_SteampunkGear2"))));
	StorageRoom_Mesh.Add(Cast<UStaticMesh>(StaticLoadObject(UStaticMesh::StaticClass(), NULL, TEXT("/Game/SICKA_mansion/StaticMeshes/SM_RoundBread.SM_RoundBread"))));
	StorageRoom_Mesh.Add(Cast<UStaticMesh>(StaticLoadObject(UStaticMesh::StaticClass(), NULL, TEXT("/Game/SICKA_mansion/StaticMeshes/SM_Gramophone.SM_Gramophone"))));
	StorageRoom_Mesh.Add(Cast<UStaticMesh>(StaticLoadObject(UStaticMesh::StaticClass(), NULL, TEXT("/Game/SICKA_mansion/StaticMeshes/SM_Globe.SM_Globe"))));
	StorageRoom_Mesh.Add(Cast<UStaticMesh>(StaticLoadObject(UStaticMesh::StaticClass(), NULL, TEXT("/Game/SICKA_mansion/StaticMeshes/SM_KnightArmorPoseCloth.SM_KnightArmorPoseCloth"))));
	StorageRoom_Mesh.Add(Cast<UStaticMesh>(StaticLoadObject(UStaticMesh::StaticClass(), NULL, TEXT("/Game/SICKA_mansion/StaticMeshes/SM_FireToolsStickHolder.SM_FireToolsStickHolder"))));
	StorageRoom_Mesh.Add(Cast<UStaticMesh>(StaticLoadObject(UStaticMesh::StaticClass(), NULL, TEXT("/Game/SICKA_mansion/StaticMeshes/SM_CurtainFlower_Gurad.SM_CurtainFlower_Gurad"))));
	StorageRoom_Mesh.Add(Cast<UStaticMesh>(StaticLoadObject(UStaticMesh::StaticClass(), NULL, TEXT("/Game/SICKA_mansion/StaticMeshes/SM_CarpaneseChairMaster.SM_CarpaneseChairMaster"))));
	StorageRoom_Mesh.Add(Cast<UStaticMesh>(StaticLoadObject(UStaticMesh::StaticClass(), NULL, TEXT("/Game/SICKA_mansion/StaticMeshes/SM_Bottle1.SM_Bottle1"))));
	// Num_StorageRoom_Mesh = 26

	InGame_StorageRoom_Mesh[0] = FMath::RandRange(0, Num_StorageRoom_Mesh - 1);
	InGame_StorageRoom_Mesh[MyKey] = InGame_StorageRoom_Mesh[0];
	int CurIndex;
	for (int32 i = 1; i < 7; i++)
	{
		if (i == MyKey)
			continue;

		do {
			CurIndex = FMath::RandRange(0, Num_StorageRoom_Mesh - 1);
		} while (InGame_StorageRoom_Mesh.Contains(CurIndex));

		InGame_StorageRoom_Mesh[i] = CurIndex;
	}
}
void ACapstoneSubObject::Restaurant(void)
{
	// init array
	InGame_Restaurant_Mesh.Init(0, 7);

	// Human Form 일때 나왔으면 하는 메쉬들 리스트.
	// StorageRoom_Mesh.Add(Cast<UStaticMesh>(StaticLoadObject(UStaticMesh::StaticClass(), NULL, TEXT("매쉬 주소")))); 
	// 형식으로 붙여넣고, Num_StorageRoom_Mesh를 증가시킬 것(필수)
	Restaurant_Mesh.Add(Cast<UStaticMesh>(StaticLoadObject(UStaticMesh::StaticClass(), NULL, TEXT("/Game/Victorian_House/Meshes/DecorativeElements/Mesh_Newspapers.Mesh_Newspapers"))));
	Restaurant_Mesh.Add(Cast<UStaticMesh>(StaticLoadObject(UStaticMesh::StaticClass(), NULL, TEXT("/Game/SICKA_mansion/StaticMeshes/SM_Candlesticktrihead.SM_Candlesticktrihead"))));
	Restaurant_Mesh.Add(Cast<UStaticMesh>(StaticLoadObject(UStaticMesh::StaticClass(), NULL, TEXT("/Game/SICKA_mansion/StaticMeshes/SM_CupidStatue.SM_CupidStatue"))));
	Restaurant_Mesh.Add(Cast<UStaticMesh>(StaticLoadObject(UStaticMesh::StaticClass(), NULL, TEXT("/Game/SICKA_mansion/StaticMeshes/SM_Gramophone.SM_Gramophone"))));
	Restaurant_Mesh.Add(Cast<UStaticMesh>(StaticLoadObject(UStaticMesh::StaticClass(), NULL, TEXT("/Game/SICKA_mansion/StaticMeshes/SM_MansionLamp.SM_MansionLamp"))));
	Restaurant_Mesh.Add(Cast<UStaticMesh>(StaticLoadObject(UStaticMesh::StaticClass(), NULL, TEXT("/Game/SICKA_mansion/StaticMeshes/SM_SteampunkGear1.SM_SteampunkGear1"))));
	Restaurant_Mesh.Add(Cast<UStaticMesh>(StaticLoadObject(UStaticMesh::StaticClass(), NULL, TEXT("/Game/SICKA_mansion/StaticMeshes/SM_WingedLion.SM_WingedLion"))));
	Restaurant_Mesh.Add(Cast<UStaticMesh>(StaticLoadObject(UStaticMesh::StaticClass(), NULL, TEXT("/Game/SICKA_mansion/StaticMeshes/SM_StandBox.SM_StandBox"))));
	Restaurant_Mesh.Add(Cast<UStaticMesh>(StaticLoadObject(UStaticMesh::StaticClass(), NULL, TEXT("/Game/SICKA_mansion/StaticMeshes/SM_Bottle4.SM_Bottle4"))));
	Restaurant_Mesh.Add(Cast<UStaticMesh>(StaticLoadObject(UStaticMesh::StaticClass(), NULL, TEXT("/Game/SICKA_mansion/StaticMeshes/SM_BreadCreamSliced.SM_BreadCreamSliced"))));
	Restaurant_Mesh.Add(Cast<UStaticMesh>(StaticLoadObject(UStaticMesh::StaticClass(), NULL, TEXT("/Game/SICKA_mansion/StaticMeshes/SM_BookPile7.SM_BookPile7"))));
	Restaurant_Mesh.Add(Cast<UStaticMesh>(StaticLoadObject(UStaticMesh::StaticClass(), NULL, TEXT("/Game/SICKA_mansion/StaticMeshes/SM_Candlestickfourside.SM_Candlestickfourside"))));
	Restaurant_Mesh.Add(Cast<UStaticMesh>(StaticLoadObject(UStaticMesh::StaticClass(), NULL, TEXT("/Game/SICKA_mansion/StaticMeshes/SM_Plate.SM_Plate"))));
	Restaurant_Mesh.Add(Cast<UStaticMesh>(StaticLoadObject(UStaticMesh::StaticClass(), NULL, TEXT("/Game/SICKA_mansion/StaticMeshes/SM_WoodMannequin.SM_WoodMannequin"))));
	Restaurant_Mesh.Add(Cast<UStaticMesh>(StaticLoadObject(UStaticMesh::StaticClass(), NULL, TEXT("/Game/SICKA_mansion/StaticMeshes/SM_TravelCase_Basic.SM_TravelCase_Basic"))));
	Restaurant_Mesh.Add(Cast<UStaticMesh>(StaticLoadObject(UStaticMesh::StaticClass(), NULL, TEXT("/Game/SICKA_mansion/StaticMeshes/SM_PaintingMedium.SM_PaintingMedium"))));
	Restaurant_Mesh.Add(Cast<UStaticMesh>(StaticLoadObject(UStaticMesh::StaticClass(), NULL, TEXT("/Game/SICKA_mansion/StaticMeshes/SM_TillFrame_Pack1.SM_TillFrame_Pack1"))));
	Restaurant_Mesh.Add(Cast<UStaticMesh>(StaticLoadObject(UStaticMesh::StaticClass(), NULL, TEXT("/Game/SICKA_mansion/StaticMeshes/SM_SteampunkGear3.SM_SteampunkGear3"))));
	Restaurant_Mesh.Add(Cast<UStaticMesh>(StaticLoadObject(UStaticMesh::StaticClass(), NULL, TEXT("/Game/SICKA_mansion/StaticMeshes/SM_SteampunkGear2.SM_SteampunkGear2"))));
	Restaurant_Mesh.Add(Cast<UStaticMesh>(StaticLoadObject(UStaticMesh::StaticClass(), NULL, TEXT("/Game/SICKA_mansion/StaticMeshes/SM_RoundBread.SM_RoundBread"))));
	Restaurant_Mesh.Add(Cast<UStaticMesh>(StaticLoadObject(UStaticMesh::StaticClass(), NULL, TEXT("/Game/SICKA_mansion/StaticMeshes/SM_Globe.SM_Globe"))));
	Restaurant_Mesh.Add(Cast<UStaticMesh>(StaticLoadObject(UStaticMesh::StaticClass(), NULL, TEXT("/Game/SICKA_mansion/StaticMeshes/SM_KnightArmorPoseCloth.SM_KnightArmorPoseCloth"))));
	Restaurant_Mesh.Add(Cast<UStaticMesh>(StaticLoadObject(UStaticMesh::StaticClass(), NULL, TEXT("/Game/SICKA_mansion/StaticMeshes/SM_FireToolsStickHolder.SM_FireToolsStickHolder"))));
	Restaurant_Mesh.Add(Cast<UStaticMesh>(StaticLoadObject(UStaticMesh::StaticClass(), NULL, TEXT("/Game/SICKA_mansion/StaticMeshes/SM_CurtainFlower_Gurad.SM_CurtainFlower_Gurad"))));
	Restaurant_Mesh.Add(Cast<UStaticMesh>(StaticLoadObject(UStaticMesh::StaticClass(), NULL, TEXT("/Game/SICKA_mansion/StaticMeshes/SM_CarpaneseChairMaster.SM_CarpaneseChairMaster"))));
	Restaurant_Mesh.Add(Cast<UStaticMesh>(StaticLoadObject(UStaticMesh::StaticClass(), NULL, TEXT("/Game/SICKA_mansion/StaticMeshes/SM_Bottle1.SM_Bottle1"))));
	// Num_Restaurant_Mesh = 26

	InGame_Restaurant_Mesh[0] = FMath::RandRange(0, Num_Restaurant_Mesh - 1);
	InGame_Restaurant_Mesh[MyKey] = InGame_Restaurant_Mesh[0];
	int CurIndex;
	for (int32 i = 1; i < 7; i++)
	{
		if (i == MyKey)
			continue;

		do {
			CurIndex = FMath::RandRange(0, Num_Restaurant_Mesh - 1);
		} while (InGame_Restaurant_Mesh.Contains(CurIndex));

		InGame_Restaurant_Mesh[i] = CurIndex;
	}
}
void ACapstoneSubObject::LibraryRoom(void)
{
	// init array
	InGame_LibraryRoom_Mesh.Init(0, 7);

	// Human Form 일때 나왔으면 하는 메쉬들 리스트.
	// LibraryRoom_Mesh.Add(Cast<UStaticMesh>(StaticLoadObject(UStaticMesh::StaticClass(), NULL, TEXT("매쉬 주소")))); 
	// 형식으로 붙여넣고, Num_LibraryRoom_Mesh를 증가시킬 것(필수)
	LibraryRoom_Mesh.Add(Cast<UStaticMesh>(StaticLoadObject(UStaticMesh::StaticClass(), NULL, TEXT("/Game/Victorian_House/Meshes/DecorativeElements/Mesh_Newspapers.Mesh_Newspapers"))));
	LibraryRoom_Mesh.Add(Cast<UStaticMesh>(StaticLoadObject(UStaticMesh::StaticClass(), NULL, TEXT("/Game/SICKA_mansion/StaticMeshes/SM_Candlesticktrihead.SM_Candlesticktrihead"))));
	LibraryRoom_Mesh.Add(Cast<UStaticMesh>(StaticLoadObject(UStaticMesh::StaticClass(), NULL, TEXT("/Game/SICKA_mansion/StaticMeshes/SM_CupidStatue.SM_CupidStatue"))));
	LibraryRoom_Mesh.Add(Cast<UStaticMesh>(StaticLoadObject(UStaticMesh::StaticClass(), NULL, TEXT("/Game/SICKA_mansion/StaticMeshes/SM_Gramophone.SM_Gramophone"))));
	LibraryRoom_Mesh.Add(Cast<UStaticMesh>(StaticLoadObject(UStaticMesh::StaticClass(), NULL, TEXT("/Game/SICKA_mansion/StaticMeshes/SM_MansionLamp.SM_MansionLamp"))));
	LibraryRoom_Mesh.Add(Cast<UStaticMesh>(StaticLoadObject(UStaticMesh::StaticClass(), NULL, TEXT("/Game/SICKA_mansion/StaticMeshes/SM_SteampunkGear1.SM_SteampunkGear1"))));
	LibraryRoom_Mesh.Add(Cast<UStaticMesh>(StaticLoadObject(UStaticMesh::StaticClass(), NULL, TEXT("/Game/SICKA_mansion/StaticMeshes/SM_WingedLion.SM_WingedLion"))));
	LibraryRoom_Mesh.Add(Cast<UStaticMesh>(StaticLoadObject(UStaticMesh::StaticClass(), NULL, TEXT("/Game/SICKA_mansion/StaticMeshes/SM_StandBox.SM_StandBox"))));
	LibraryRoom_Mesh.Add(Cast<UStaticMesh>(StaticLoadObject(UStaticMesh::StaticClass(), NULL, TEXT("/Game/SICKA_mansion/StaticMeshes/SM_Bottle4.SM_Bottle4"))));
	LibraryRoom_Mesh.Add(Cast<UStaticMesh>(StaticLoadObject(UStaticMesh::StaticClass(), NULL, TEXT("/Game/SICKA_mansion/StaticMeshes/SM_BreadCreamSliced.SM_BreadCreamSliced"))));
	LibraryRoom_Mesh.Add(Cast<UStaticMesh>(StaticLoadObject(UStaticMesh::StaticClass(), NULL, TEXT("/Game/SICKA_mansion/StaticMeshes/SM_BookPile7.SM_BookPile7"))));
	LibraryRoom_Mesh.Add(Cast<UStaticMesh>(StaticLoadObject(UStaticMesh::StaticClass(), NULL, TEXT("/Game/SICKA_mansion/StaticMeshes/SM_Candlestickfourside.SM_Candlestickfourside"))));
	LibraryRoom_Mesh.Add(Cast<UStaticMesh>(StaticLoadObject(UStaticMesh::StaticClass(), NULL, TEXT("/Game/SICKA_mansion/StaticMeshes/SM_Plate.SM_Plate"))));
	LibraryRoom_Mesh.Add(Cast<UStaticMesh>(StaticLoadObject(UStaticMesh::StaticClass(), NULL, TEXT("/Game/SICKA_mansion/StaticMeshes/SM_WoodMannequin.SM_WoodMannequin"))));
	LibraryRoom_Mesh.Add(Cast<UStaticMesh>(StaticLoadObject(UStaticMesh::StaticClass(), NULL, TEXT("/Game/SICKA_mansion/StaticMeshes/SM_TravelCase_Basic.SM_TravelCase_Basic"))));
	LibraryRoom_Mesh.Add(Cast<UStaticMesh>(StaticLoadObject(UStaticMesh::StaticClass(), NULL, TEXT("/Game/SICKA_mansion/StaticMeshes/SM_PaintingMedium.SM_PaintingMedium"))));
	LibraryRoom_Mesh.Add(Cast<UStaticMesh>(StaticLoadObject(UStaticMesh::StaticClass(), NULL, TEXT("/Game/SICKA_mansion/StaticMeshes/SM_TillFrame_Pack1.SM_TillFrame_Pack1"))));
	LibraryRoom_Mesh.Add(Cast<UStaticMesh>(StaticLoadObject(UStaticMesh::StaticClass(), NULL, TEXT("/Game/SICKA_mansion/StaticMeshes/SM_SteampunkGear3.SM_SteampunkGear3"))));
	LibraryRoom_Mesh.Add(Cast<UStaticMesh>(StaticLoadObject(UStaticMesh::StaticClass(), NULL, TEXT("/Game/SICKA_mansion/StaticMeshes/SM_SteampunkGear2.SM_SteampunkGear2"))));
	LibraryRoom_Mesh.Add(Cast<UStaticMesh>(StaticLoadObject(UStaticMesh::StaticClass(), NULL, TEXT("/Game/SICKA_mansion/StaticMeshes/SM_RoundBread.SM_RoundBread"))));
	LibraryRoom_Mesh.Add(Cast<UStaticMesh>(StaticLoadObject(UStaticMesh::StaticClass(), NULL, TEXT("/Game/SICKA_mansion/StaticMeshes/SM_Globe.SM_Globe"))));
	LibraryRoom_Mesh.Add(Cast<UStaticMesh>(StaticLoadObject(UStaticMesh::StaticClass(), NULL, TEXT("/Game/SICKA_mansion/StaticMeshes/SM_KnightArmorPoseCloth.SM_KnightArmorPoseCloth"))));
	LibraryRoom_Mesh.Add(Cast<UStaticMesh>(StaticLoadObject(UStaticMesh::StaticClass(), NULL, TEXT("/Game/SICKA_mansion/StaticMeshes/SM_FireToolsStickHolder.SM_FireToolsStickHolder"))));
	LibraryRoom_Mesh.Add(Cast<UStaticMesh>(StaticLoadObject(UStaticMesh::StaticClass(), NULL, TEXT("/Game/SICKA_mansion/StaticMeshes/SM_CurtainFlower_Gurad.SM_CurtainFlower_Gurad"))));
	LibraryRoom_Mesh.Add(Cast<UStaticMesh>(StaticLoadObject(UStaticMesh::StaticClass(), NULL, TEXT("/Game/SICKA_mansion/StaticMeshes/SM_CarpaneseChairMaster.SM_CarpaneseChairMaster"))));
	LibraryRoom_Mesh.Add(Cast<UStaticMesh>(StaticLoadObject(UStaticMesh::StaticClass(), NULL, TEXT("/Game/SICKA_mansion/StaticMeshes/SM_Bottle1.SM_Bottle1"))));
	// Num_LibraryRoom_Mesh = 26

	InGame_LibraryRoom_Mesh[0] = FMath::RandRange(0, Num_LibraryRoom_Mesh - 1);
	InGame_LibraryRoom_Mesh[MyKey] = InGame_LibraryRoom_Mesh[0];
	int CurIndex;
	for (int32 i = 1; i < 7; i++)
	{
		if (i == MyKey)
			continue;

		do {
			CurIndex = FMath::RandRange(0, Num_LibraryRoom_Mesh - 1);
		} while (InGame_LibraryRoom_Mesh.Contains(CurIndex));

		InGame_LibraryRoom_Mesh[i] = CurIndex;
	}

}


void ACapstoneSubObject::SmallObject(void)
{
	// init array
	InGame_Small_Mesh.Init(0, 7);

	// Human Form 일때 나왔으면 하는 메쉬들 리스트.
	// Small_Mesh.Add(Cast<UStaticMesh>(StaticLoadObject(UStaticMesh::StaticClass(), NULL, TEXT("매쉬 주소")))); 
	// 형식으로 붙여넣고, Num_Small_Mesh를 증가시킬 것(필수)
	Small_Mesh.Add(Cast<UStaticMesh>(StaticLoadObject(UStaticMesh::StaticClass(), NULL, TEXT("/Game/SICKA_mansion/StaticMeshes/SM_PlateBig.SM_PlateBig"))));
	Small_Mesh.Add(Cast<UStaticMesh>(StaticLoadObject(UStaticMesh::StaticClass(), NULL, TEXT("/Game/SICKA_mansion/StaticMeshes/SM_PlateBig.SM_PlateBig"))));
	Small_Mesh.Add(Cast<UStaticMesh>(StaticLoadObject(UStaticMesh::StaticClass(), NULL, TEXT("/Game/SICKA_mansion/StaticMeshes/SM_Bottle1.SM_Bottle1"))));
	Small_Mesh.Add(Cast<UStaticMesh>(StaticLoadObject(UStaticMesh::StaticClass(), NULL, TEXT("/Game/SICKA_mansion/StaticMeshes/SM_Bottle15.SM_Bottle15"))));
	Small_Mesh.Add(Cast<UStaticMesh>(StaticLoadObject(UStaticMesh::StaticClass(), NULL, TEXT("/Game/SICKA_mansion/StaticMeshes/SM_Bottle14.SM_Bottle14"))));
	Small_Mesh.Add(Cast<UStaticMesh>(StaticLoadObject(UStaticMesh::StaticClass(), NULL, TEXT("/Game/SICKA_mansion/StaticMeshes/SM_BookPile.SM_BookPile"))));
	Small_Mesh.Add(Cast<UStaticMesh>(StaticLoadObject(UStaticMesh::StaticClass(), NULL, TEXT("/Game/Modular_MedievalTown_WI/Meshes/Props/SM_Apple_1.SM_Apple_1"))));
	Small_Mesh.Add(Cast<UStaticMesh>(StaticLoadObject(UStaticMesh::StaticClass(), NULL, TEXT("/Game/Modular_MedievalTown_WI/Meshes/Props/SM_Candle_Short.SM_Candle_Short"))));
	Small_Mesh.Add(Cast<UStaticMesh>(StaticLoadObject(UStaticMesh::StaticClass(), NULL, TEXT("/Game/Modular_MedievalTown_WI/Meshes/Props/SM_Knife.SM_Knife"))));
	Small_Mesh.Add(Cast<UStaticMesh>(StaticLoadObject(UStaticMesh::StaticClass(), NULL, TEXT("/Game/Modular_MedievalTown_WI/Meshes/Props/SM_Vase_1.SM_Vase_1"))));
	Small_Mesh.Add(Cast<UStaticMesh>(StaticLoadObject(UStaticMesh::StaticClass(), NULL, TEXT("/Game/Modular_MedievalTown_WI/Meshes/Props/SM_Vase_4.SM_Vase_4"))));
	Small_Mesh.Add(Cast<UStaticMesh>(StaticLoadObject(UStaticMesh::StaticClass(), NULL, TEXT("/Game/Victorian_House/Meshes/DecorativeElements/Mesh_Newspapers.Mesh_Newspapers"))));
	Small_Mesh.Add(Cast<UStaticMesh>(StaticLoadObject(UStaticMesh::StaticClass(), NULL, TEXT("/Game/Victorian_House/Meshes/DecorativeElements/Mesh_Newspapers.Mesh_Newspapers"))));
	// Num_Small_Mesh = 13

	InGame_Small_Mesh[0] = FMath::RandRange(0, Num_Small_Mesh - 1);
	InGame_Small_Mesh[MyKey] = InGame_Small_Mesh[0];
	int CurIndex;
	for (int32 i = 1; i < 7; i++)
	{
		if (i == MyKey)
			continue;

		do {
			CurIndex = FMath::RandRange(0, Num_Small_Mesh - 1);
		} while (InGame_Small_Mesh.Contains(CurIndex));

		InGame_Small_Mesh[i] = CurIndex;
	}
}


void ACapstoneSubObject::BigObject(void)
{
	// init array
	InGame_Big_Mesh.Init(0, 7);

	// Human Form 일때 나왔으면 하는 메쉬들 리스트.
	// Big_Mesh.Add(Cast<UStaticMesh>(StaticLoadObject(UStaticMesh::StaticClass(), NULL, TEXT("매쉬 주소")))); 
	// 형식으로 붙여넣고, Num_Big_Mesh를 증가시킬 것(필수)
	Big_Mesh.Add(Cast<UStaticMesh>(StaticLoadObject(UStaticMesh::StaticClass(), NULL, TEXT("/Game/Modular_MedievalTown_WI/Meshes/Buildings/SM_ChimneyTop.SM_ChimneyTop"))));
	Big_Mesh.Add(Cast<UStaticMesh>(StaticLoadObject(UStaticMesh::StaticClass(), NULL, TEXT("/Game/SICKA_mansion/StaticMeshes/SM_FoodStandGround_3S.SM_FoodStandGround_3S"))));
	Big_Mesh.Add(Cast<UStaticMesh>(StaticLoadObject(UStaticMesh::StaticClass(), NULL, TEXT("/Game/SICKA_mansion/StaticMeshes/SM_KnightArmorPoseCloth.SM_KnightArmorPoseCloth"))));
	Big_Mesh.Add(Cast<UStaticMesh>(StaticLoadObject(UStaticMesh::StaticClass(), NULL, TEXT("/Game/SICKA_mansion/StaticMeshes/SM_PolandianChair.SM_PolandianChair"))));
	Big_Mesh.Add(Cast<UStaticMesh>(StaticLoadObject(UStaticMesh::StaticClass(), NULL, TEXT("/Game/SICKA_mansion/StaticMeshes/SM_StandBox.SM_StandBox"))));
	Big_Mesh.Add(Cast<UStaticMesh>(StaticLoadObject(UStaticMesh::StaticClass(), NULL, TEXT("/Game/SICKA_mansion/StaticMeshes/SM_WoodenStudyTable.SM_WoodenStudyTable"))));
	Big_Mesh.Add(Cast<UStaticMesh>(StaticLoadObject(UStaticMesh::StaticClass(), NULL, TEXT("/Game/SICKA_mansion/StaticMeshes/SM_WindowNoFrame.SM_WindowNoFrame"))));
	Big_Mesh.Add(Cast<UStaticMesh>(StaticLoadObject(UStaticMesh::StaticClass(), NULL, TEXT("/Game/SICKA_mansion/StaticMeshes/SM_WaiterStand.SM_WaiterStand"))));
	Big_Mesh.Add(Cast<UStaticMesh>(StaticLoadObject(UStaticMesh::StaticClass(), NULL, TEXT("/Game/SICKA_mansion/StaticMeshes/SM_SackSet_TripleStack.SM_SackSet_TripleStack"))));
	Big_Mesh.Add(Cast<UStaticMesh>(StaticLoadObject(UStaticMesh::StaticClass(), NULL, TEXT("/Game/SICKA_mansion/StaticMeshes/SM_PaintingMedium.SM_PaintingMedium"))));
	Big_Mesh.Add(Cast<UStaticMesh>(StaticLoadObject(UStaticMesh::StaticClass(), NULL, TEXT("/Game/SICKA_mansion/StaticMeshes/SM_Gramophone.SM_Gramophone"))));
	Big_Mesh.Add(Cast<UStaticMesh>(StaticLoadObject(UStaticMesh::StaticClass(), NULL, TEXT("/Game/SICKA_mansion/StaticMeshes/SM_FoodStand.SM_FoodStand"))));
	Big_Mesh.Add(Cast<UStaticMesh>(StaticLoadObject(UStaticMesh::StaticClass(), NULL, TEXT("/Game/SICKA_mansion/StaticMeshes/SM_FoodStandGround_1S.SM_FoodStandGround_1S"))));
	Big_Mesh.Add(Cast<UStaticMesh>(StaticLoadObject(UStaticMesh::StaticClass(), NULL, TEXT("/Game/SICKA_mansion/StaticMeshes/SM_CellarBarrel.SM_CellarBarrel"))));
	// Num_Big_Mesh = 14

	InGame_Big_Mesh[0] = FMath::RandRange(0, Num_Big_Mesh - 1);
	InGame_Big_Mesh[MyKey] = InGame_Big_Mesh[0];
	int CurIndex;
	for (int32 i = 1; i < 7; i++)
	{
		if (i == MyKey)
			continue;

		do {
			CurIndex = FMath::RandRange(0, Num_Big_Mesh - 1);
		} while (InGame_Big_Mesh.Contains(CurIndex));

		InGame_Big_Mesh[i] = CurIndex;
	}
}


