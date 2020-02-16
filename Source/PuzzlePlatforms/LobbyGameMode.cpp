// Fill out your copyright notice in the Description page of Project Settings.


#include "LobbyGameMode.h"

void ALobbyGameMode::PostLogin(APlayerController* NewPlayer)
{
    Super::PostLogin(NewPlayer);
    ++CountPlayers;
    UE_LOG(LogTemp, Warning, TEXT("A NEW CHALLENGER! Total players: %d"), CountPlayers);
    if (CountPlayers >= 3)
    {
        UE_LOG(LogTemp, Warning, TEXT("There are 3 players"), CountPlayers);

    }
}

void ALobbyGameMode::Logout(AController* Exiting)
{
    Super::Logout(Exiting);
    --CountPlayers;
    UE_LOG(LogTemp, Warning, TEXT("A Player Left! Total players: %d"), CountPlayers);
}