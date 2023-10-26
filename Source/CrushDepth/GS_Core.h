// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameStateBase.h"
#include "GS_Core.generated.h"

/**
 * 
 */
UCLASS(Config=GlobalVariables)
class CRUSHDEPTH_API AGS_Core : public AGameStateBase
{
	GENERATED_BODY()
	

public:
	AGS_Core();

	float SubmarineStartHealth;

	float CurrentSubmarineHealth = SubmarineStartHealth;

	UFUNCTION(BlueprintCallable, Category="Submarine")
	float GetSubmarineHealth();
	UFUNCTION(BlueprintCallable, Category = "Submarine")
	void SetSubmarineHealth(float NewHealth);
	UFUNCTION(BlueprintCallable, Category = "Submarine")
	void SubtractSubmarineHealth(float Amount);
};
