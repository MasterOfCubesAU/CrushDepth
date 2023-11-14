// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Oxygen_System.generated.h"

/**
 * 
 */
UCLASS()
class CRUSHDEPTH_API UOxygen_System : public UObject
{
	GENERATED_BODY()
private:
	float CurrentOxygen;
	float MaxOxygen;
	float DepletionRate;

public:
	UOxygen_System();

	UFUNCTION(BlueprintCallable, Category = "Oxygen")
	float GetCurrentOxygen();
	UFUNCTION(BlueprintCallable, Category = "Oxygen")
	void SetCurrentOxygen(float Amount);

	UFUNCTION(BlueprintCallable, Category = "Oxygen")
	float GetMaxOxygen();
	UFUNCTION(BlueprintCallable, Category = "Oxygen")
	void SetMaxOxygen(float Amount);

	UFUNCTION(BlueprintCallable, Category = "Oxygen")
	float GetDepletionRate();
	UFUNCTION(BlueprintCallable, Category = "Oxygen")
	void SetDepletionRate(float Amount);

	UFUNCTION(BlueprintCallable, Category = "Oxygen")
	void ConsumeOxygen();

	// Events
	UFUNCTION(BlueprintImplementableEvent, Category = "Oxygen")
	void OnOxygenFinish();
};
