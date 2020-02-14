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
  // WidgetBlueprint'/Game/MenuSystem/WBP_Menu.WBP_Menu'
  // WidgetBlueprint'/Game/MenuSystem/WBP_Row.WBP_Row'
  // static ConstructorHelpers::FClassFinder<UUserWidget> RowBPClass(TEXT("/Game/MenuSystem/WBP_Row.WBP_Row"));
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
  if (!ensure(JoinCancelButton != nullptr))
    return false;
  HostCancelButton->OnClicked.AddDynamic(this, &UMainMenu::OnHostCancelClick);
  if (!ensure(JoinCancelButton != nullptr))
    return false;
  HostConfirmButton->OnClicked.AddDynamic(this, &UMainMenu::OnHostConfirmClick);
  if (!ensure(QuitButton != nullptr))
    return false;
  QuitButton->OnClicked.AddDynamic(this, &UMainMenu::OnQuitClick);

  return true;
}

void UMainMenu::SetServerList(TArray<FServerData> Servers)
{
  if (!ensure(ServerList != nullptr)) return;
  ServerList->ClearChildren();
  int32 i = 0;
  // ServerNames.Add("test1");
  // ServerNames.Add("test2");
  // ServerNames.Add("test3");
  for (auto &&Server : Servers)
  {
    if (!ensure(RowClass != nullptr))
      return;
    URowWidget *Row = CreateWidget<URowWidget>(this, RowClass);
    FString NameString = FString::Printf(TEXT("%s (%s)"), *Server.Name.Left(12), *Server.HostUsername.Left(12));
    FText NameText = FText::FromString(NameString);
    Row->ServerName->SetText(NameText);
    FString InfoString = FString::Printf(TEXT("%dms %d/%d"), Server.Ping, Server.CurrentPlayers, Server.MaxPlayers);
    FText InfoText = FText::FromString(InfoString);
    Row->PlayersText->SetText(InfoText);
    Row->Setup(this, i++);
    ServerList->AddChild(Row);
    // RowList.Add(Row);
  }
}

void UMainMenu::SelectIndex(int32 NewIndex)
{
  SelectedIndex = NewIndex;
  UE_LOG(LogTemp, Warning, TEXT("Selected index is now: %d"), SelectedIndex.GetValue());
  UpdateChildren();
}

void UMainMenu::UpdateChildren()
{
  TArray<UWidget *> RowList = ServerList->GetAllChildren();
  // Deselect all who are not current index
  for (auto &&Child : RowList)
  {
    URowWidget* Row = Cast<URowWidget>(Child);
    if (!ensure(Row != nullptr )) return;
    if (SelectedIndex != Row->MyIndex)
    {
      Row->bIsSelected = false;
      Row->DeSelect();
    }
  }
}

void UMainMenu::OnHostClick()
{
  UE_LOG(LogTemp, Warning, TEXT("Host Button clicked"));
  if (!ensure(MenuSwitcher != nullptr)) return;
  MenuSwitcher->SetActiveWidget(HostWindow);
  // if (!ensure(MenuInterface != nullptr))
  //   return;
  // MenuInterface->Host();
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
    MenuInterface->Join(SelectedIndex.GetValue());
  }
  else
  {
    UE_LOG(LogTemp, Warning, TEXT("Index not set"));
  }
  
  
}

void UMainMenu::OnJoinCancelClick()
{
  UE_LOG(LogTemp, Warning, TEXT("Join Cancel Button clicked"));
  if (!ensure(MenuSwitcher != nullptr))
    return;
  MenuSwitcher->SetActiveWidget(MenuWindow);
}

void UMainMenu::OnHostCancelClick()
{
  UE_LOG(LogTemp, Warning, TEXT("Host Cancel Button clicked"));
  if (!ensure(MenuSwitcher != nullptr))
    return;
  MenuSwitcher->SetActiveWidget(MenuWindow);
}

void UMainMenu::OnHostConfirmClick()
{
  UE_LOG(LogTemp, Warning, TEXT("Host Confirm Button clicked"));
  if (!ensure(HostTextBox != nullptr)) return;
  FText NameText = HostTextBox->GetText();
  if (!ensure(MenuInterface != nullptr))
    return;
  MenuInterface->Host(NameText.ToString());
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