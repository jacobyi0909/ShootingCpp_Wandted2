// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerHPWidget.h"

#include "Components/ProgressBar.h"
#include "Components/TextBlock.h"

void UPlayerHPWidget::UpdateHPWidget(const float& curHP, const float& maxHP)
{
	float per = curHP / maxHP;

	HPBar->SetPercent(per);
	FString t =
		FString::Printf(TEXT("%d%%"), static_cast<int32>(per*100));
	TextHP->SetText(FText::FromString(t));
}
