// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "PlayerHPWidget.generated.h"

/**
 * 
 */
UCLASS()
class SHOOTINGCPP_WANDTED2_API UPlayerHPWidget : public UUserWidget
{
	GENERATED_BODY()
public:
	UPROPERTY(meta=(BindWidget))
	class UProgressBar* HPBar;

	UPROPERTY(meta=(BindWidget))
	class UTextBlock* TextHP;

	void UpdateHPWidget(const float& curHP, const float& maxHP);
};
