// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyHpUI.h"

#include "Components/ProgressBar.h"

void UEnemyHpUI::NativeConstruct()
{
	Super::NativeConstruct();
	// 태어날 때 체력정보를 100%로 하고싶다.
	HPBarBG->SetPercent(1.f);
	HPBar->SetPercent(1.f);
}

void UEnemyHpUI::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);
	// 살아가면서 HPBarBG의 값을 HPBar에 수렴하고싶다.
	float newPer = FMath::Lerp(HPBarBG->GetPercent(),HPBar->GetPercent(),  InDeltaTime * 5); 
	
	HPBarBG->SetPercent(newPer);
}

void UEnemyHpUI::UpdateHPWidget(const float& curHP, const float& maxHP)
{
	float per = curHP / maxHP;
	HPBar->SetPercent(per);
}
