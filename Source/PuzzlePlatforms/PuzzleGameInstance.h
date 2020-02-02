// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "PuzzleGameInstance.generated.h"

/**
 * 
 */
UCLASS()
class PUZZLEPLATFORMS_API UPuzzleGameInstance : public UGameInstance
{
	GENERATED_BODY()

public:
	UPuzzleGameInstance();
	virtual void Init() override;

	UFUNCTION(Exec, BlueprintCallable)
	void LoadMenu();
	UFUNCTION(Exec)
	void Host();
	UFUNCTION(Exec)
	void Join(const FString& Address);

private:
	class TSubclassOf<class UUserWidget> MenuClass;
	
};
