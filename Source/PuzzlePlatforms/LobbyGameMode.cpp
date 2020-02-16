// Fill out your copyright notice in the Description page of Project Settings.


#include "LobbyGameMode.h"
#include "Engine/Engine.h"
#include "GameMapsSettings.h"
#include "TimerManager.h"
#include "PuzzleGameInstance.h"

void ALobbyGameMode::PostLogin(APlayerController* NewPlayer)
{
    Super::PostLogin(NewPlayer);
    // UGameMapsSettings* GMSettings = UGameMapsSettings::GetGameMapsSettings();
    // GMSettings->TransitionMap = FSoftObjectPath("/Game/Maps/LoadingMap");

    ++CountPlayers;
    UE_LOG(LogTemp, Warning, TEXT("A NEW CHALLENGER! Total players: %d"), CountPlayers);
    if (CountPlayers >= 2)
    {
        UE_LOG(LogTemp, Warning, TEXT("There are 3 players, starting in 5 secs"), CountPlayers);
        if( (TimerHandle.IsValid() == false ) || ( bTimerExpired) ) 
        {
            GetWorldTimerManager().SetTimer(TimerHandle, this, &ALobbyGameMode::OnTimerEnd, 5.0f);
            bTimerExpired = false;
        }
        // UWorld* World = GetWorld();
        // if (!ensure(World != nullptr)) return;
        // World->ServerTravel("/Game/ThirdPersonCPP/Maps/ThirdPersonExampleMap?listen");
    }
}

void ALobbyGameMode::Logout(AController* Exiting)
{
    Super::Logout(Exiting);
    --CountPlayers;
    UE_LOG(LogTemp, Warning, TEXT("A Player Left! Total players: %d"), CountPlayers);
}

// TODO transition map UI needs to be in game state so I can remove it here
void ALobbyGameMode::OnTimerEnd()
{
    UE_LOG(LogTemp, Warning, TEXT("TIMER END"));
    bTimerExpired = true;
    bUseSeamlessTravel = true;
    UWorld* World = GetWorld();
    if (!ensure(World != nullptr)) return;
    UPuzzleGameInstance* GI = Cast<UPuzzleGameInstance>(World->GetGameInstance());
    if (!ensure(GI != nullptr)) return;
    GI->StartSession();
    World->ServerTravel("/Game/ThirdPersonCPP/Maps/ThirdPersonExampleMap?listen");
}