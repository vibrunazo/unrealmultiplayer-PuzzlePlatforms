// Fill out your copyright notice in the Description page of Project Settings.


#include "PuzzleGameInstance.h"

void UPuzzleGameInstance::Init()
{
    Super::Init();
    UE_LOG(LogTemp, Warning, TEXT("logging from game instance init"));
}