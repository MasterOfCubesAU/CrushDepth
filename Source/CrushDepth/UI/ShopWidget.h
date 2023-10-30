// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include <Components/TextBlock.h>
#include "Components/Button.h"
#include "../Public/GlobalVariablesLibrary.h"

#include "ShopWidget.generated.h"


DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FHoverDelegate, FString, name);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FGetNameDelegate);

// Upgrade Button class 
UCLASS()
class CRUSHDEPTH_API UUpgradeButton : public UButton {
	GENERATED_BODY()

public:
	UUpgradeButton();

	UPROPERTY()
	FHoverDelegate hover;

	UPROPERTY()
	FGetNameDelegate getName;

	UFUNCTION()
	void OnGetName();

	UFUNCTION()
	void OnHover(FString name);

	int32 GetTier() const {
		return tier;
	}
	void UpgradeTier() {
		++tier;
	}
	void SetButtonName(FString NewName) { 
		ButtonName = NewName; 
	}
	FString GetButtonName() const { 
		return ButtonName; 
	}

	void SetShopWidgetInstance(UShopWidget *instance) {
		ShopWidgetInstance = instance;
	}

private:
	int32 tier = 0;
	FString ButtonName;
	UShopWidget* ShopWidgetInstance;
};

// ShopWidget Class
UCLASS()
class CRUSHDEPTH_API UShopWidget : public UUserWidget
{

	GENERATED_BODY()

public:
	void SetDescriptionText(FString description) {
		DescriptionText->SetText(FText::FromString(description));
		DescriptionText->SetVisibility(ESlateVisibility::Visible);
	}

	void SetUpgradeTitle(FString title) {
		UpgradeTitle->SetText(FText::FromString(title));
		UpgradeTitle->SetVisibility(ESlateVisibility::Visible);
	}

	TMap<FString, FString> GetDescriptions() {
		return Descriptions;
	};

	TMap<FString, FString> GetTitles() {
		return UpgradeTitles;
	};

	TMap<FString, TArray<int32>> getCosts() {
		return Costs;
	};

	void SetCurrentHoveredButton(FString ButtonName) {
		CurrentHoveredButton = ButtonName;
	}

	FString GetCurrentHoveredButton() { return CurrentHoveredButton; }

	void SetCurrentClickedButton(FString ButtonName) {
		CurrentClickedButton = ButtonName;
	}

	FString GetCurrentClickedButton() { return CurrentClickedButton; }

protected:

	// Text variables
	UPROPERTY(meta = (BindWidget)) class UTextBlock* WidgetTitle;
	UPROPERTY(meta = (BindWidget)) class UTextBlock* DescriptionText;
	UPROPERTY(meta = (BindWidget)) class UTextBlock* UpgradeTitle;

	// ALL HEALTH UPGRADE PROPERTIES
	UPROPERTY(meta = (BindWidget)) class UUpgradeButton* HealthUpgradeButton;
	UPROPERTY(meta = (BindWidget)) class UTextBlock* HealthUpgradeCost;
	UPROPERTY(meta = (BindWidget)) class UCheckBox* HealthUpgradeCheckbox1;
	UPROPERTY(meta = (BindWidget)) class UCheckBox* HealthUpgradeCheckbox2;

	// ALL SPEED UPGRADE PROPERTIES
	UPROPERTY(meta = (BindWidget)) class UUpgradeButton* SpeedUpgradeButton;
	UPROPERTY(meta = (BindWidget)) class UTextBlock* SpeedUpgradeCost;
	UPROPERTY(meta = (BindWidget)) class UCheckBox* SpeedUpgradeCheckbox1;
	UPROPERTY(meta = (BindWidget)) class UCheckBox* SpeedUpgradeCheckbox2;

	// ALL DECREASE TASK RATE UPGRADE PROPERTIES
	UPROPERTY(meta = (BindWidget)) class UUpgradeButton* TaskRateUpgradeButton;
	UPROPERTY(meta = (BindWidget)) class UTextBlock* TaskRateUpgradeCost;
	UPROPERTY(meta = (BindWidget)) class UCheckBox* TaskRateUpgradeCheckbox1;
	UPROPERTY(meta = (BindWidget)) class UCheckBox* TaskRateUpgradeCheckbox2;

	// ALL DECREASE MONEY UPGRADE PROPERTIES
	UPROPERTY(meta = (BindWidget)) class UUpgradeButton* MoneyUpgradeButton;
	UPROPERTY(meta = (BindWidget)) class UTextBlock* MoneyUpgradeCost;
	UPROPERTY(meta = (BindWidget)) class UCheckBox* MoneyUpgradeCheckbox1;
	UPROPERTY(meta = (BindWidget)) class UCheckBox* MoneyUpgradeCheckbox2;

	// ALL DECREASE SUBMARINE DESCENT UPGRADE PROPERTIES
	UPROPERTY(meta = (BindWidget)) class UUpgradeButton* SubmarineDescentUpgradeButton;
	UPROPERTY(meta = (BindWidget)) class UTextBlock* SubmarineDescentUpgradeCost;
	UPROPERTY(meta = (BindWidget)) class UCheckBox* SubmarineDescentUpgradeCheckbox1;
	UPROPERTY(meta = (BindWidget)) class UCheckBox* SubmarineDescentUpgradeCheckbox2;

	// Buy and Cancel Button Components 
	UPROPERTY(meta = (BindWidget))
		class UButton* BuyButton;
	UPROPERTY(meta = (BindWidget))
		class UTextBlock* BuyButtonText;
	UPROPERTY(meta = (BindWidget))
		class UButton* CancelButton;
	UPROPERTY(meta = (BindWidget))
		class UTextBlock* CancelButtonText;

	UFUNCTION()
		void OnUpgradeButtonHovered();
	UFUNCTION()
		void OnUpgradeButtonUnhovered();
	UFUNCTION()
		void OnUpgradeButtonClicked();
	UFUNCTION()
		void OnBuyButtonClicked();
	UFUNCTION()
		void SetScreenNormal();
	

	void NativeConstruct() override;

private:
	TMap<FString, FString> UpgradeTitles = {
		{"Health", "Submarine Durability"},
		{"Speed", "Agility"},
		{"TaskRate", "Reliability"},
		{"Money", "Credits Increase"},
		{"SubmarineDescent", "Submarine Descent"},
		{"OxygenEffectiveness", "Oxygen Tank Effectiveness"},
		{"MaxOxygen", "Max Oxygen Supply"}
	};
	TMap<FString, FString> Descriptions = {
		{"Health", "Increase the durability of the submarine."},
		{"Speed", "Increase your manoeuvrability within the submarine "},
		{"TaskRate", "Decrease task spawn rate"},
		{"Money", "Increase money generation rate"},
		{"SubmarineDescent", "Increase submarine descend speed"},
		{"Oxygen", "Decrease rate of oxygen depletion"},
		{"MaxOxygen", "Increase max oxygen"}
	};
	TMap<FString, TArray<int32>> Costs = {
		{"Health", TArray<int32>{2, 4}},
		{"Speed", TArray<int32>{3, 5}},
		{"TaskRate", TArray<int32>{4, 6}},
		{"Money", TArray<int32>{4, 6}},
		{"SubmarineDescent", TArray<int32>{4, 6}},
		{"OxygenEffectivness", TArray<int32>{4, 6}},
		{"MaxOxygen", TArray<int32>{4, 6}}
	};

	FString CurrentHoveredButton;
	FString CurrentClickedButton;

	TArray<class UCheckBox*> HealthUpgradeTiers;
	TArray<class UCheckBox*> SpeedUpgradeTiers;
	TArray<class UCheckBox*> TaskRateUpgradeTiers;
	TArray<class UCheckBox*> MoneyUpgradeTiers;
	TArray<class UCheckBox*> SubmarineDescentUpgradeTiers;
};