// Fill out your copyright notice in the Description page of Project Settings.


#include "LobbyGameMode.h"
#include "Engine/Engine.h"
#include "GameMapsSettings.h"

void ALobbyGameMode::PostLogin(APlayerController* NewPlayer)
{
    Super::PostLogin(NewPlayer);
    bUseSeamlessTravel = true;
    // UGameMapsSettings* GMSettings = UGameMapsSettings::GetGameMapsSettings();
    // GMSettings->TransitionMap = FSoftObjectPath("/Game/Maps/LoadingMap");

    ++CountPlayers;
    UE_LOG(LogTemp, Warning, TEXT("A NEW CHALLENGER! Total players: %d"), CountPlayers);
    if (CountPlayers >= 2)
    {
        UE_LOG(LogTemp, Warning, TEXT("There are 3 players"), CountPlayers);
        UWorld* World = GetWorld();
        if (!ensure(World != nullptr)) return;
        World->ServerTravel("/Game/ThirdPersonCPP/Maps/ThirdPersonExampleMap?listen");
    }
}

void ALobbyGameMode::Logout(AController* Exiting)
{
    Super::Logout(Exiting);
    --CountPlayers;
    UE_LOG(LogTemp, Warning, TEXT("A Player Left! Total players: %d"), CountPlayers);
}