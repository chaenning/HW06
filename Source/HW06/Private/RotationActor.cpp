#include "RotationActor.h"

// Sets default values
ARotationActor::ARotationActor()
{
	SceneRoot = CreateDefaultSubobject<USceneComponent>(TEXT("SceneRoot"));
	SetRootComponent(SceneRoot);

	StaticMeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMesh"));
	StaticMeshComp->SetupAttachment(SceneRoot);

	PrimaryActorTick.bCanEverTick = true;
	RotationSpeed = 90.0f;
	RotationDirection = 1;
}

// Called when the game starts or when spawned
void ARotationActor::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ARotationActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (!FMath::IsNearlyZero(RotationSpeed))
	{
		AddActorLocalRotation(FRotator(0.0f, RotationSpeed * RotationDirection * DeltaTime, 0.0f));
	}
}

void ARotationActor::SetRotation()
{
	RotationDirection = FMath::RandBool() ? 1.0f : -1.0f;
	RotationSpeed = FMath::FRandRange(50.f, 200.f);
}

