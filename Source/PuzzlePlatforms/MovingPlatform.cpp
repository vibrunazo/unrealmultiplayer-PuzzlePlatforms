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
        GlobalTargetLoc = GetTransform().TransformPosition(TargetLocation);
        CurrentTargetLoc = GlobalTargetLoc;
    }
    InitialLocation = GetActorLocation();
}

void AMovingPlatform::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
    if (HasAuthority())
    {
        // FVector CurLoc = GetActorLocation();
        // FVector Direction = TargetLocation - CurLoc;
        FVector Direction = CurrentTargetLoc - GetActorLocation();
        Direction.Normalize();
        if (FVector::Dist(GetActorLocation(), CurrentTargetLoc) > Speed * DeltaTime)
        {
            AddActorLocalOffset(Direction * Speed * DeltaTime);

        }
        else
        {
            SetActorLocation(CurrentTargetLoc);
            if (CurrentTargetId == 0)
            {
                CurrentTargetId = 1;
                CurrentTargetLoc = GlobalTargetLoc;
            }
            else 
            {
                CurrentTargetId = 0;
                CurrentTargetLoc = InitialLocation;
            }
        }
        // AddActorLocalOffset(FVector(Speed * DeltaTime, 0.0f, 0.0f));
    }

}