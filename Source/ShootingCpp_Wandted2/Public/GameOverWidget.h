// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "GameOverWidget.generated.h"

/**
 * 
 */
UCLASS()
class SHOOTINGCPP_WANDTED2_API UGameOverWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	// 태어날 때 버튼에 기능을 연결하고싶다.
	virtual void NativeConstruct() override;
	
	UPROPERTY(meta=(BindWidget))
	class UButton* ButtonQuit;

	UPROPERTY(meta=(BindWidget))
	class UButton* ButtonRestart;

	UFUNCTION()
	void OnMyClickButtonQuit();

	UFUNCTION()
	void OnMyClickButtonRestart();

};
