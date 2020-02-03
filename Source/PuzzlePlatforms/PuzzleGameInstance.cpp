// Fill out your copyright notice in the Description page of Project Settings.


#include "PuzzleGameInstance.h"
#include "Engine/Engine.h"
#include "GameFramework/PlayerController.h"
#include "UObject/ConstructorHelpers.h"
#include "PlatformTrigger.h"
#include "MenuSystem/MainMenu.h"
#include "Blueprint/UserWidget.h"

UPuzzleGameInstance::UPuzzleGameInstance()
{

    // static ConstructorHelpers::FClassFinder<APlatformTrigger> PlatformTriggerBPClass(TEXT("/Game/Blueprint/BP_PlatformTrigger"));
    // if (!ensure(PlatformTriggerBPClass.Class != nullptr)) return;
    // UE_LOG(LogTemp, Warning, TEXT("Found class %s"), *PlatformTriggerBPClass.Class->GetName());

    static ConstructorHelpers::FClassFinder<UUserWidget> MenuBPClass(TEXT("/Game/MenuSystem/WBP_Menu"));
    if (!ensure(MenuBPClass.Class != nullptr)) return;
    MenuClass = MenuBPClass.Class;
    // UE_LOG(LogTemp, Warning, TEXT("Found Widget class %s"), *MenuClass->GetName());
}

void UPuzzleGameInstance::Init()
{
    Super::Init();
    // UE_LOG(LogTemp, Warning, TEXT("logging from game instance init"));
}

// Called by Level BluePrint on MainMenu level
void UPuzzleGameInstance::LoadMenu()
{
    if (!ensure(MenuClass != nullptr)) return;
    UMainMenu* Menu = CreateWidget<UMainMenu>(this, MenuClass);
    if (!ensure(Menu != nullptr)) return;
    Menu->AddToViewport();
    Menu->bIsFocusable = true;
    APlayerController* PlayerController = GetFirstLocalPlayerController();
    if (!ensure(PlayerController != nullptr)) return;
    Menu->SetUserFocus(PlayerController);
    PlayerController->SetInputMode(FInputModeUIOnly());
    PlayerController->bShowMouseCursor = true;

    Menu->SetMenuInterface(this);
}

void UPuzzleGameInstance::Host()
{
    UE_LOG(LogTemp, Warning, TEXT("logging from host function"));
    UEngine* Engine = GetEngine();
    Engine->AddOnScreenDebugMessage(-1, 5.f, FColor::Yellow, TEXT("Le message on le screen"));

    APlayerController* PlayerController = GetFirstLocalPlayerController();
    if (!ensure(PlayerController != nullptr)) return;
    PlayerController->SetInputMode(FInputModeGameOnly());

    UWorld* World = GetWorld();
    if (!ensure(World != nullptr)) return;
    World->ServerTravel("/Game/ThirdPersonCPP/Maps/ThirdPersonExampleMap?listen");
}

void UPuzzleGameInstance::Join()
{
    Join("192.168.15.11");
}
void UPuzzleGameInstance::Join(const FString& Address)
{
    UE_LOG(LogTemp, Warning, TEXT("logging from host function"));
    UEngine* Engine = GetEngine();
    Engine->AddOnScreenDebugMessage(-1, 5.f, FColor::Yellow, FString::Printf(TEXT("Joining: %s"), *Address));

    APlayerController* PlayerController = GetFirstLocalPlayerController();
    if (!ensure(PlayerController != nullptr)) return;
    PlayerController->SetInputMode(FInputModeGameOnly());

    PlayerController->ClientTravel(Address, ETravelType::TRAVEL_Absolute);
}