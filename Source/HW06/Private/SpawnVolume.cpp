#include "SpawnVolume.h"
#include "Components/BoxComponent.h"
#include "Engine/World.h"
#include "RotationActor.h"
#include "GameFramework/Actor.h"

// Sets default values
ASpawnVolume::ASpawnVolume()
{
    PrimaryActorTick.bCanEverTick = false;

    Scene = CreateDefaultSubobject<USceneComponent>(TEXT("Scene"));
    SetRootComponent(Scene);

    SpawningBox = CreateDefaultSubobject<UBoxComponent>(TEXT("SpawningBox"));
    SpawningBox->SetupAttachment(Scene);
    SpawnCount = 10;
}

void ASpawnVolume::BeginPlay()
{
    for(int i =0; i< SpawnCount; i++)
    {
        SpawPlatform();
    }
}

FVector ASpawnVolume::GetRandomPointInVolume() const
{
    FVector BoxExtent = SpawningBox->GetScaledBoxExtent();
    FVector BoxOrigin = SpawningBox->GetComponentLocation();

    return BoxOrigin + FVector(
        FMath::FRandRange(-BoxExtent.X, BoxExtent.X),
        FMath::FRandRange(-BoxExtent.Y, BoxExtent.Y),
        FMath::FRandRange(-BoxExtent.Z, BoxExtent.Z)
    );
}

void ASpawnVolume::SpawPlatform()
{
    if (!PlatformClass) return;

    AActor* SpawnedActor = GetWorld()->SpawnActor<AActor>(
        PlatformClass,
        GetRandomPointInVolume(),
        FRotator::ZeroRotator
    );

    if (ARotationActor* RotationActor = Cast<ARotationActor>(SpawnedActor))
    {
        RotationActor->SetRotation();
    }
}
