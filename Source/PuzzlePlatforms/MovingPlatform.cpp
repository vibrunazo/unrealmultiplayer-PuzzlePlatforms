// Fill out your copyright notice in the Description page of Project Settings.


#include "MovingPlatform.h"
#include "Math/Vector.h"

AMovingPlatform::AMovingPlatform()
{
    PrimaryActorTick.bCanEverTick = true;
    SetMobility(EComponentMobility::Movable);
}

void AMovingPlatform::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
    if (HasAuthority())
    {
        AddActorLocalOffset(FVector(Speed * DeltaTime, 0.0f, 0.0f));
    }

}