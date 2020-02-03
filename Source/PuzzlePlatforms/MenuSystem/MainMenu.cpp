// Fill out your copyright notice in the Description page of Project Settings.


#include "MainMenu.h"
#include "Components/Button.h"

  bool UMainMenu::Initialize()
  {
    bool Success = Super::Initialize();
    if (!Success) return false;
    if (!ensure(HostButton != nullptr)) return false;
    HostButton->OnClicked.AddDynamic(this, &UMainMenu::OnHostClick);
    if (!ensure(JoinButton != nullptr)) return false;
    JoinButton->OnClicked.AddDynamic(this, &UMainMenu::OnJoinClick);

    return true;
  }

  void UMainMenu::OnHostClick()
  {
      UE_LOG(LogTemp, Warning, TEXT("Host Button clicked"));
      if (!ensure(MenuInterface != nullptr)) return;
      MenuInterface->Host();
  }

  void UMainMenu::OnJoinClick()
  {
      UE_LOG(LogTemp, Warning, TEXT("Join Button clicked"));
      if (!ensure(MenuInterface != nullptr)) return;
      MenuInterface->Join();
  }

  void UMainMenu::SetMenuInterface(IMenuInterface* DudeWhoImplemented)
  {
    MenuInterface = DudeWhoImplemented;
  }