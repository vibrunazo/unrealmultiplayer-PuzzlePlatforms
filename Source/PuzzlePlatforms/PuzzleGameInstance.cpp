// Fill out your copyright notice in the Description page of Project Settings.


#include "PuzzleGameInstance.h"
#include "Engine/Engine.h"
#include "GameFramework/PlayerController.h"
#include "UObject/ConstructorHelpers.h"
#include "PlatformTrigger.h"
#include "MenuSystem/MainMenu.h"
#include "MenuSystem/MenuWidget.h"
#include "Blueprint/UserWidget.h"
// #include "OnlineSubsystem.h"
// #include "OnlineSessionSettings.h"
// #include "Interfaces/OnlineSessionInterface.h"

const static FName SESSION_NAME = TEXT("My Session Game");

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
    SessionInterface = OSS->GetSessionInterface();
    if (!ensure(SessionInterface.IsValid())) return;
    UE_LOG(LogTemp, Warning, TEXT("Found Session Interface"));
    // SessionInterface->CreateSession(0, TEXT("My Session Game"), SessionSettings);
    SessionInterface->OnCreateSessionCompleteDelegates.AddUObject(this, &UPuzzleGameInstance::OnCreateSessionComplete);
    SessionInterface->OnDestroySessionCompleteDelegates.AddUObject(this, &UPuzzleGameInstance::OnDestroySessionComplete);
    SessionInterface->OnFindSessionsCompleteDelegates.AddUObject(this, &UPuzzleGameInstance::OnFindSessionsComplete);
    SessionInterface->OnJoinSessionCompleteDelegates.AddUObject(this, &UPuzzleGameInstance::OnJoinSessionComplete);
    SessionSearch = MakeShareable(new FOnlineSessionSearch());
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
    if (SessionInterface.IsValid())
    {
        auto ExistingSession = SessionInterface->GetNamedSession(SESSION_NAME);
        if (ExistingSession != nullptr)
        {
            bNeedsNewSession = true;
            SessionInterface->DestroySession(SESSION_NAME);
        }
        else
        {
            CreateSession();
            // FOnlineSessionSettings SessionSettings;
            // SessionInterface->CreateSession(0, SESSION_NAME, SessionSettings);
        }

    }
    // UE_LOG(LogTemp, Warning, TEXT("logging from host function"));
    // UEngine* Engine = GetEngine();
    // Engine->AddOnScreenDebugMessage(-1, 5.f, FColor::Yellow, TEXT("Le message on le screen"));
    // if (Menu)
    // {
    //     Menu->Teardown();
    // }

    // UWorld* World = GetWorld();
    // if (!ensure(World != nullptr)) return;
    // World->ServerTravel("/Game/ThirdPersonCPP/Maps/ThirdPersonExampleMap?listen");
}

// void UPuzzleGameInstance::Join()
// {
//     Join("192.168.15.11");
// }

void UPuzzleGameInstance::Join(uint32 Index)
{
    if (!ensure(Menu != nullptr)) return;
    if (!ensure(SessionInterface.IsValid())) return;
    if (!ensure(SessionSearch.IsValid())) return;
    SessionInterface->JoinSession(0, SESSION_NAME, SessionSearch->SearchResults[Index]);

}

// void UPuzzleGameInstance::Join(const FString& Address)
// {
//     // UE_LOG(LogTemp, Warning, TEXT("logging from host function"));
//     if (!ensure(*Address != nullptr)) return;
//     UEngine* Engine = GetEngine();
//     Engine->AddOnScreenDebugMessage(-1, 5.f, FColor::Yellow, FString::Printf(TEXT("Joining: %s"), *Address));

//     APlayerController* PlayerController = GetFirstLocalPlayerController();
//     if (!ensure(PlayerController != nullptr)) return;
//     Menu->SetServerList({"One Server", "Another Server"});
//     // Menu->Teardown();


//     // PlayerController->ClientTravel(Address, ETravelType::TRAVEL_Absolute);
// }

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

void UPuzzleGameInstance::OnCreateSessionComplete(FName SessionName, bool Success)
{
    if (!Success) return;
    UE_LOG(LogTemp, Warning, TEXT("Session Created: %s"), *SessionName.ToString());
    if (Menu)
    {
        Menu->Teardown();
    }

    UWorld* World = GetWorld();
    if (!ensure(World != nullptr)) return;
    World->ServerTravel("/Game/ThirdPersonCPP/Maps/ThirdPersonExampleMap?listen");
}

void UPuzzleGameInstance::OnDestroySessionComplete(FName SessionName, bool bWasSuccessful)
{
    if (!bWasSuccessful || !SessionInterface.IsValid() || !bNeedsNewSession) return;
    CreateSession();
    bNeedsNewSession = false;
}

void UPuzzleGameInstance::CreateSession()
{
    if (!ensure(SessionInterface.IsValid())) return;
    FOnlineSessionSettings SessionSettings;
    if (IOnlineSubsystem::Get()->GetSubsystemName() == "NULL") SessionSettings.bIsLANMatch = true;
    else SessionSettings.bIsLANMatch = false;
    SessionSettings.NumPublicConnections = 4;
    SessionSettings.bShouldAdvertise = true;
    SessionSettings.bUsesPresence = true;
    SessionInterface->CreateSession(0, SESSION_NAME, SessionSettings);
}

void UPuzzleGameInstance::OnFindSessionsComplete(bool bSuccess)
{
    UE_LOG(LogTemp, Warning, TEXT("Find Sessions Complete"));
    if (!ensure(SessionInterface.IsValid() && bSuccess && Menu != nullptr)) return;
    TArray<FOnlineSessionSearchResult> Results = SessionSearch->SearchResults;
    UE_LOG(LogTemp, Warning, TEXT("Total of %d sessions"), Results.Num());
    TArray<FServerData> ServerData;
    for (auto &&Result : Results)
    {
        FString SessId = Result.GetSessionIdStr();
        int32 SessPing = Result.PingInMs;
        UE_LOG(LogTemp, Warning, TEXT("Session: %s, ping: %d"), *SessId, SessPing);
        FServerData Data;
        Data.Name = SessId;
        Data.HostUsername = Result.Session.OwningUserName;
        Data.Ping = SessPing;
        Data.MaxPlayers = Result.Session.SessionSettings.NumPublicConnections;
        Data.CurrentPlayers = Data.MaxPlayers - Result.Session.NumOpenPublicConnections;
        ServerData.Add(Data);
    }
    Menu->SetServerList(ServerData);
}

void UPuzzleGameInstance::MenuNeedsSessions()
{
    if (!SessionSearch.IsValid()) return;
    // SessionSearch->bIsLanQuery = true;
    SessionSearch->MaxSearchResults = 200;
    SessionSearch->QuerySettings.Set(SEARCH_PRESENCE, true, EOnlineComparisonOp::Equals);
    SessionInterface->FindSessions(0, SessionSearch.ToSharedRef());
    UE_LOG(LogTemp, Warning, TEXT("Started looking for 200 sessions"));
    // Log LogOnline VeryVerbose
}

void UPuzzleGameInstance::OnJoinSessionComplete(FName SessionName, EOnJoinSessionCompleteResult::Type Result)
{
    FString ConnectInfo;

    if (!SessionInterface->GetResolvedConnectString(SessionName, ConnectInfo))
    {
        UE_LOG(LogTemp, Warning, TEXT("Could not get connect string"));
        return;
    }
    APlayerController* PlayerController = GetFirstLocalPlayerController();
    if (!ensure(PlayerController != nullptr)) return;
    if (!ensure(Menu != nullptr)) return;
    Menu->Teardown();

    UE_LOG(LogTemp, Warning, TEXT("OnJoinSessionCompleted! Info: %s"), *ConnectInfo);
    PlayerController->ClientTravel(ConnectInfo, ETravelType::TRAVEL_Absolute);
}