// Fill out your copyright notice in the Description page of Project Settings.


#include "TOSaveGame.h"

UTOSaveGame::UTOSaveGame()
{
    MapName = FName("Room");
    Progress = 1;
    PlayerLocation = FVector(-780.0f, -700.0f, 163.170105f);
    HP = 100;
    Level = 1;
    InventoryItemCount = { 5, 10, 10 , 10, 10};
}

