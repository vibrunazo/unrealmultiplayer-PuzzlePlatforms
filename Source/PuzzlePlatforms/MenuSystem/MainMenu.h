// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MenuWidget.h"
#include "MainMenu.generated.h"

USTRUCT()
struct FServerData
{
	GENERATED_BODY()
	
	FString Name;
	uint16 CurrentPlayers;
	uint16 MaxPlayers;
	FString HostUsername;
	int32 Ping;
};

/**
 * 
 */
UCLASS()
class PUZZLEPLATFORMS_API UMainMenu : public UMenuWidget
{
	GENERATED_BODY()

public:
	UMainMenu(const FObjectInitializer &ObjectInitializer);
	void SetServerList(TArray<FServerData> ServerNames);
	void SelectIndex(int32 NewIndex);
	void UpdateChildren();

	// UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	// class UEditableTextBox* IPTextbox;
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	class UScrollBox* ServerList;
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	class UWidget* MenuWindow;
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	class UWidget* JoinWindow;
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	class UWidget* HostWindow;
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
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	class UButton* HostConfirmButton;
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	class UEditableTextBox* HostTextBox;
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	class UButton* HostCancelButton;
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	class UButton* QuitButton;
	
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
	UFUNCTION()
	void OnHostConfirmClick();
	UFUNCTION()
	void OnHostCancelClick();
	UFUNCTION()
	void OnQuitClick();

	TSubclassOf<class UUserWidget> RowClass;
	TOptional<uint32> SelectedIndex;
	// TArray<class URowWidget*> RowList;

};
