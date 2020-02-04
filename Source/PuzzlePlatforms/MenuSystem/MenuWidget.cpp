// Fill out your copyright notice in the Description page of Project Settings.


#include "MenuWidget.h"

void UMenuWidget::Setup()
  {
    this->AddToViewport();
    this->bIsFocusable = true;
    APlayerController* PlayerController = GetWorld()->GetFirstPlayerController();
    if (!ensure(PlayerController != nullptr)) return;
    this->SetUserFocus(PlayerController);
    PlayerController->SetInputMode(FInputModeUIOnly());
    PlayerController->bShowMouseCursor = true;
  }

  void UMenuWidget::Teardown()
  {
    APlayerController* PlayerController = GetWorld()->GetFirstPlayerController();
    if (!ensure(PlayerController != nullptr)) return;
    PlayerController->SetInputMode(FInputModeGameOnly());
    PlayerController->bShowMouseCursor = false;
    this->RemoveFromViewport();
  }

  void UMenuWidget::SetMenuInterface(IMenuInterface* DudeWhoImplemented)
  {
    MenuInterface = DudeWhoImplemented;
  }