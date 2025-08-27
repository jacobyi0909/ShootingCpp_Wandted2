// Fill out your copyright notice in the Description page of Project Settings.


#include "MainWidget.h"

#include "PlayerHPWidget.h"
#include "Components/TextBlock.h"

void UMainWidget::UpdateTextScore(int32 HighScore, int32 Score)
{
	TextHighScore->SetText(FText::AsNumber(HighScore));
	TextScore->SetText(FText::AsNumber(Score));
}

void UMainWidget::UpdateHPWidget(const float& curHP, const float& maxHP)
{
	PlayerHP->UpdateHPWidget(curHP, maxHP);
}
