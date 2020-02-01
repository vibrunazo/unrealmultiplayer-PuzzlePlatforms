// Fill out your copyright notice in the Description page of Project Settings.


#include "PuzzleGameInstance.h"
#include "Engine/Engine.h"

void UPuzzleGameInstance::Init()
{
    Super::Init();
    UE_LOG(LogTemp, Warning, TEXT("logging from game instance init"));
}

void UPuzzleGameInstance::Host()
{
    UE_LOG(LogTemp, Warning, TEXT("logging from host function"));
    UEngine* Engine = GetEngine();
    Engine->AddOnScreenDebugMessage(-1, 5.f, FColor::Yellow, TEXT("Le message on le screen"));
}

void UPuzzleGameInstance::Join(const FString& Address)
{
    UE_LOG(LogTemp, Warning, TEXT("logging from host function"));
    UEngine* Engine = GetEngine();
    Engine->AddOnScreenDebugMessage(-1, 5.f, FColor::Yellow, FString::Printf(TEXT("Joining: %s"), *Address));
}