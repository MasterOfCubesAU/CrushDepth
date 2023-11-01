// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Wallet.generated.h"

/**
 * 
 */
UCLASS()
class CRUSHDEPTH_API UWallet : public UObject
{
	GENERATED_BODY()
	
private:
	float Balance;

public:
	UWallet();

	UFUNCTION(BlueprintCallable, Category="Wallet")
	float GetBalance();
	UFUNCTION(BlueprintCallable, Category = "Wallet")
	void SetBalance(float Amount);
	UFUNCTION(BlueprintCallable, Category = "Wallet")
	void SubtractBalance(float Amount);
	UFUNCTION(BlueprintCallable, Category = "Wallet")
	void AddBalance(float Amount);
};
