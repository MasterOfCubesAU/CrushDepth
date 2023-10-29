// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameStateBase.h"
#include "SubmarineStatesEnum.h"
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
	float BestSubmarineDepth;
	FTimerHandle DiveTimer;
	SubmarineStates CurrentSubmarineState;

	void DoDive();
	void StartDescent();
	void StartAscent();
	
	// Health
	float CurrentSubmarineHealth;
	float SubmarineStartHealth;

public:
	AGS_Core();

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
	float GetBestSubmarineDepth();

	UFUNCTION(BlueprintCallable, Category = "Submarine")
	SubmarineStates GetSubmarineState();

	UFUNCTION(BlueprintCallable, Category = "Submarine")
	bool ToggleDive();

	UFUNCTION(BlueprintCallable, Category = "Submarine")
	void SetAscentRate(float NewRate);

	UFUNCTION(BlueprintCallable, Category = "Submarine")
	void SetDescentRate(float NewRate);
	
};