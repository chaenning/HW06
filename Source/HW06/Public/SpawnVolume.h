#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SpawnVolume.generated.h"

class UBoxComponent;

UCLASS()
class HW06_API ASpawnVolume : public AActor
{
	GENERATED_BODY()
	
public:	
	ASpawnVolume();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spawing")
	TSubclassOf<AActor> PlatformClass;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Spawing")
	USceneComponent* Scene;
	// ���� ������ ����� �ڽ� ������Ʈ
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Spawing")
	UBoxComponent* SpawningBox;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spawing")
	int32 SpawnCount;

	UFUNCTION(BlueprintCallable, Category = "Spawning")
	FVector GetRandomPointInVolume() const;

	UFUNCTION(BlueprintCallable, Category = "Spawning")
	void SpawPlatform();

	virtual void BeginPlay() override;
};
