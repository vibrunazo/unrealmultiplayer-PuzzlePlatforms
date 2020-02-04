// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MenuWidget.h"
#include "InGameMenu.generated.h"

/**
 * 
 */
UCLASS()
class PUZZLEPLATFORMS_API UInGameMenu : public UMenuWidget
{
	GENERATED_BODY()
public:
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	class UButton* CancelButton;
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	class UButton* QuitButton;
private:
	virtual bool Initialize() override;
	UFUNCTION()
	void OnCancelClick();
	UFUNCTION()
	void OnQuitClick();
};
