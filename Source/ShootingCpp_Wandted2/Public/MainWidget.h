// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "MainWidget.generated.h"

/**
 * 
 */
UCLASS()
class SHOOTINGCPP_WANDTED2_API UMainWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	UPROPERTY(meta=(BindWidget))
	class UTextBlock* TextHighScore;

	UPROPERTY(meta=(BindWidget))
	class UTextBlock* TextScore;

	UPROPERTY(meta=(BindWidget))
	class UPlayerHPWidget* PlayerHP;
	

	void UpdateTextScore(int32 HighScore, int32 Score);

	void UpdateHPWidget(const float& curHP, const float& maxHP);
	
	
};
