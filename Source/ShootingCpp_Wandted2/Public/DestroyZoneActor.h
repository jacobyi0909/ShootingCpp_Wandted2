// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "DestroyZoneActor.generated.h"

DECLARE_DELEGATE_OneParam(FDelegateSingle, int32);
DECLARE_MULTICAST_DELEGATE_OneParam(FDelegateMulti, int32);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FDelegateDynamicMulti, int32, NewValue);

DECLARE_DELEGATE_RetVal_TwoParams(int32, FDelegateSingleRet, int32, int32);

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


	// 델리게이트, 이벤트
	DECLARE_EVENT_OneParam(ADestroyZone, FDestroyZoneEvent, int32);
	FDestroyZoneEvent DestroyZoneEvent;

	FDelegateSingle DelegateSingle;
	FDelegateMulti DelegateMulti;
	FDelegateDynamicMulti DelegateDynamicMulti;

	FDelegateSingleRet DelegateAdd;

	int32 MyAdd(int32 a, int32 b);

	UFUNCTION()
	void DelegateTestFunction(int32 NewValue);
};


