// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "DestroyZoneActor.generated.h"

UCLASS()
class SHOOTINGCPP_WANDTED2_API ADestroyZoneActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ADestroyZoneActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// 충돌체 컴포넌트를 생성해서 루트로 하고싶다.
	UPROPERTY(EditAnywhere)
	TObjectPtr<class UBoxComponent> BoxComp;
	// StaticMesh도 만들어서 루트에 붙이고싶다.
	UPROPERTY(EditAnywhere)
	TObjectPtr<class UStaticMeshComponent> MeshComp;
	
	// 만약 누군가 나와 충돌했다면 파괴하고싶다.
	UFUNCTION()
	void OnBoxCompOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	
	

};
