// Fill out your copyright notice in the Description page of Project Settings.


#include "DestroyZoneActor.h"

#include "BulletActor.h"
#include "EnemyActor.h"
#include "Components/BoxComponent.h"

// Sets default values
ADestroyZoneActor::ADestroyZoneActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	BoxComp = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxComp"));
	SetRootComponent(BoxComp);
	BoxComp->SetBoxExtent(FVector(50.f));

	MeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshComp"));
	MeshComp->SetupAttachment(RootComponent);

	BoxComp->SetGenerateOverlapEvents(true);
	BoxComp->SetCollisionProfileName(TEXT("DestroyZone"));
	
	MeshComp->SetGenerateOverlapEvents(false);
	MeshComp->SetCollisionEnabled(ECollisionEnabled::Type::NoCollision);
}

// Called when the game starts or when spawned
void ADestroyZoneActor::BeginPlay()
{
	Super::BeginPlay();
	BoxComp->OnComponentBeginOverlap.AddDynamic(this, &ADestroyZoneActor::OnBoxCompOverlap);
}

// Called every frame
void ADestroyZoneActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ADestroyZoneActor::OnBoxCompOverlap(
	UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep,
	const FHitResult& SweepResult)
{
	// 너만 파괴되어라

	//if (OtherActor->IsA<ABulletActor>() ||		OtherActor->IsA<AEnemyActor>())
	//{
		OtherActor->Destroy();
	//} 
}