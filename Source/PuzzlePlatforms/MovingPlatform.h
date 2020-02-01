// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/StaticMeshActor.h"
#include "MovingPlatform.generated.h"

// class UFloatingPawnMovement;

/**
 * 
 */
UCLASS()
class PUZZLEPLATFORMS_API AMovingPlatform : public AStaticMeshActor
{
	GENERATED_BODY()
	
public:
	AMovingPlatform();

	void AddActiveTrigger();
	void RemoveActiveTrigger();
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Movement")
	float Speed = 50.0f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Movement", Meta = (MakeEditWidget=true))
	FVector TargetLocation = FVector(0.0f, 0.0f, 0.0f);

private:
	virtual void BeginPlay() override;
	// Called every frame
	virtual void Tick( float DeltaSeconds ) override;

	FVector GlobalTargetLoc = FVector(0.0f, 0.0f, 0.0f);
	FVector InitialLocation = FVector(0.0f, 0.0f, 0.0f);
	FVector CurrentTargetLoc = FVector(0.0f, 0.0f, 0.0f);
	uint8 CurrentTargetId = 1;
	UPROPERTY(EditAnywhere, Category="Movement")
	uint8 ActiveTriggers = 1;

};
