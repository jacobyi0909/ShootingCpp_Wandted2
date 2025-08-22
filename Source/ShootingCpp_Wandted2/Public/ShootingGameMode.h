// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "ShootingGameMode.generated.h"

/**
 * 
 */
UCLASS()
class SHOOTINGCPP_WANDTED2_API AShootingGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	AShootingGameMode();

	virtual void BeginPlay() override;

private:
	int32 Score;

public:
	__declspec(property(get=GetScore, put=SetScore)) int32 SCORE;
	int32 GetScore();
	void SetScore(int32 NewScore);

	UPROPERTY(EditAnywhere)
	TSubclassOf<class UMainWidget> MainWidgetFactory;

	UPROPERTY()
	class UMainWidget* MainWidget;
	
};
