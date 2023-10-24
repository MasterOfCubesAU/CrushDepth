// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include <Components/TextBlock.h>
#include "Components/Button.h"
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
	int32 tier;
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

	TMap<FString, FString> GetDescriptions() {
		return Descriptions;
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

	UPROPERTY(meta = (BindWidget)) class UTextBlock* UpgradesTitle;
	UPROPERTY(meta = (BindWidget)) class UTextBlock* DescriptionText;

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
	TMap<FString, FString> Descriptions = {
		{"Health", "Increase submarine health by 2"},
		{"Speed", "Increase player speed"},
		{"TaskRate", "Decrease task spawn rate"},
		{"Money", "Increase money generation rate"},
		{"Submarine_descent", "Increase submarine descend speed"},
		{"Oxygen", "Decrease rate of oxygen depletion"},
		{"Max_Oxygen", "Increase max oxygen"}
	};
	TMap<FString, TArray<int32>> Costs = {
		{"Health", TArray<int32>{2, 4}},
		{"Speed", TArray<int32>{3, 5}},
		{"TaskRate", TArray<int32>{4, 6}}
	};

	FString CurrentHoveredButton;
	FString CurrentClickedButton;

	TArray<class UCheckBox*> HealthUpgradeTiers;
	TArray<class UCheckBox*> SpeedUpgradeTiers;
	TArray<class UCheckBox*> TaskRateUpgradeTiers;
};
