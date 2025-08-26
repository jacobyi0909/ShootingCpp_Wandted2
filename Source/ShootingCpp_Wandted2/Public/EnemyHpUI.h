// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "EnemyHpUI.generated.h"

/**
 * 
 */
UCLASS()
class SHOOTINGCPP_WANDTED2_API UEnemyHpUI : public UUserWidget
{
	GENERATED_BODY()
public:
	virtual void NativeConstruct() override;
	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;
	
	UPROPERTY(meta=(BindWidget))
	class UProgressBar* HPBar;

	UPROPERTY(meta=(BindWidget))
	class UProgressBar* HPBarBG;

	void UpdateHPWidget(const float& curHP, const float& maxHP);
	
	
};
