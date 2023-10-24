// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameStateBase.h"
#include "GS_Core.generated.h"

/**
 * 
 */
UCLASS()
class CRUSHDEPTH_API AGS_Core : public AGameStateBase
{
	GENERATED_BODY()
	

public:
	static constexpr float SubmarineStartHealth = 100.f;
	static inline float CurrentSubmarineHealth = SubmarineStartHealth;

	AGS_Core() = default;

	UFUNCTION(BlueprintCallable, Category="Submarine")
	static float GetSubmarineHealth();
	UFUNCTION(BlueprintCallable, Category = "Submarine")
	static void SetSubmarineHealth(float NewHealth);
	UFUNCTION(BlueprintCallable, Category = "Submarine")
	static void SubtractSubmarineHealth(float Amount);
};
