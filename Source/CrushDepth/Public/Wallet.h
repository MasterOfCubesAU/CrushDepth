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
	float GetBalance();
	void SetBalance(float Amount);
	void SubtractBalance(float Amount);
	void AddBalance(float Amount);
};
