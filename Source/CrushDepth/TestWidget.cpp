// Fill out your copyright notice in the Description page of Project Settings.


#include "TestWidget.h"
#include <Components/Button.h>
#include <Components/TextBlock.h>

void UTestWidget::NativeConstruct() {
	Super::NativeConstruct();

	GenerateRandom();

	GenerateButton->OnClicked.AddUniqueDynamic(this, &UTestWidget::OnGenerateButtonClicked);
}

void UTestWidget::GenerateRandom() {
	int32 RandomNumber = FMath::RandRange(0, 100);
	RandomNumberLabel->SetText(FText::AsNumber(RandomNumber));
}

void UTestWidget::OnGenerateButtonClicked() {
	GenerateRandom();
}