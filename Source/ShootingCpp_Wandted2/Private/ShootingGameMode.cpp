// Fill out your copyright notice in the Description page of Project Settings.


#include "ShootingGameMode.h"

#include "GameOverWidget.h"
#include "MainWidget.h"
#include "ShootingSaveGame.h"
#include "Kismet/GameplayStatics.h"

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

	// 시작할 때 파일을 읽어서 HishScore의 값을 가져오고싶다.
	MyLoadGame();
	MainWidget->UpdateTextScore(HIGH_SCORE, Score);
	
}

int32 AShootingGameMode::GetScore()
{
	return Score;
}

void AShootingGameMode::SetScore(int32 NewScore)
{
	Score = NewScore;
	// 만약 NewScore가 HighScore 보다 크다면
	if (Score > HIGH_SCORE)
	{
		// HighScore 를 갱신하고싶다.
		HIGH_SCORE = Score;
		MySaveGame();
	}
	MainWidget->UpdateTextScore(HIGH_SCORE, Score);
}

int32 AShootingGameMode::GetHighScore()
{
	return HighScore;
}

void AShootingGameMode::SetHighScore(int32 NewHighScore)
{
	HighScore = NewHighScore;
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

void AShootingGameMode::MySaveGame()
{
	// 세이브게임 객체를 생성해서
	auto* instance = Cast<UShootingSaveGame>(
		UGameplayStatics::CreateSaveGameObject(UShootingSaveGame::StaticClass()));
	if (instance)
	{
		// instance에 실제로 저장할 정보를 담고싶다.
		instance->Save_HighScore = HIGH_SCORE;
		// 파일로 저장하고싶다.
		bool bSuccess = UGameplayStatics::SaveGameToSlot(instance, SaveSlotName, SaveUserIndex);

		if (!bSuccess)
		{
			// UI로 실패 출력
		}
	}
}

void AShootingGameMode::MyLoadGame(int32 defaultHighScore)
{
	// 파일이 존재한다면
	if (!UGameplayStatics::DoesSaveGameExist(SaveSlotName, SaveUserIndex))
	{
		HighScore = defaultHighScore;
		return;
	}
	// Load하고 세이브 게임 객체의 정보를 이용하고싶다.
	auto* instance = Cast<UShootingSaveGame>(
		UGameplayStatics::LoadGameFromSlot(SaveSlotName, SaveUserIndex));

	HighScore = instance->Save_HighScore;
}
