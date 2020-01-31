// Fill out your copyright notice in the Description page of Project Settings.


#include "PlatformTrigger.h"
#include "Components/BoxComponent.h"
#include "Components/StaticMeshComponent.h"

// Sets default values
APlatformTrigger::APlatformTrigger()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	TriggerVolume = CreateDefaultSubobject<UBoxComponent>(TEXT("Trigger Box"));
	if (!ensure(TriggerVolume != nullptr)) return;
	SetRootComponent(TriggerVolume);
	MeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Trigger Mesh"));
	if (!ensure(MeshComp != nullptr)) return;
	MeshComp->SetupAttachment(TriggerVolume);

}

// Called when the game starts or when spawned
void APlatformTrigger::BeginPlay()
{
	Super::BeginPlay();

	TriggerVolume->OnComponentBeginOverlap.AddDynamic(this, &APlatformTrigger::OnTrigger);
	TriggerVolume->OnComponentEndOverlap.AddDynamic(this, &APlatformTrigger::OnUntrigger);
}

// Called every frame
void APlatformTrigger::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void APlatformTrigger::OnTrigger(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)  
{
	UE_LOG(LogTemp, Warning, TEXT("Activated!"));  
}

void APlatformTrigger::OnUntrigger(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	UE_LOG(LogTemp, Warning, TEXT("Untrigger!"));  
}