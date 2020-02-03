// Fill out your copyright notice in the Description page of Project Settings.


#include "MainMenu.h"
// #include "Blueprint/UserWidget.h"

// UMainMenu::UMainMenu(const FObjectInitializer& ObjectInitializer)
// {
//     UE_LOG(LogTemp, Warning, TEXT("Hello from main menu"));
// }

  void UMainMenu::NativeConstruct()
  {
    Super::NativeConstruct();
    UE_LOG(LogTemp, Warning, TEXT("Hello from main menu"));
  }