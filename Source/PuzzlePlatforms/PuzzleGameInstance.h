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

	UFUNCTION(Exec, BlueprintCallable)
	void GoToMainMenu() override;
	UFUNCTION(Exec, BlueprintCallable)
	void LoadMenu();
	UFUNCTION(Exec, BlueprintCallable)
	void LoadInGameMenu();
	UFUNCTION(Exec)
	void Host() override;
	void Join() override;
	UFUNCTION(Exec)
	void Join(const FString& Address) override;


private:
	void OnCreateSessionComplete(FName, bool);

	class TSubclassOf<class UUserWidget> MenuClass;
	class TSubclassOf<class UUserWidget> InGameMenuClass;

	class UMainMenu* Menu;
	class UMenuWidget* InGameMenu;
	IOnlineSessionPtr SessionInterface;
};
