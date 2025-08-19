// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "EnemyManagerActor.generated.h"

UCLASS()
class SHOOTINGCPP_WANDTED2_API AEnemyManagerActor : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AEnemyManagerActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// 일정시간마다 적을 생성하고싶다.
	UPROPERTY(EditAnywhere)
	class USceneComponent* RootComp;

	UPROPERTY(EditAnywhere)
	class UArrowComponent* SpawnPoint;

	UPROPERTY(EditAnywhere)
	TSubclassOf<class AEnemyActor> EnemyFactory;

	void MakeEnemy();

	FTimerHandle MakeEnemyTimerHandle;


};
