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

	// 태어날 때 레벨에 존재하는 SpawnPoint들을 찾아서 목록으로 기억하고 싶다.
	// MakeEnemy에서 목록에 있는것중에 랜덤으로 하나 정해서 Transform으로 사용하고 싶다.

	UPROPERTY(VisibleAnywhere)
	TArray<class AActor*> SpawnPoints;

};
