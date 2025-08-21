// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerPawn.h"

#include "BulletActor.h"
#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"
#include "Components/ArrowComponent.h"
#include "Components/BoxComponent.h"
#include "Kismet/GameplayStatics.h"

APlayerPawn::APlayerPawn()
{
	PrimaryActorTick.bCanEverTick = true;

	// BoxComp를 생성해서 루트컴포넌트로 하고싶다.
	BoxComp = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxComp"));
	SetRootComponent(BoxComp);
	
	MeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshComp"));
	MeshComp->SetupAttachment(RootComponent);

	MeshComp->SetRelativeRotation(FRotator(0.f, 90.f, 90.f));
	MeshComp->SetRelativeScale3D(FVector(0.575f));
	

	ConstructorHelpers::FObjectFinder<UStaticMesh> tempMesh(TEXT("/Script/Engine.StaticMesh'/Game/Shooting/Models/SpaceShip/Spaceship_ARA.Spaceship_ARA'"));
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

	FirePointComp = CreateDefaultSubobject<UArrowComponent>(TEXT("FirePointComp"));
	FirePointComp->SetupAttachment(RootComponent);
	
	// Box와 Mesh의 충돌설정을 하고싶다.
	MeshComp->SetGenerateOverlapEvents(false);
	MeshComp->SetCollisionEnabled(ECollisionEnabled::Type::NoCollision);
	
	BoxComp->SetGenerateOverlapEvents(true);
	BoxComp->SetCollisionProfileName(TEXT("Player"));
}

// Called when the game starts or when spawned
void APlayerPawn::BeginPlay()
{
	Super::BeginPlay();

	APlayerController* pc = GetWorld()->GetFirstPlayerController();
	
	UEnhancedInputLocalPlayerSubsystem* subsys = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(pc->GetLocalPlayer());

	 if (subsys)
	 {
	 	subsys->AddMappingContext(IMC_Player, 0);
	 }
}

void APlayerPawn::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);
	
	GetWorldTimerManager().ClearTimer(MakeBulletTimerHandle);
}

// Called every frame
void APlayerPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	// P = P0 + vt
	FVector P0 = GetActorLocation();
	FVector direction = FVector(0, H, V);
	direction.Normalize();
	FVector velocity = direction * Speed;

	SetActorLocation(P0 + velocity * DeltaTime);

	// SetActorLocation(GetActorLocation() + FVector(0, H, V).GetSafeNormal() * Speed * DeltaTime);

	H = V = 0;

	if (AutoFireType::Interval == AutoFireType)
	{
		// 만약 bAutoFire가 true라면
		if (true == bAutoFire)
		{
			// 1. 시간이 흐르다가
			CurrentTime += DeltaTime;
			// 2. 만약 현재시간이 생성시간이 초과하면
			if (CurrentTime > MakeBulletTime)
			{
				// 3.	총알을 생성하고싶다.
				MakeBullet();
				// 4.	현재시간을 0으로 하고 싶다.
				CurrentTime = 0;
			}
		}
	}
}

// Called to bind functionality to input
void APlayerPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	// PlayerInputComponent->BindAxis(TEXT("Horizontal"), this, &APlayerPawn::OnMyHorizontal);
	//
	// PlayerInputComponent->BindAxis(TEXT("Vertical"), this, &APlayerPawn::OnMyVertical);
	UEnhancedInputComponent* input = CastChecked<UEnhancedInputComponent>(PlayerInputComponent);

	//check(nullptr == input)
	
	
	if (input)
	{
		input->BindAction(IA_Move, ETriggerEvent::Triggered, this, &APlayerPawn::OnMyMove);
		
		input->BindAction(IA_Fire, ETriggerEvent::Started, this, &APlayerPawn::OnMyFirePressed);
		input->BindAction(IA_Fire, ETriggerEvent::Completed, this, &APlayerPawn::OnMyFireReleased);
	}
	
}

void APlayerPawn::OnMyHorizontal(float Value)
{
	H = Value;
	//UE_LOG(LogTemp, Warning, TEXT("%s"), *FString(__FUNCTION__))
}

void APlayerPawn::OnMyVertical(float Value)
{
	V = Value;
	//UE_LOG(LogTemp, Warning, TEXT("%s"), *FString(__FUNCTION__))
}

void APlayerPawn::OnMyMove(const FInputActionValue& Value)
{
	FVector2D v = Value.Get<FVector2D>();
	V = v.X;
	H = v.Y;
}

void APlayerPawn::MakeBullet()
{
	// 총알을 FirePoint에 배치하도록 생성하고싶다.
	FTransform t = FirePointComp->GetComponentTransform();
	GetWorld()->SpawnActor<ABulletActor>(BulletFactory, t);

	// 총알 발사음을 출력하고 싶다.
	if (FireSound)
	{
		UGameplayStatics::PlaySound2D(GetWorld(), FireSound);
	}

	// ABulletActor를 Cpp로 완성하는 경우는 아래와같이 UClass를 가져와서 Spawn한다.
	//GetWorld()->SpawnActor<ABulletActor>(ABulletActor::StaticClass(), t);
}

void APlayerPawn::OnMyFirePressed(const FInputActionValue& Value)
{
	if (AutoFireType == AutoFireType::Interval)
	{
		bAutoFire = true;
		CurrentTime = 0;
		MakeBullet();
	}
	else if (AutoFireType == AutoFireType::Timer)
	{
		// 키를 누르면 타이머를 이용해서 MakeBullet을 반복적으로 호출하고 싶다.
		GetWorld()->GetTimerManager().SetTimer(MakeBulletTimerHandle, this, &APlayerPawn::MakeBullet, MakeBulletTime, true);
		MakeBullet();
	}
}
void APlayerPawn::OnMyFireReleased(const FInputActionValue& Value)
{
	if (AutoFireType == AutoFireType::Interval)
	{
		bAutoFire = false;
	}
	else if (AutoFireType == AutoFireType::Timer)
	{
		// 키를 떼면 타이머를 멈추고싶다.
		GetWorld()->GetTimerManager().ClearTimer(MakeBulletTimerHandle);
	}
}
