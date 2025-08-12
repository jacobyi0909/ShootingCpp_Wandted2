// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerPawn.h"
#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"
#include "Components/BoxComponent.h"

APlayerPawn::APlayerPawn()
{
	PrimaryActorTick.bCanEverTick = true;

	// BoxComp를 생성해서 루트컴포넌트로 하고싶다.
	BoxComp = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxComp"));
	SetRootComponent(BoxComp);
	
	MeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshComp"));
	MeshComp->SetupAttachment(RootComponent);

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

