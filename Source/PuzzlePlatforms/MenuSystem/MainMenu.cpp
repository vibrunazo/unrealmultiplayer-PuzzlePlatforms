// Fill out your copyright notice in the Description page of Project Settings.

#include "MainMenu.h"
#include "RowWidget.h"
#include "Components/Button.h"
#include "Components/WidgetSwitcher.h"
#include "Components/EditableTextBox.h"
#include "Engine/World.h"
#include "UObject/ConstructorHelpers.h"
#include "Components/ScrollBox.h"
#include "Components/TextBlock.h"

UMainMenu::UMainMenu(const FObjectInitializer &ObjectInitializer)
{
  static ConstructorHelpers::FClassFinder<UUserWidget> RowBPClass(TEXT("/Game/MenuSystem/WBP_Row"));
  if (!ensure(RowBPClass.Class != nullptr))
    return;
  RowClass = RowBPClass.Class;
}

bool UMainMenu::Initialize()
{
  bool Success = Super::Initialize();
  if (!Success)
    return false;
  if (!ensure(HostButton != nullptr))
    return false;
  HostButton->OnClicked.AddDynamic(this, &UMainMenu::OnHostClick);
  if (!ensure(JoinButton != nullptr))
    return false;
  JoinButton->OnClicked.AddDynamic(this, &UMainMenu::OnJoinClick);
  if (!ensure(JoinConfirmButton != nullptr))
    return false;
  JoinConfirmButton->OnClicked.AddDynamic(this, &UMainMenu::OnJoinConfirmClick);
  if (!ensure(JoinCancelButton != nullptr))
    return false;
  JoinCancelButton->OnClicked.AddDynamic(this, &UMainMenu::OnJoinCancelClick);
  if (!ensure(QuitButton != nullptr))
    return false;
  QuitButton->OnClicked.AddDynamic(this, &UMainMenu::OnQuitClick);

  return true;
}

void UMainMenu::SetServerList(TArray<FString> ServerNames)
{
  if (!ensure(ServerList != nullptr)) return;
  ServerList->ClearChildren();
  uint32 i = 0;
  for (auto &&CurName : ServerNames)
  {
    if (!ensure(RowClass != nullptr))
      return;
    URowWidget *Row = CreateWidget<URowWidget>(this, RowClass);
    Row->ServerName->SetText(FText::FromString(CurName));
    Row->Setup(this, i++);
    ServerList->AddChild(Row);
  }
}

void UMainMenu::SelectIndex(uint32 NewIndex)
{
  SelectedIndex = NewIndex;
  UE_LOG(LogTemp, Warning, TEXT("Selected index is now: %d"), SelectedIndex.GetValue());
}

void UMainMenu::OnHostClick()
{
  UE_LOG(LogTemp, Warning, TEXT("Host Button clicked"));
  if (!ensure(MenuInterface != nullptr))
    return;
  MenuInterface->Host();
}

void UMainMenu::OnJoinClick()
{
  // FText IPText = IPTextbox->GetText();
  // UE_LOG(LogTemp, Warning, TEXT("Join Button clicked with IP: %s"), *IPText.ToString());
  if (!ensure(MenuSwitcher != nullptr))
    return;
  MenuSwitcher->SetActiveWidget(JoinWindow);
  MenuInterface->MenuNeedsSessions();
}

void UMainMenu::OnJoinConfirmClick()
{
  
  // UE_LOG(LogTemp, Warning, TEXT("Row name: %s"), *Row->GetFullName());
  // FText IPText = IPTextbox->GetText();
  // UE_LOG(LogTemp, Warning, TEXT("Join Confirm clicked with IP: %s"), *IPText.ToString());
  if (!ensure(MenuInterface != nullptr)) return;
  // MenuInterface->Join(*IPText.ToString());
  if (SelectedIndex.IsSet())
  {
    UE_LOG(LogTemp, Warning, TEXT("Selected Index: %d"), SelectedIndex.GetValue());
  }
  else
  {
    UE_LOG(LogTemp, Warning, TEXT("Index not set"));
  }
  
  MenuInterface->Join();
}

void UMainMenu::OnJoinCancelClick()
{
  UE_LOG(LogTemp, Warning, TEXT("Join Cancel Button clicked"));
  if (!ensure(MenuSwitcher != nullptr))
    return;
  MenuSwitcher->SetActiveWidget(MenuWindow);
}

void UMainMenu::OnQuitClick()
{
  UWorld *World = GetWorld();
  if (!ensure(World != nullptr))
    return;
  APlayerController *Cont = World->GetFirstPlayerController();
  if (!ensure(Cont != nullptr))
    return;
  Cont->ConsoleCommand("Quit");
}