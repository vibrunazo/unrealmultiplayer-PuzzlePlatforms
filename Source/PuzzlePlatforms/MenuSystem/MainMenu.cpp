// Fill out your copyright notice in the Description page of Project Settings.


#include "MainMenu.h"
#include "Components/Button.h"

  void UMainMenu::NativeConstruct()
  {
    Super::NativeConstruct();
  }

  bool UMainMenu::Initialize()
  {
    bool Success = Super::Initialize();
    if (!Success) return false;
    if (!ensure(HostButton != nullptr)) return false;
    HostButton->OnClicked.AddDynamic(this, &UMainMenu::OnHostClick);

    return true;
  }

  void UMainMenu::OnHostClick()
  {
      UE_LOG(LogTemp, Warning, TEXT("Host Button clicked"));
  }