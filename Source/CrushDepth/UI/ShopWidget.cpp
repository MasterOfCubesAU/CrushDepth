// Fill out your copyright notice in the Description page of Project Settings.


#include "ShopWidget.h"
#include <Components/Button.h>
#include <Components/TextBlock.h>
#include <Components/CheckBox.h>
#include "CrushDepth/GS_Core.h"
#include "CrushDepth/Public/Wallet.h"
#include "CrushDepth/CD_PlayerState.h"
#include "CrushDepth/Public/GlobalVariablesLibrary.h"
#include "GameFramework/PlayerState.h"

UUpgradeButton::UUpgradeButton() {
	OnHovered.AddDynamic(this, &UUpgradeButton::OnGetName);
	hover.AddDynamic(this, &UUpgradeButton::OnHover);
}


void UShopWidget::NativeConstruct() {
	Super::NativeConstruct();

	AGS_Core* const GameState = GetWorld() != NULL ? GetWorld()->GetGameState<AGS_Core>() : NULL;

	HealthUpgradeButton->SetButtonName("Health");
	HealthUpgradeButton->SetShopWidgetInstance(this);
	HealthUpgradeTiers.Add(HealthUpgradeCheckbox1);
	HealthUpgradeTiers.Add(HealthUpgradeCheckbox2);
	for (auto i = 0; i < GameState->GetUpgradeTier("Health"); ++i) {
		HealthUpgradeTiers[i]->SetIsChecked(true);
	}

	SpeedUpgradeButton->SetButtonName("Speed");
	SpeedUpgradeButton->SetShopWidgetInstance(this);
	SpeedUpgradeTiers.Add(SpeedUpgradeCheckbox1);
	SpeedUpgradeTiers.Add(SpeedUpgradeCheckbox2);
	for (auto i = 0; i < GameState->GetUpgradeTier("Speed"); ++i) {
		SpeedUpgradeTiers[i]->SetIsChecked(true);
	}

	TaskRateUpgradeButton->SetButtonName("TaskRate");
	TaskRateUpgradeButton->SetShopWidgetInstance(this);
	TaskRateUpgradeTiers.Add(TaskRateUpgradeCheckbox1);
	TaskRateUpgradeTiers.Add(TaskRateUpgradeCheckbox2);
	for (auto i = 0; i < GameState->GetUpgradeTier("TaskRate"); ++i) {
		TaskRateUpgradeTiers[i]->SetIsChecked(true);
	}

	MoneyUpgradeButton->SetButtonName("Money");
	MoneyUpgradeButton->SetShopWidgetInstance(this);
	MoneyUpgradeTiers.Add(MoneyUpgradeCheckbox1);
	MoneyUpgradeTiers.Add(MoneyUpgradeCheckbox2);
	for (auto i = 0; i < GameState->GetUpgradeTier("Money"); ++i) {
		MoneyUpgradeTiers[i]->SetIsChecked(true);
	}

	SubmarineDescentUpgradeButton->SetButtonName("SubmarineDescent");
	SubmarineDescentUpgradeButton->SetShopWidgetInstance(this);
	SubmarineDescentUpgradeTiers.Add(SubmarineDescentUpgradeCheckbox1);
	SubmarineDescentUpgradeTiers.Add(SubmarineDescentUpgradeCheckbox2);
	for (auto i = 0; i < GameState->GetUpgradeTier("SubmarineDescent"); ++i) {
		SubmarineDescentUpgradeTiers[i]->SetIsChecked(true);
	}

	MaxOxygenUpgradeButton->SetButtonName("MaxOxygen");
	MaxOxygenUpgradeButton->SetShopWidgetInstance(this);
	MaxOxygenUpgradeTiers.Add(MaxOxygenUpgradeCheckbox1);
	MaxOxygenUpgradeTiers.Add(MaxOxygenUpgradeCheckbox2);
	for (auto i = 0; i < GameState->GetUpgradeTier("MaxOxygen"); ++i) {
		MaxOxygenUpgradeTiers[i]->SetIsChecked(true);
	}

	FString MoneyString = "$";
	int32 RoundMoney = FMath::FloorToInt((((ACD_PlayerState*)GetWorld()->GetFirstPlayerController()->PlayerState)->wallet->GetBalance()));
	MoneyText->SetText(FText::FromString(MoneyString + FString::FromInt(RoundMoney)));

	// Initialise cost for Health Upgrade
	if (GameState->GetUpgradeTier("Health") == Costs["Health"].Num()) {
		HealthUpgradeCost->SetText(FText::FromString("MAX"));
	} else {
		HealthUpgradeCost->SetText(FText::FromString(MoneyString + FString::FromInt(Costs["Health"][0])));
	}

	if (GameState->GetUpgradeTier("Speed") == Costs["Speed"].Num()) {
		SpeedUpgradeCost->SetText(FText::FromString("MAX"));
	} else {
		SpeedUpgradeCost->SetText(FText::FromString(MoneyString + FString::FromInt(Costs["Speed"][0])));
	}

	if (GameState->GetUpgradeTier("TaskRate") == Costs["TaskRate"].Num()) {
		TaskRateUpgradeCost->SetText(FText::FromString("MAX"));
	} else {
		TaskRateUpgradeCost->SetText(FText::FromString(MoneyString + FString::FromInt(Costs["TaskRate"][0])));
	}

	if (GameState->GetUpgradeTier("Money") == Costs["Money"].Num()) {
		MoneyUpgradeCost->SetText(FText::FromString("MAX"));
	} else {
		MoneyUpgradeCost->SetText(FText::FromString(MoneyString + FString::FromInt(Costs["Money"][0])));
	}

	if (GameState->GetUpgradeTier("SubmarineDescent") == Costs["SubmarineDescent"].Num()) {
		SubmarineDescentUpgradeCost->SetText(FText::FromString("MAX"));
	} else {
		SubmarineDescentUpgradeCost->SetText(FText::FromString(MoneyString + FString::FromInt(Costs["SubmarineDescent"][0])));
	}

	if (GameState->GetUpgradeTier("MaxOxygen") == Costs["MaxOxygen"].Num()) {
		MaxOxygenUpgradeCost->SetText(FText::FromString("MAX"));
	} else {
		MaxOxygenUpgradeCost->SetText(FText::FromString(MoneyString + FString::FromInt(Costs["MaxOxygen"][0])));
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

	if (MaxOxygenUpgradeButton) {
		MaxOxygenUpgradeButton->OnHovered.AddDynamic(this, &UShopWidget::OnUpgradeButtonHovered);
		MaxOxygenUpgradeButton->OnUnhovered.AddDynamic(this, &UShopWidget::OnUpgradeButtonUnhovered);

		MaxOxygenUpgradeButton->OnClicked.AddDynamic(this, &UShopWidget::OnUpgradeButtonClicked);
	}

	if (BuyButton) {
		BuyButton->OnClicked.AddDynamic(this, &UShopWidget::OnBuyButtonClicked);
	}
	if (CancelButton) {
		CancelButton->OnClicked.AddDynamic(this, &UShopWidget::SetScreenNormal);
	}
}


void UShopWidget::OnUpgradeButtonHovered() {
	BuyButton->SetVisibility(ESlateVisibility::Hidden);
	BuyButtonText->SetVisibility(ESlateVisibility::Hidden);

	CancelButton->SetVisibility(ESlateVisibility::Hidden);
	CancelButtonText->SetVisibility(ESlateVisibility::Hidden);
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

	DescriptionText->SetText(FText::FromString("Would you like to buy this item"));
	DescriptionText->SetVisibility(ESlateVisibility::Visible);
}


void UShopWidget::OnBuyButtonClicked() {
	AGS_Core* const GameState = GetWorld() != NULL ? GetWorld()->GetGameState<AGS_Core>() : NULL;
	float Money = ((ACD_PlayerState*)GetWorld()->GetFirstPlayerController()->PlayerState)->wallet->GetBalance();
	FString DollarSign = TEXT("$");
	int32 NewMoney;
	FString NewMoneyString;
	float CurrentCost;

	if (UShopWidget::GetCurrentClickedButton() == "Health") {
		// If no more upgrade tiers, the buy button does nothing
		if (GameState->GetUpgradeTier("Health") == Costs["Health"].Num()) return;

		// If not enough money, buy button does nothing
		CurrentCost = Costs["Health"][GameState->GetUpgradeTier("Health")];
		if (CurrentCost > Money) return;
		
		// Tick the corresponding check box
		HealthUpgradeTiers[GameState->GetUpgradeTier("Health")]->SetIsChecked(true);
		GameState->SetUpgradeTier("Health", GameState->GetUpgradeTier("Health") + 1);

		FString tier = FString::FromInt(GameState->GetUpgradeTier("Health"));
		FString num = FString::FromInt(Costs["Health"].Num());

		GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, (TEXT("%s = StringVariable"), tier));
			
		// If there are no more tiers, set the text to MAX, otherwise change cost 
		if (GameState->GetUpgradeTier("Health") == Costs["Health"].Num()) {
			HealthUpgradeCost->SetText(FText::FromString("MAX"));
		}
		// Get current money and set new money to be current money - upgrade cost
		else {
			HealthUpgradeCost->SetText(FText::FromString(DollarSign + FString::FromInt(Costs["Health"][GameState->GetUpgradeTier("Health")])));
		}

		float CurrentSubmarineStartHealth = GameState->GetSubmarineStartHealth();
		float NewHealth = CurrentSubmarineStartHealth * 1.2;
		GameState->SetSubmarineStartHealth(NewHealth);
		GameState->SetSubmarineHealth(NewHealth);
		NewMoney = Money - CurrentCost;
		NewMoneyString = FString::FromInt(FMath::FloorToInt(Money - CurrentCost));
	}
	else if (UShopWidget::GetCurrentClickedButton() == "Speed") {
		if (GameState->GetUpgradeTier("Speed") == Costs["Speed"].Num()) return;

		CurrentCost = Costs["Speed"][GameState->GetUpgradeTier("Speed")];
		if (CurrentCost > Money) return;

		SpeedUpgradeTiers[GameState->GetUpgradeTier("Speed")]->SetIsChecked(true);
		GameState->SetUpgradeTier("Speed", GameState->GetUpgradeTier("Speed") + 1);

		if (GameState->GetUpgradeTier("Speed") == Costs["Speed"].Num()) {
			SpeedUpgradeCost->SetText(FText::FromString("MAX"));
		} else {
			SpeedUpgradeCost->SetText(FText::FromString(DollarSign + FString::FromInt(Costs["Speed"][GameState->GetUpgradeTier("Speed")])));
		}
		ACD_PlayerState* const PlayerState = ((ACD_PlayerState*)GetWorld()->GetFirstPlayerController()->PlayerState);
		PlayerState->SetPlayerSpeed(PlayerState->GetPlayerSpeed() * 1.1);

		NewMoney = Money - CurrentCost;
		NewMoneyString = FString::FromInt(FMath::FloorToInt(Money - CurrentCost));
	}
	else if (UShopWidget::GetCurrentClickedButton() == "TaskRate") {
		if (GameState->GetUpgradeTier("TaskRate") == Costs["TaskRate"].Num()) return;

		CurrentCost = Costs["TaskRate"][GameState->GetUpgradeTier("TaskRate")];
		if (CurrentCost > Money) return;

		TaskRateUpgradeTiers[GameState->GetUpgradeTier("TaskRate")]->SetIsChecked(true);
		GameState->SetUpgradeTier("TaskRate", GameState->GetUpgradeTier("TaskRate") + 1);

		if (GameState->GetUpgradeTier("TaskRate") == Costs["TaskRate"].Num()) {
			TaskRateUpgradeCost->SetText(FText::FromString("MAX"));
		} else {
			TaskRateUpgradeCost->SetText(FText::FromString(DollarSign + FString::FromInt(Costs["TaskRate"][GameState->GetUpgradeTier("TaskRate")])));
		}
		float CurrentTaskRate = GameState->GetTaskRate();
		GameState->SetTaskRate(CurrentTaskRate * 1.1);

		NewMoney = Money - CurrentCost;
		NewMoneyString = FString::FromInt(FMath::FloorToInt(Money - CurrentCost));
	}
	else if (UShopWidget::GetCurrentClickedButton() == "Money") {
		if (GameState->GetUpgradeTier("Money") == Costs["Money"].Num()) return;

		CurrentCost = Costs["Money"][GameState->GetUpgradeTier("Money")];
		if (CurrentCost > Money) return;

		MoneyUpgradeTiers[GameState->GetUpgradeTier("Money")]->SetIsChecked(true);
		GameState->SetUpgradeTier("Money", GameState->GetUpgradeTier("Money") + 1);

		if (GameState->GetUpgradeTier("Money") == Costs["Money"].Num()) {
			MoneyUpgradeCost->SetText(FText::FromString("MAX"));
		} else {
			MoneyUpgradeCost->SetText(FText::FromString(DollarSign + FString::FromInt(Costs["Money"][GameState->GetUpgradeTier("Money")])));
		}

		float CurrentMoneyRate = GameState->GetMoneyRate();
		GameState->SetMoneyRate(CurrentMoneyRate * 1.1);
		NewMoney = Money - CurrentCost;
		NewMoneyString = FString::FromInt(FMath::FloorToInt(Money - CurrentCost));
	}
	else if (UShopWidget::GetCurrentClickedButton() == "SubmarineDescent") {
		if (GameState->GetUpgradeTier("SubmarineDescent") == Costs["SubmarineDescent"].Num()) return;

		CurrentCost = Costs["SubmarineDescent"][GameState->GetUpgradeTier("SubmarineDescent")];
		if (CurrentCost > Money) return;

		SubmarineDescentUpgradeTiers[GameState->GetUpgradeTier("SubmarineDescent")]->SetIsChecked(true);
		GameState->SetUpgradeTier("SubmarineDescent", GameState->GetUpgradeTier("SubmarineDescent") + 1);

		if (GameState->GetUpgradeTier("SubmarineDescent") == Costs["SubmarineDescent"].Num()) {
			SubmarineDescentUpgradeCost->SetText(FText::FromString("MAX"));
		} else {
			SubmarineDescentUpgradeCost->SetText(FText::FromString(DollarSign + FString::FromInt(Costs["SubmarineDescent"][GameState->GetUpgradeTier("SubmarineDescent")])));
		}

		float CurrentDescentRate = GameState->GetDescentRate();
		GameState->SetDescentRate(CurrentDescentRate * 1.2);
		NewMoney = Money - CurrentCost;
		NewMoneyString = FString::FromInt(FMath::FloorToInt(Money - CurrentCost));
	}
	else if (UShopWidget::GetCurrentClickedButton() == "MaxOxygen") {
		if (GameState->GetUpgradeTier("MaxOxygen") == Costs["MaxOxygen"].Num()) return;

		CurrentCost = Costs["MaxOxygen"][GameState->GetUpgradeTier("MaxOxygen")];
		if (CurrentCost > Money) return;

		MaxOxygenUpgradeTiers[GameState->GetUpgradeTier("MaxOxygen")]->SetIsChecked(true);
		GameState->SetUpgradeTier("MaxOxygen", GameState->GetUpgradeTier("MaxOxygen") + 1);

		if (GameState->GetUpgradeTier("MaxOxygen") == Costs["MaxOxygen"].Num()) {
			MaxOxygenUpgradeCost->SetText(FText::FromString("MAX"));
		} else {
			MaxOxygenUpgradeCost->SetText(FText::FromString(DollarSign + FString::FromInt(Costs["MaxOxygen"][GameState->GetUpgradeTier("MaxOxygen")])));
		}

		float CurrentMaxOxygen = GameState->GetMaxOxygen();
		float NewOxygen = CurrentMaxOxygen * 2;
		GameState->SetMaxOxygen(NewOxygen);
		GameState->SetCurrentOxygen(NewOxygen);
		NewMoney = Money - CurrentCost;
		NewMoneyString = FString::FromInt(FMath::FloorToInt(Money - CurrentCost));
	}

	MoneyText->SetText(FText::FromString(DollarSign + NewMoneyString));
	((ACD_PlayerState*)GetWorld()->GetFirstPlayerController()->PlayerState)->wallet->SetBalance(NewMoney);
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