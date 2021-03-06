// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "MenuSystem/MenuInterface.h"
#include "OnlineSubsystem.h"
#include "OnlineSessionSettings.h"
#include "Interfaces/OnlineSessionInterface.h"
#include "PuzzleGameInstance.generated.h"

/**
 * 
 */
UCLASS()
class PUZZLEPLATFORMS_API UPuzzleGameInstance : public UGameInstance, public IMenuInterface
{
	GENERATED_BODY()

public:
	UPuzzleGameInstance();
	virtual void Init() override;
	void CreateSession();

	UFUNCTION(Exec, BlueprintCallable)
	void GoToMainMenu() override;
	UFUNCTION(Exec, BlueprintCallable)
	void LoadMenu();
	UFUNCTION(Exec, BlueprintCallable)
	void LoadInGameMenu();
	// UFUNCTION(Exec)
	// void Host() override;
	UFUNCTION(Exec)
	void Host(FString NewServerName) override;
	// void Join() override;
	// UFUNCTION(Exec)
	// void Join(const FString& Address) override;
	UFUNCTION(Exec)
	void Join(uint32 Index) override;
	void MenuNeedsSessions() override;
	void StartSession();


private:
	void OnCreateSessionComplete(FName, bool);
	void OnDestroySessionComplete(FName SessionName, bool bWasSuccessful);
	void OnFindSessionsComplete(bool);
	void OnJoinSessionComplete(FName SessionName, EOnJoinSessionCompleteResult::Type Result);

	class TSubclassOf<class UUserWidget> MenuClass;
	class TSubclassOf<class UUserWidget> InGameMenuClass;

	class UMainMenu* Menu;
	class UMenuWidget* InGameMenu;
	IOnlineSessionPtr SessionInterface;
	TSharedPtr<FOnlineSessionSearch> SessionSearch;
	// whether we need a new session to be created after one is destroyed
	bool bNeedsNewSession = false;
	FString CustomServerName = "New Server";
};
