// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerPawn.h"
#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"


// Sets default values
APlayerPawn::APlayerPawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	MeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshComp"));
	MeshComp->SetupAttachment(RootComponent);

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

