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
	BoxComp->OnComponentBeginOverlap.AddDynamic(
		this, &ADestroyZoneActor::OnBoxCompOverlap);

	DelegateSingle.BindUObject(this, &ADestroyZoneActor::DelegateTestFunction);

	// Lambda 람다식 - 대단히 소 중 하다
	int32 ak = 0;	// 지역변수를 캡쳐할때는 레퍼런스 타입 형태로 사용함.
	auto AddFunction = [this, &ak](int32 a, int32 b)->int32
	{
		ak = 0;
		return a + b;
	};

	int32 result = AddFunction(1, 2);

	DelegateSingle.BindLambda([this](int32 NewValue)
	{
	});

	DelegateAdd.BindUObject(this, &ADestroyZoneActor::MyAdd);


	DelegateMulti.AddUObject(this, &ADestroyZoneActor::DelegateTestFunction);
	
	DelegateDynamicMulti.AddDynamic(this, &ADestroyZoneActor::DelegateTestFunction);
	
	DelegateSingle.Execute(10);
	int32 r = DelegateAdd.Execute(10, 20);
	DelegateMulti.Broadcast(10);
	DelegateDynamicMulti.Broadcast(10);


	DestroyZoneEvent.AddUObject(this, &ADestroyZoneActor::DelegateTestFunction);
	DestroyZoneEvent.Broadcast(10);
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

void ADestroyZoneActor::DelegateTestFunction(int32 NewValue)
{
	UE_LOG(LogTemp, Warning, TEXT("DelegateTestFunction"));
}
int32 ADestroyZoneActor::MyAdd(int32 a, int32 b)
{
	return a  + b;
}
