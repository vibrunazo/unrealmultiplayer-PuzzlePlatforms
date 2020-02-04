// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "PuzzleController.generated.h"

/**
 * 
 */
UCLASS()
class PUZZLEPLATFORMS_API APuzzleController : public APlayerController
{
	GENERATED_BODY()

	virtual void BeginPlay() override;

	virtual void SetupInputComponent() override;

	void InputMenu();
	
};
