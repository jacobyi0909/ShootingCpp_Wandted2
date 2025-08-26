// Fill out your copyright notice in the Description page of Project Settings.


#include "ShootingGameMode.h"

#include "GameOverWidget.h"
#include "MainWidget.h"

AShootingGameMode::AShootingGameMode()
{
}

void AShootingGameMode::BeginPlay()
{
	Super::BeginPlay();

	MainWidget = CreateWidget<UMainWidget>(GetWorld(), MainWidgetFactory);

	MainWidget->AddToViewport();
	// 체력 게이지를 꽉 채워서 시작하고싶다.
	MainWidget->UpdateHPWidget(1, 1);

	auto* pc = GetWorld()->GetFirstPlayerController();
	pc->SetInputMode(FInputModeGameOnly());
	pc->SetShowMouseCursor(false);
	
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

void AShootingGameMode::ShowGameOverUI()
{
	GameOverWidget = CreateWidget<UGameOverWidget>(GetWorld(), GameOverWidgetFactory);
	GameOverWidget->AddToViewport(10);

	// InputMode 를 UI Only로 하고싶다.
	auto* pc = GetWorld()->GetFirstPlayerController();
	pc->SetInputMode(FInputModeUIOnly());
	pc->SetShowMouseCursor(true);
}