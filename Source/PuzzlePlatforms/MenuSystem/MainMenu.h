// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "MenuInterface.h"
#include "MainMenu.generated.h"

/**
 * 
 */
UCLASS()
class PUZZLEPLATFORMS_API UMainMenu : public UUserWidget
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	class UEditableTextBox* IPTextbox;
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	class UWidget* MenuWindow;
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	class UWidget* JoinWindow;
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	class UWidgetSwitcher* MenuSwitcher;
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	class UButton* HostButton;
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	class UButton* JoinButton;
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	class UButton* JoinConfirmButton;
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	class UButton* JoinCancelButton;
	void SetMenuInterface(IMenuInterface* DudeWhoImplemented);
	void Setup();
	void Teardown();
private:
	virtual bool Initialize() override;
	UFUNCTION()
	void OnHostClick();
	UFUNCTION()
	void OnJoinClick();
	UFUNCTION()
	void OnJoinConfirmClick();
	UFUNCTION()
	void OnJoinCancelClick();

	IMenuInterface* MenuInterface;

};
