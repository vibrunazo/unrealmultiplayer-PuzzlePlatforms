// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "MenuSystem/MenuInterface.h"
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
	void LoadMenu();
	UFUNCTION(Exec, BlueprintCallable)
	void LoadInGameMenu();
	UFUNCTION(Exec)
	void Host();
	void Join();
	UFUNCTION(Exec)
	void Join(const FString& Address);

private:
	class TSubclassOf<class UUserWidget> MenuClass;
	class TSubclassOf<class UUserWidget> InGameMenuClass;

	class UMainMenu* Menu;
	class UMenuWidget* InGameMenu;
	
};
