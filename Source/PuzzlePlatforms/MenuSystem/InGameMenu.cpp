// Fill out your copyright notice in the Description page of Project Settings.


#include "InGameMenu.h"
#include "Components/Button.h"

bool UInGameMenu::Initialize()
{
    bool Success = Super::Initialize();
    if (!Success) return false;
    if (!ensure(CancelButton != nullptr)) return false;
    CancelButton->OnClicked.AddDynamic(this, &UInGameMenu::OnCancelClick);
    if (!ensure(QuitButton != nullptr)) return false;
    QuitButton->OnClicked.AddDynamic(this, &UInGameMenu::OnQuitClick);

    return true;
}

void UInGameMenu::OnCancelClick()
{
    UE_LOG(LogTemp, Warning, TEXT("Cancel Button clicked"));
    this->Teardown();
}

void UInGameMenu::OnQuitClick()
{
    UE_LOG(LogTemp, Warning, TEXT("Quit Button clicked"));
    if (!ensure(MenuInterface != nullptr)) return;
    MenuInterface->GoToMainMenu();
}
