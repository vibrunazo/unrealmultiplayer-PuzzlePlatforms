// Fill out your copyright notice in the Description page of Project Settings.


#include "PuzzleController.h"
#include "PuzzleGameInstance.h"

void APuzzleController::BeginPlay()
{
    Super::BeginPlay();
    // UE_LOG(LogTemp, Warning, TEXT("Hello from controller begin"));

    // check(PlayerInput);
	// PlayerInput->BindAction("Jump", IE_Pressed, this, &ACharacter::Jump);
}

void APuzzleController::SetupInputComponent()
 {
     Super::SetupInputComponent();
 
     InputComponent->BindAction("Menu", IE_Pressed, this, &APuzzleController::InputMenu);
 }

 void APuzzleController::InputMenu()
 {
     UE_LOG(LogTemp, Warning, TEXT("Input Menu"));
     UPuzzleGameInstance* GameInstance = Cast<UPuzzleGameInstance>(GetGameInstance());
     GameInstance->LoadInGameMenu();
 }