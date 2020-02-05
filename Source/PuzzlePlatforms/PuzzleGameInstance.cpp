// Fill out your copyright notice in the Description page of Project Settings.


#include "PuzzleGameInstance.h"
#include "Engine/Engine.h"
#include "GameFramework/PlayerController.h"
#include "UObject/ConstructorHelpers.h"
#include "PlatformTrigger.h"
#include "MenuSystem/MainMenu.h"
#include "MenuSystem/MenuWidget.h"
#include "Blueprint/UserWidget.h"
#include "OnlineSubsystem.h"

UPuzzleGameInstance::UPuzzleGameInstance()
{

    // static ConstructorHelpers::FClassFinder<APlatformTrigger> PlatformTriggerBPClass(TEXT("/Game/Blueprint/BP_PlatformTrigger"));
    // if (!ensure(PlatformTriggerBPClass.Class != nullptr)) return;
    // UE_LOG(LogTemp, Warning, TEXT("Found class %s"), *PlatformTriggerBPClass.Class->GetName());

    static ConstructorHelpers::FClassFinder<UUserWidget> MenuBPClass(TEXT("/Game/MenuSystem/WBP_Menu"));
    if (!ensure(MenuBPClass.Class != nullptr)) return;
    MenuClass = MenuBPClass.Class;
    static ConstructorHelpers::FClassFinder<UUserWidget> IGMenuBPClass(TEXT("/Game/MenuSystem/WBP_IngameMenu"));
    if (!ensure(IGMenuBPClass.Class != nullptr)) return;
    InGameMenuClass = IGMenuBPClass.Class;
    // UE_LOG(LogTemp, Warning, TEXT("Found Widget class %s"), *InGameMenuClass->GetName());
}

void UPuzzleGameInstance::Init()
{
    Super::Init();
    // UE_LOG(LogTemp, Warning, TEXT("logging from game instance init"));
    IOnlineSubsystem* OSS = IOnlineSubsystem::Get();
    if (!ensure(OSS != nullptr)) return;
    UE_LOG(LogTemp, Warning, TEXT("OSS: %s Platform: %s"), *OSS->GetInstanceName().ToString(), *OSS->GetOnlineServiceName().ToString());
    IOnlineSessionPtr SessionInterface = OSS->GetSessionInterface();
    if (!ensure(SessionInterface != nullptr)) return;
    UE_LOG(LogTemp, Warning, TEXT("Found Session Interface"));
}

// Called by Level BluePrint on MainMenu level
void UPuzzleGameInstance::LoadMenu()
{
    if (!ensure(MenuClass != nullptr)) return;
    Menu = CreateWidget<UMainMenu>(this, MenuClass);
    if (!ensure(Menu != nullptr)) return;
    Menu->Setup();

    Menu->SetMenuInterface(this);
}

// Called by PuzzleController when player inputs Menu action
void UPuzzleGameInstance::LoadInGameMenu()
{
    if (!ensure(InGameMenuClass != nullptr)) return;
    InGameMenu = CreateWidget<UMenuWidget>(this, InGameMenuClass);
    if (!ensure(InGameMenu != nullptr)) return;
    InGameMenu->Setup();

    InGameMenu->SetMenuInterface(this);
}

void UPuzzleGameInstance::Host()
{
    // UE_LOG(LogTemp, Warning, TEXT("logging from host function"));
    // UEngine* Engine = GetEngine();
    // Engine->AddOnScreenDebugMessage(-1, 5.f, FColor::Yellow, TEXT("Le message on le screen"));
    if (Menu)
    {
        Menu->Teardown();
    }

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
    // UE_LOG(LogTemp, Warning, TEXT("logging from host function"));
    if (!ensure(*Address != nullptr)) return;
    UEngine* Engine = GetEngine();
    Engine->AddOnScreenDebugMessage(-1, 5.f, FColor::Yellow, FString::Printf(TEXT("Joining: %s"), *Address));

    APlayerController* PlayerController = GetFirstLocalPlayerController();
    if (!ensure(PlayerController != nullptr)) return;
    Menu->Teardown();

    PlayerController->ClientTravel(Address, ETravelType::TRAVEL_Absolute);
}

void UPuzzleGameInstance::GoToMainMenu()
{
    // UWorld* World = GetWorld();
    // if (!ensure(World != nullptr)) return;
    // World->ServerTravel("/Game/MenuSystem/MainMenu");
    APlayerController* PlayerController = GetFirstLocalPlayerController();
    if (!ensure(PlayerController != nullptr)) return;
    if (InGameMenu) InGameMenu->Teardown();

    PlayerController->ClientTravel("/Game/MenuSystem/MainMenu", ETravelType::TRAVEL_Absolute);
}