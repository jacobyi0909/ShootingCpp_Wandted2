// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyManagerActor.h"

#include "EnemyActor.h"
#include "EngineUtils.h"
#include "Components/ArrowComponent.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
AEnemyManagerActor::AEnemyManagerActor()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	RootComp = CreateDefaultSubobject<USceneComponent>(TEXT("RootComp"));
	SetRootComponent(RootComp);
	
	SpawnPoint = CreateDefaultSubobject<UArrowComponent>(TEXT("SpawnPoint"));
	SpawnPoint->SetupAttachment(RootComponent);
	SpawnPoint->SetRelativeRotation(FRotator(-90.f, 180.f, 0.f));
}

// Called when the game starts or when spawned
void AEnemyManagerActor::BeginPlay()
{
	Super::BeginPlay();

	//UGameplayStatics::GetAllActorsOfClass(GetWorld(), AActor::StaticClass(), SpawnPoints);
	SpawnPoints.Empty(10);
	for (TActorIterator<AActor> it(GetWorld()); it; ++it)
	{
		AActor* actor = *it;
		// 만약 actor의 이름에 "SpawnPoint"가 포함되어 있다면SpawnPoints에 추가하고싶다.

		if (actor->GetActorNameOrLabel().Contains(TEXT("SpawnPoint")))
		{
			SpawnPoints.Add(actor);
		}
	}
	SpawnPoints.Shrink();

	GetWorld()->GetTimerManager().SetTimer(
		MakeEnemyTimerHandle,
		this,
		&AEnemyManagerActor::MakeEnemy,
		2,
		true);
	
}

void AEnemyManagerActor::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);
	GetWorld()->GetTimerManager().ClearTimer(MakeEnemyTimerHandle);
}

// Called every frame
void AEnemyManagerActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AEnemyManagerActor::MakeEnemy()
{
	static int32 PrevIndex = -1;
	
	// SpawnPoint에 적을 생성하고싶다.
	int32 idx = FMath::RandRange(0, SpawnPoints.Num() - 1);
	// 만약 이전 인덱스와 현재 인덱스가 같다면
	if (idx == PrevIndex)
	{
		// 현재 인덱스를 다른 인덱스로 하고싶다.
		idx = (idx + 1) % SpawnPoints.Num();
		//idx = (idx + SpawnPoints.Num() - 1) % SpawnPoints.Num();
	}
	FTransform t = SpawnPoints[idx]->GetActorTransform();
	GetWorld()->SpawnActor<AEnemyActor>(
		EnemyFactory, t);
	PrevIndex = idx;
}

