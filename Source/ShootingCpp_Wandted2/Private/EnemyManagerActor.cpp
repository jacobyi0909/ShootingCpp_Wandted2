// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyManagerActor.h"

#include "EnemyActor.h"
#include "Components/ArrowComponent.h"


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
	// SpawnPoint에 적을 생성하고싶다.
	GetWorld()->SpawnActor<AEnemyActor>(
		EnemyFactory, SpawnPoint->GetComponentTransform());
}

