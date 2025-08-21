// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyActor.h"

#include "PlayerPawn.h"
#include "Components/BoxComponent.h"
#include "Kismet/KismetMathLibrary.h"

// Sets default values
AEnemyActor::AEnemyActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// BoxComp를 생성해서 루트컴포넌트로 하고싶다.
	BoxComp = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxComp"));
	SetRootComponent(BoxComp);
	MeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshComp"));
	MeshComp->SetupAttachment(RootComponent);

	BoxComp->SetBoxExtent(FVector(50.f));
	MeshComp->SetRelativeLocationAndRotation(
		FVector(0, 0, -40.f),
		FRotator(0, -90.f, 0));
	MeshComp->SetRelativeScale3D(FVector(0.35f));

	ConstructorHelpers::FObjectFinder<UStaticMesh> tempMesh(TEXT("/Script/Engine.StaticMesh'/Game/Shooting/Models/Drone/Drone_low.Drone_low'"));
	// 만약 로딩을 성공했다면
	if (tempMesh.Succeeded())
	{
		// MeshComp의 staticMesh를 업데이트 하고싶다
		MeshComp->SetStaticMesh(tempMesh.Object);
	}
	ConstructorHelpers::FObjectFinder<UMaterial> tempMat(TEXT("/Script/Engine.Material'/Engine/BasicShapes/BasicShapeMaterial.BasicShapeMaterial'"));
	if (tempMat.Succeeded())
	{
		MeshComp->SetMaterial(0, tempMat.Object);
	}

	// Box와 Mesh의 충돌설정을 하고싶다.
	MeshComp->SetGenerateOverlapEvents(false);
	MeshComp->SetCollisionEnabled(ECollisionEnabled::Type::NoCollision);
	
	BoxComp->SetGenerateOverlapEvents(true);
	BoxComp->SetCollisionProfileName(TEXT("Enemy"));

	// BoxComp->SetCollisionEnabled(ECollisionEnabled::Type::QueryAndPhysics);
	// BoxComp->SetCollisionObjectType(ECC_GameTraceChannel2);
	//
	// BoxComp->SetCollisionResponseToAllChannels(ECR_Ignore);
	// BoxComp->SetCollisionResponseToChannel(ECC_GameTraceChannel1, ECR_Overlap);
	// BoxComp->SetCollisionResponseToChannel(ECC_GameTraceChannel3, ECR_Overlap);

}

// Called when the game starts or when spawned
void AEnemyActor::BeginPlay()
{
	Super::BeginPlay();
	
	BoxComp->OnComponentBeginOverlap.AddDynamic(this, &AEnemyActor::OnBoxCompOverlap);

	// 확률
	// int32 seed = GetTypeHash(FString(TEXT("asdfsdfsdafas")));
	// FMath::SRandInit(seed);
	// int32 r2 = static_cast<int32>((FMath::SRand() * 1000)) % 10;
	// srand(seed);
	//UE_LOG(LogTemp, Warning, TEXT("%d, %d"), seed, r);

	int32 r = FMath::RandRange(0, 9);


	// 기본은 앞방향
	Dir = GetActorForwardVector();
	// 30%는 주인공방향
	if (r < 3)
	{
		// 주인공 방향으로 이동하고싶다.
		auto target = GetWorld()->GetFirstPlayerController()->GetPawn();
		Dir = target->GetActorLocation() - this->GetActorLocation();
		Dir.Normalize();
	}

	// 진행방향으로 회전하고싶다.
	FRotator newRot = UKismetMathLibrary::MakeRotFromXZ(Dir, GetActorUpVector());

	SetActorRotation(newRot);
}

// Called every frame
void AEnemyActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	SetActorLocation(GetActorLocation() + Dir * Speed * DeltaTime);
}

void AEnemyActor::NotifyActorBeginOverlap(AActor* OtherActor)
{
	Super::NotifyActorBeginOverlap(OtherActor);
}

void AEnemyActor::OnBoxCompOverlap(UPrimitiveComponent* OverlappedComponent,
	AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex,
	bool bFromSweep, const FHitResult& SweepResult)
{
	// 만약 상대가 플레이어라면
	auto* player = Cast<APlayerPawn>(OtherActor);
	
	if (player)
	{
		//  너죽고 나죽고 하고싶다.
		player->Destroy();
		this->Destroy();
	}
}

