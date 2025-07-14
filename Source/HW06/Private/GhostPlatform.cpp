// Fill out your copyright notice in the Description page of Project Settings.


#include "GhostPlatform.h"

// Sets default values
AGhostPlatform::AGhostPlatform()
{
	SceneRoot = CreateDefaultSubobject<USceneComponent>(TEXT("SceneRoot"));
	SetRootComponent(SceneRoot);

	StaticMeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMesh"));
	StaticMeshComp->SetupAttachment(SceneRoot);

	PrimaryActorTick.bCanEverTick = true;

}


void AGhostPlatform::BeginPlay()
{
	Super::BeginPlay();
	ToggleVisibility();
}


void AGhostPlatform::ToggleVisibility()
{
    bIsVisible = !bIsVisible;

    SetActorHiddenInGame(!bIsVisible);
    SetActorEnableCollision(bIsVisible);

    float NextDelay = bIsVisible ? VisibleDuration : HiddenDuration;

    GetWorld()->GetTimerManager().SetTimer(
        ToggleTimer,
        this,
        &AGhostPlatform::ToggleVisibility,
        NextDelay,
        false
    );
}
