// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "InputActionValue.h"
#include "GameFramework/Pawn.h"
#include "PlayerPawn.generated.h"


enum class AutoFireType
{
	Interval,
	Timer,
};

//class UStaticMeshComponent; //전방선언 정식으로 쓰는 표현식

UCLASS()
class SHOOTINGCPP_WANDTED2_API APlayerPawn : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	APlayerPawn();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class UBoxComponent* BoxComp;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class UStaticMeshComponent* MeshComp;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float Speed = 500.f;

	void OnMyHorizontal(float Value);
	void OnMyVertical(float Value);

	float H;
	float V;

	UPROPERTY(EditAnywhere)
	class UInputMappingContext* IMC_Player;

	UPROPERTY(EditAnywhere)
	class UInputAction* IA_Move;

	UPROPERTY(EditAnywhere)
	class UInputAction* IA_Fire;

	void OnMyMove(const FInputActionValue& Value);
	void OnMyFirePressed(const FInputActionValue& Value);
	void OnMyFireReleased(const FInputActionValue& Value);

	// 총구위치를 만들고싶다.
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class UArrowComponent* FirePointComp;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<class ABulletActor> BulletFactory;

	void MakeBullet();
	bool bAutoFire;

	float CurrentTime;
	float MakeBulletTime = 0.25f;

	AutoFireType AutoFireType = AutoFireType::Timer;
	FTimerHandle MakeBulletTimerHandle;

	UPROPERTY(EditAnywhere)
	class USoundBase* FireSound;


};

