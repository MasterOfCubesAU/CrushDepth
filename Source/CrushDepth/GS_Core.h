// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameStateBase.h"
#include "SubmarineStatesEnum.h"
#include "CD_PlayerState.h"
#include "Kismet/GameplayStatics.h"
#include "Public/PA_System.h"
#include "Public/Oxygen_System.h"
#include "GS_Core.generated.h"

/**
 * 
 */
UCLASS(config=GlobalVariables)
class CRUSHDEPTH_API AGS_Core : public AGameStateBase
{
	GENERATED_BODY()

private:
	// Depth
	float AscentRate;
	float DescentRate;
	float CurrentSubmarineDepth;
	float CurrentBestAttempt;
	float MoneyRate;
	FTimerHandle DiveTimer;
	SubmarineStates CurrentSubmarineState;

	void DoDive();
	void StartDescent();
	void StartAscent();
	
	// Health
	float CurrentSubmarineHealth;
	float SubmarineStartHealth;

	// Shop 
	TMap<FString, int32> UpgradeTiers = {
		{"Health", 0},
		{"Speed", 0},
		{"TaskRate", 0},
		{"Money", 0},
		{"SubmarineDescent", 0},
	};

	// Tasks
	float TaskRate;

public:
	AGS_Core();

	// Oxygen
	UPROPERTY(BlueprintReadWrite)
	UOxygen_System* oxygen;

	// Submarine Health
	UFUNCTION(BlueprintCallable, Category = "Submarine")
	float GetSubmarineHealth();
	UFUNCTION(BlueprintCallable, Category = "Submarine")
	void SetSubmarineHealth(float NewHealth);
	UFUNCTION(BlueprintCallable, Category = "Submarine")
	void SubtractSubmarineHealth(float Amount);


	// Submarine Depth
	UFUNCTION(BlueprintCallable, Category = "Submarine")
	float GetSubmarineDepth();

	UFUNCTION(BlueprintCallable, Category = "Submarine")
	float GetCurrentBestAttempt();

	UFUNCTION(BlueprintCallable, Category = "Submarine")
	float GetBestAttempt();

	UFUNCTION(BlueprintCallable, Category = "Submarine")
	SubmarineStates GetSubmarineState();

	UFUNCTION(BlueprintCallable, Category = "Submarine")
	bool ToggleDive();

	UFUNCTION(BlueprintCallable, Category = "Submarine")
	void SetAscentRate(float NewRate);

	UFUNCTION(BlueprintCallable, Category = "Submarine")
	float GetAscentRate();

	UFUNCTION(BlueprintCallable, Category = "Submarine")
	void SetDescentRate(float NewRate);

	UFUNCTION(BlueprintCallable, Category = "Submarine")
	float GetDescentRate();
	
	UFUNCTION(BlueprintCallable, Category = "Submarine")
	void OnGameOver();

	UFUNCTION(BlueprintCallable, Category = "Submarine")
	float GetMoneyRate();

	UFUNCTION(BlueprintCallable, Category = "Submarine")
	void SetMoneyRate(float NewRate);

	// Shop
	UFUNCTION(BlueprintCallable, Category = "Shop")
	int32 GetUpgradeTier(FString UpgradeType);

	UFUNCTION(BlueprintCallable, Category = "Shop")
	void SetUpgradeTier(FString UpgradeType, int32 Tier);

	// Tasks
	UFUNCTION(BlueprintCallable, Category = "Tasks")
	float GetTaskRate();

	UFUNCTION(BlueprintCallable, Category = "Tasks")
	void SetTaskRate(float NewRate);
	// Events
	UFUNCTION(BlueprintImplementableEvent)
	void OnSurface();


	UFUNCTION(BlueprintImplementableEvent)
	void OnStartDive();

	UFUNCTION(BlueprintImplementableEvent)
	void OnStartAscent();

	
};