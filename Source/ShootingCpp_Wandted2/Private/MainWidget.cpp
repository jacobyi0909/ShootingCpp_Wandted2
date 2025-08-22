// Fill out your copyright notice in the Description page of Project Settings.


#include "MainWidget.h"

#include "Components/TextBlock.h"

void UMainWidget::UpdateTextScore(int32 Score)
{
	TextScore->SetText(FText::AsNumber(Score));
}
