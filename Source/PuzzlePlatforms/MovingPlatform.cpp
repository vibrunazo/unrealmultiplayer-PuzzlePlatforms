// Fill out your copyright notice in the Description page of Project Settings.


#include "MovingPlatform.h"
#include "Math/Vector.h"

AMovingPlatform::AMovingPlatform()
{
    PrimaryActorTick.bCanEverTick = true;
    SetMobility(EComponentMobility::Movable);
}

void AMovingPlatform::BeginPlay()
{
    Super::BeginPlay();

    if (HasAuthority())
    {
        SetReplicates(true);
        SetReplicateMovement(true);
    }
}

void AMovingPlatform::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
    if (HasAuthority())
    {
        // FVector CurLoc = GetActorLocation();
        // FVector Direction = TargetLocation - CurLoc;
        FVector Direction = TargetLocation;
        Direction.Normalize();
        AddActorLocalOffset(Direction * Speed * DeltaTime);
        // AddActorLocalOffset(FVector(Speed * DeltaTime, 0.0f, 0.0f));
    }

}