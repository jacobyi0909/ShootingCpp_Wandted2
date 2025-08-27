// Fill out your copyright notice in the Description page of Project Settings.


#include "BulletActor.h"

#include "EnemyActor.h"
#include "MainWidget.h"
#include "PlayerPawn.h"
#include "ShootingGameMode.h"
#include "Components/BoxComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Particles/ParticleSystem.h"

// Sets default values
ABulletActor::ABulletActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	// BoxComp를 생성해서 루트컴포넌트로 하고싶다.
	BoxComp = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxComp"));
	SetRootComponent(BoxComp);
	BoxComp->SetBoxExtent(FVector(37.5f, 12.5f, 50.f));
	
	MeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshComp"));
	MeshComp->SetupAttachment(RootComponent);
	MeshComp->SetWorldScale3D(FVector(0.75f, 0.25f, 1.f));

	ConstructorHelpers::FObjectFinder<UStaticMesh> tempMesh(TEXT("/Script/Engine.StaticMesh'/Engine/BasicShapes/Cube.Cube'"));
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
	BoxComp->SetCollisionProfileName(TEXT("Bullet"));

	ConstructorHelpers::FObjectFinder<UParticleSystem> tempExpVFX(TEXT("/Script/Engine.ParticleSystem'/Game/StarterContent/Particles/P_Explosion.P_Explosion'"));

	if (tempExpVFX.Succeeded())
	{
		ExplosionVFX = tempExpVFX.Object;
	}
	
	ConstructorHelpers::FObjectFinder<USoundBase> tempExpSound(TEXT("/Script/Engine.SoundWave'/Game/Shooting/Sounds/Explosion.Explosion'"));

	if (tempExpSound.Succeeded())
	{
		ExplosionSound = tempExpSound.Object;
	}
	
	
}

// Called when the game starts or when spawned
void ABulletActor::BeginPlay()
{
	Super::BeginPlay();

	BoxComp->OnComponentBeginOverlap.AddDynamic(
		this,
		&ABulletActor::OnBoxCompOverlap
	);
	
}

// Called every frame
void ABulletActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (false == MeshComp->IsVisible())
	{
		return;
	}
	
	// 나의 앞 방향을 구하고 싶다.
	FVector dir = GetActorForwardVector();
	// 그 방향으로 이동하고싶다.
	SetActorLocation(GetActorLocation() + dir * Speed * DeltaTime);

}

void ABulletActor::NotifyActorBeginOverlap(AActor* OtherActor)
{
	Super::NotifyActorBeginOverlap(OtherActor);

	// // 만약 상대가 Enemy이라면
	// AEnemyActor* enemy = Cast<AEnemyActor>(OtherActor);
	// if (enemy)
	// {
	// 	// 너죽고 나죽고 하고싶다.
	// 	enemy->Destroy();
	// 	this->Destroy();
	// }
}

void ABulletActor::OnBoxCompOverlap(
	UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep,
	const FHitResult& SweepResult)
{
	// 만약 상대가 Enemy이라면
	AEnemyActor* enemy = Cast<AEnemyActor>(OtherActor);
	if (enemy)
	{
		// 적이 할일
		// 적의 체력을 1 감소하고싶다.
		enemy->HP -= 1;
		// 만약 적의 체력이 0이하라면
		if (enemy->HP <= 0)
		{
			// 점수를 1점 추가하고싶다.
			auto* gameMode = Cast<AShootingGameMode>(GetWorld()->GetAuthGameMode());

			//gameMode->SetScore(gameMode->GetScore() + 1);
			gameMode->SCORE += 1;
		
			// 너죽고 나죽고 하고싶다.
			enemy->Destroy();
		}
		
		// 총알이 할일
		
		// VFX를 표현하고싶다.
		UGameplayStatics::SpawnEmitterAtLocation(
			GetWorld(),
			ExplosionVFX,
			GetActorLocation()
		);
		// 소리도 재생하고싶다.
		UGameplayStatics::PlaySound2D(GetWorld(), ExplosionSound);

		//this->Destroy();
		// 비활성화 하고 
		SetActive(false);
		// 주인공의 탄창에 나를 넣고싶다.
		auto player = Cast<APlayerPawn>(
			GetWorld()->GetFirstPlayerController()->GetPawn());
		player->Magazine.Add(this);
	}
}

// bool B()
// {
// 	return true;
// }
//
// bool A()
// {
// 	return B() ? A() : B() ? A() : B() ? A() : B();
// }

void ABulletActor::SetActive(bool value)
{
	// 외형을 보이거나 안보이게 하고싶다.
	MeshComp->SetVisibility(value);
	// 충돌체를 켜거나 끄고싶다.
	BoxComp->SetCollisionEnabled(
		value ?
		ECollisionEnabled::Type::QueryAndPhysics :
		ECollisionEnabled::Type::NoCollision);
}
