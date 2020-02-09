// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "RowWidget.generated.h"

/**
 * 
 */
UCLASS()
class PUZZLEPLATFORMS_API URowWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	// called from the parent to setup both who my parent is and what my index is
	void Setup(class UMainMenu* Parent, uint32 NewIndex);
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	class UTextBlock* ServerName;
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	class UButton* RowButton;
private:
	UFUNCTION()
	void OnRowClick();
	UPROPERTY()
	class UMainMenu* MyParent = nullptr;
	uint32 MyIndex = 0;
};
