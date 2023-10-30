// Fill out your copyright notice in the Description page of Project Settings.


#include "ShopWidget.h"
#include <Components/Button.h>
#include <Components/TextBlock.h>
#include <Components/CheckBox.h>
#include "CrushDepth/GS_Core.h"
#include "CrushDepth/Public/GlobalVariablesLibrary.h"

void UShopWidget::NativeConstruct() {
	Super::NativeConstruct();

	HealthUpgradeButton->SetButtonName("Health");
	HealthUpgradeButton->SetShopWidgetInstance(this);
	HealthUpgradeTiers.Add(HealthUpgradeCheckbox1);
	HealthUpgradeTiers.Add(HealthUpgradeCheckbox2);

	SpeedUpgradeButton->SetButtonName("Speed");
	SpeedUpgradeButton->SetShopWidgetInstance(this);
	SpeedUpgradeTiers.Add(SpeedUpgradeCheckbox1);
	SpeedUpgradeTiers.Add(SpeedUpgradeCheckbox2);

	TaskRateUpgradeButton->SetButtonName("TaskRate");
	TaskRateUpgradeButton->SetShopWidgetInstance(this);
	TaskRateUpgradeTiers.Add(TaskRateUpgradeCheckbox1);
	TaskRateUpgradeTiers.Add(TaskRateUpgradeCheckbox2);

	MoneyUpgradeButton->SetButtonName("Money");
	MoneyUpgradeButton->SetShopWidgetInstance(this);
	MoneyUpgradeTiers.Add(MoneyUpgradeCheckbox1);
	MoneyUpgradeTiers.Add(MoneyUpgradeCheckbox2);

	SubmarineDescentUpgradeButton->SetButtonName("SubmarineDescent");
	SubmarineDescentUpgradeButton->SetShopWidgetInstance(this);
	SubmarineDescentUpgradeTiers.Add(SubmarineDescentUpgradeCheckbox1);
	SubmarineDescentUpgradeTiers.Add(SubmarineDescentUpgradeCheckbox2);

	// Initialise cost for Health Upgrade
	if (HealthUpgradeCost->GetText().ToString().IsEmpty()) {
		HealthUpgradeCost->SetText(FText::AsNumber(Costs["Health"][0]));
	}

	if (SpeedUpgradeCost->GetText().ToString().IsEmpty()) {
		SpeedUpgradeCost->SetText(FText::AsNumber(Costs["Speed"][0]));
	}

	if (TaskRateUpgradeCost->GetText().ToString().IsEmpty()) {
		TaskRateUpgradeCost->SetText(FText::AsNumber(Costs["TaskRate"][0]));
	}

	if (MoneyUpgradeCost->GetText().ToString().IsEmpty()) {
		MoneyUpgradeCost->SetText(FText::AsNumber(Costs["Money"][0]));
	}

	if (SubmarineDescentUpgradeCost->GetText().ToString().IsEmpty()) {
		SubmarineDescentUpgradeCost->SetText(FText::AsNumber(Costs["SubmarineDescent"][0]));
	}

	// Conditions for upgrade buttons 
	if (SpeedUpgradeButton) {
		SpeedUpgradeButton->OnHovered.AddDynamic(this, &UShopWidget::OnUpgradeButtonHovered);
		SpeedUpgradeButton->OnUnhovered.AddDynamic(this, &UShopWidget::OnUpgradeButtonUnhovered);

		SpeedUpgradeButton->OnClicked.AddDynamic(this, &UShopWidget::OnUpgradeButtonClicked);
	}

	if (HealthUpgradeButton) {
		HealthUpgradeButton->OnHovered.AddDynamic(this, &UShopWidget::OnUpgradeButtonHovered);
		HealthUpgradeButton->OnUnhovered.AddDynamic(this, &UShopWidget::OnUpgradeButtonUnhovered);

		HealthUpgradeButton->OnClicked.AddDynamic(this, &UShopWidget::OnUpgradeButtonClicked);
	}

	if (TaskRateUpgradeButton) {
		TaskRateUpgradeButton->OnHovered.AddDynamic(this, &UShopWidget::OnUpgradeButtonHovered);
		TaskRateUpgradeButton->OnUnhovered.AddDynamic(this, &UShopWidget::OnUpgradeButtonUnhovered);

		TaskRateUpgradeButton->OnClicked.AddDynamic(this, &UShopWidget::OnUpgradeButtonClicked);
	}

	if (MoneyUpgradeButton) {
		MoneyUpgradeButton->OnHovered.AddDynamic(this, &UShopWidget::OnUpgradeButtonHovered);
		MoneyUpgradeButton->OnUnhovered.AddDynamic(this, &UShopWidget::OnUpgradeButtonUnhovered);

		MoneyUpgradeButton->OnClicked.AddDynamic(this, &UShopWidget::OnUpgradeButtonClicked);
	}

	if (SubmarineDescentUpgradeButton) {
		SubmarineDescentUpgradeButton->OnHovered.AddDynamic(this, &UShopWidget::OnUpgradeButtonHovered);
		SubmarineDescentUpgradeButton->OnUnhovered.AddDynamic(this, &UShopWidget::OnUpgradeButtonUnhovered);

		SubmarineDescentUpgradeButton->OnClicked.AddDynamic(this, &UShopWidget::OnUpgradeButtonClicked);
	}

	if (BuyButton) {
		BuyButton->OnClicked.AddDynamic(this, &UShopWidget::OnBuyButtonClicked);
	}
	if (CancelButton) {
		CancelButton->OnClicked.AddDynamic(this, &UShopWidget::SetScreenNormal);
	}
}


void UShopWidget::OnUpgradeButtonHovered() {
	/*BuyButton->SetVisibility(ESlateVisibility::Hidden);
	BuyButtonText->SetVisibility(ESlateVisibility::Hidden);

	CancelButton->SetVisibility(ESlateVisibility::Hidden);
	CancelButtonText->SetVisibility(ESlateVisibility::Hidden);*/
}

void UShopWidget::OnUpgradeButtonUnhovered() {
	
	if (DescriptionText)
	{
		// Only set the visibility of the description to hidden if the user is not in buy selection
		FString text = DescriptionText->GetText().ToString();
		if (! text.StartsWith("Would you")) {
			DescriptionText->SetVisibility(ESlateVisibility::Hidden);
		}
	}
	UpgradeTitle->SetVisibility(ESlateVisibility::Hidden);
}


void UShopWidget::OnUpgradeButtonClicked() {
	UShopWidget::SetCurrentClickedButton(UShopWidget::GetCurrentHoveredButton());
	BuyButton->SetVisibility(ESlateVisibility::Visible);
	BuyButtonText->SetVisibility(ESlateVisibility::Visible);

	CancelButton->SetVisibility(ESlateVisibility::Visible);
	CancelButtonText->SetVisibility(ESlateVisibility::Visible);

	DescriptionText->SetText(FText::FromString("Would you like to buy this item?"));
	DescriptionText->SetVisibility(ESlateVisibility::Visible);
}


void UShopWidget::OnBuyButtonClicked() {
	AGS_Core* const GameState = GetWorld() != NULL ? GetWorld()->GetGameState<AGS_Core>() : NULL;

	if (UShopWidget::GetCurrentClickedButton() == "Health") {
		// If no more upgrade tiers, the buy button does nothing
		if (HealthUpgradeButton->GetTier() == Costs["Health"].Num()) return;

		// Tick the corresponding check box
		HealthUpgradeTiers[HealthUpgradeButton->GetTier()]->SetIsChecked(true);
		HealthUpgradeButton->UpgradeTier();

		// If there are no more tiers, set the text to MAX, otherwise change cost 
		if (HealthUpgradeButton->GetTier() == Costs["Health"].Num()) {
			HealthUpgradeCost->SetText(FText::FromString("MAX"));
		}
		else {
			HealthUpgradeCost->SetText(FText::AsNumber(Costs["Health"][HealthUpgradeButton->GetTier()]));
			float CurrentSubmarineHealth = GameState->GetSubmarineHealth();
			GameState->SetSubmarineHealth(CurrentSubmarineHealth + 200);
		}
		
	}
	else if (UShopWidget::GetCurrentClickedButton() == "Speed") {
		// If no more upgrade tiers, the buy button does nothing
		if (SpeedUpgradeButton->GetTier() == Costs["Speed"].Num()) return;

		SpeedUpgradeTiers[SpeedUpgradeButton->GetTier()]->SetIsChecked(true);
		SpeedUpgradeButton->UpgradeTier();
		if (SpeedUpgradeButton->GetTier() == Costs["Speed"].Num()) {
			SpeedUpgradeCost->SetText(FText::FromString("MAX"));
		}
		else {
			SpeedUpgradeCost->SetText(FText::AsNumber(Costs["Speed"][SpeedUpgradeButton->GetTier()]));
		}
	}
	else if (UShopWidget::GetCurrentClickedButton() == "TaskRate") {
		// If no more upgrade tiers, the buy button does nothing
		if (TaskRateUpgradeButton->GetTier() == Costs["TaskRate"].Num()) return;

		TaskRateUpgradeTiers[TaskRateUpgradeButton->GetTier()]->SetIsChecked(true);
		TaskRateUpgradeButton->UpgradeTier();
		if (TaskRateUpgradeButton->GetTier() == Costs["TaskRate"].Num()) {
			TaskRateUpgradeCost->SetText(FText::FromString("MAX"));
		}
		else {
			TaskRateUpgradeCost->SetText(FText::AsNumber(Costs["TaskRate"][TaskRateUpgradeButton->GetTier()]));
			float CurrentTaskRate = UGlobalVariablesLibrary::GetTaskSpawnRate();
			UGlobalVariablesLibrary::SetTaskSpawnRate(CurrentTaskRate + 1);
		}
	}
	else if (UShopWidget::GetCurrentClickedButton() == "Money") {
		// If no more upgrade tiers, the buy button does nothing
		if (MoneyUpgradeButton->GetTier() == Costs["Money"].Num()) return;

		MoneyUpgradeTiers[MoneyUpgradeButton->GetTier()]->SetIsChecked(true);
		MoneyUpgradeButton->UpgradeTier();
		if (MoneyUpgradeButton->GetTier() == Costs["Money"].Num()) {
			MoneyUpgradeCost->SetText(FText::FromString("MAX"));
		}
		else {
			MoneyUpgradeCost->SetText(FText::AsNumber(Costs["Money"][MoneyUpgradeButton->GetTier()]));
		}
	}
	else if (UShopWidget::GetCurrentClickedButton() == "SubmarineDescent") {
		// If no more upgrade tiers, the buy button does nothing
		if (SubmarineDescentUpgradeButton->GetTier() == Costs["SubmarineDescent"].Num()) return;

		SubmarineDescentUpgradeTiers[SubmarineDescentUpgradeButton->GetTier()]->SetIsChecked(true);
		SubmarineDescentUpgradeButton->UpgradeTier();
		if (SubmarineDescentUpgradeButton->GetTier() == Costs["SubmarineDescent"].Num()) {
			SubmarineDescentUpgradeCost->SetText(FText::FromString("MAX"));
		}
		else {
			SubmarineDescentUpgradeCost->SetText(FText::AsNumber(Costs["SubmarineDescent"][SubmarineDescentUpgradeButton->GetTier()]));
			float CurrentDescentRate = GameState->GetDescentRate();
			GameState->SetDescentRate(CurrentDescentRate * 1.5);
		}
	}
	UShopWidget::SetScreenNormal();
}

void UShopWidget::SetScreenNormal() {
	DescriptionText->SetVisibility(ESlateVisibility::Hidden);
	UpgradeTitle->SetVisibility(ESlateVisibility::Hidden);
	BuyButton->SetVisibility(ESlateVisibility::Hidden);
	BuyButtonText->SetVisibility(ESlateVisibility::Hidden);

	CancelButton->SetVisibility(ESlateVisibility::Hidden);
	CancelButtonText->SetVisibility(ESlateVisibility::Hidden);
}

UUpgradeButton::UUpgradeButton() {
	OnHovered.AddDynamic(this, &UUpgradeButton::OnGetName);

	hover.AddDynamic(this, &UUpgradeButton::OnHover);
}

void UUpgradeButton::OnGetName() {
	hover.Broadcast(this->GetButtonName());
}

void UUpgradeButton::OnHover(FString button_name) {
	FString description = ShopWidgetInstance->GetDescriptions()[button_name];
	FString upgrade_name = ShopWidgetInstance->GetTitles()[button_name];
	ShopWidgetInstance->SetDescriptionText(description);
	ShopWidgetInstance->SetUpgradeTitle(upgrade_name);
	ShopWidgetInstance->SetCurrentHoveredButton(button_name);
}