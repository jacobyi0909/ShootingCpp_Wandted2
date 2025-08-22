// Fill out your copyright notice in the Description page of Project Settings.


#include "ShootingGameMode.h"

#include "MainWidget.h"

AShootingGameMode::AShootingGameMode()
{
}

void AShootingGameMode::BeginPlay()
{
	Super::BeginPlay();

	MainWidget = CreateWidget<UMainWidget>(GetWorld(), MainWidgetFactory);

	MainWidget->AddToViewport();
	
}

int32 AShootingGameMode::GetScore()
{
	return Score;
}

void AShootingGameMode::SetScore(int32 NewScore)
{
	Score = NewScore;
	MainWidget->UpdateTextScore(Score);
}
