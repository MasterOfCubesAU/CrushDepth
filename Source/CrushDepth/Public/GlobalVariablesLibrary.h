// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "GlobalVariablesLibrary.generated.h"

/**
 * 
 */
UCLASS()
class CRUSHDEPTH_API UGlobalVariablesLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
	
public:

	// ALL SUBMARINE VARIABLES
	UFUNCTION(BlueprintCallable, Category = "GlobalVariables")
	static float GetSubmarineStartHealth();

	UFUNCTION(BlueprintCallable, Category = "GlobalVariables")
	static void SetSubmarineStartHealth(float SubmarineStartHealth);

	UFUNCTION(BlueprintCallable, Category = "GlobalVariables")
	static float GetCurrentSubmarineHealth();

	UFUNCTION(BlueprintCallable, Category = "GlobalVariables")
	static void SetCurrentSubmarineHealth(float SubmarineHealth);

	UFUNCTION(BlueprintCallable, Category = "GlobalVariables")
	static float GetSubmarineDescentRate();

	UFUNCTION(BlueprintCallable, Category = "GlobalVariables")
	static void SetSubmarineDescentRate(float SubmarineDescentRate);

	// ALL PLAYER VARIABLES
	UFUNCTION(BlueprintCallable, Category = "GlobalVariables")
	static float GetPlayerMoney();

	UFUNCTION(BlueprintCallable, Category = "GlobalVariables")
	static void SetPlayerMoney(float Money);

	UFUNCTION(BlueprintCallable, Category = "GlobalVariables")
	static float GetPlayerSpeed();

	UFUNCTION(BlueprintCallable, Category = "GlobalVariables")
	static void SetPlayerSpeed(float Speed);

	UFUNCTION(BlueprintCallable, Category = "GlobalVariables")
	static float GetMoneyGenerationRate();

	UFUNCTION(BlueprintCallable, Category = "GlobalVariables")
	static void SetMoneyGenerationRate(float MoneyGenerationRate);

	// ALL ENVIRONMENT VARIABLES
	UFUNCTION(BlueprintCallable, Category = "GlobalVariables")
	static float GetTaskSpawnRate();

	UFUNCTION(BlueprintCallable, Category = "GlobalVariables")
	static void SetTaskSpawnRate(float TaskSpawnRate);

	UFUNCTION(BlueprintCallable, Category = "GlobalVariables")
	static float GetMaxOxygen();

	UFUNCTION(BlueprintCallable, Category = "GlobalVariables")
	static void SetMaxOxygen(float MaxOxygen);

	UFUNCTION(BlueprintCallable, Category = "GlobalVariables")
	static float GetOxygenDepletionRate();

	UFUNCTION(BlueprintCallable, Category = "GlobalVariables")
	static void SetOxygenDepletionRate(float OxygenDepletionRate);
};
