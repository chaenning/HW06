// Fill out your copyright notice in the Description page of Project Settings.


#include "MovingPlatform.h"

// Sets default values
AMovingPlatform::AMovingPlatform()
{
	SceneRoot = CreateDefaultSubobject<USceneComponent>(TEXT("SceneRoot"));
	SetRootComponent(SceneRoot);

	StaticMeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMesh"));
	StaticMeshComp->SetupAttachment(SceneRoot);

	PrimaryActorTick.bCanEverTick = true;
	MoveSpeed = 90.0f;
	MoveDirection = FVector(0.0f, 0.0f, 1.0f);
	StartDistance = 0.0f;
	MoveDistance = 500.0f;
	MoveDelay = 3.0f;
	bIsPaused = false;
}

// Called when the game starts or when spawned
void AMovingPlatform::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AMovingPlatform::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (!FMath::IsNearlyZero(MoveSpeed) && !bIsPaused)
	{
		FVector Offset = MoveDirection * MoveSpeed * DeltaTime;
		AddActorWorldOffset(Offset, true);

		StartDistance += Offset.Size();

		if (StartDistance >= MoveDistance) // 방향 전환
		{
			bIsPaused = true;
			if (FMath::IsNearlyZero(MoveDelay))
			{
				ResumeMovement();
			}
			else
			{
				GetWorld()->GetTimerManager().SetTimer(
					PauseTimerHandle,
					this,
					&AMovingPlatform::ResumeMovement,
					MoveDelay
				);
			}
		}
	}
}

void AMovingPlatform::ResumeMovement()
{
	MoveDirection *= -1;
	StartDistance = 0.f;
	bIsPaused = false;
}
