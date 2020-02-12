// Fill out your copyright notice in the Description page of Project Settings.


#include "RowWidget.h"
#include "MainMenu.h"
#include "Components/Button.h"

void URowWidget::Setup(class UMainMenu* Parent, int32 NewIndex)
{
    MyParent = Parent;
    MyIndex = NewIndex;

    if (!ensure(RowButton != nullptr)) return;
    RowButton->OnClicked.AddDynamic(this, &URowWidget::OnRowClick);
}

void URowWidget::OnRowClick()
{
    MyParent->SelectIndex(MyIndex);
    bIsSelected = true;
    UE_LOG(LogTemp, Warning, TEXT("Set to true"));
}

// void URowWidget::DeSelect()
// {
//     bIsSelected = false;
// }