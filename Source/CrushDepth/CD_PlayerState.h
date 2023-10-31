// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerState.h"
#include "PlayerStatesEnum.h"
#include "Public/Wallet.h"
#include "CD_PlayerState.generated.h"

/**
 * 
 */

UCLASS()
class CRUSHDEPTH_API ACD_PlayerState : public APlayerState
{
	GENERATED_BODY()

public:
	ACD_PlayerState();
	UFUNCTION(BlueprintCallable)
	PlayerStates GetPlayerState();
	UFUNCTION(BlueprintCallable)
	void SetPlayerState(PlayerStates NewState);
	UPROPERTY(BlueprintReadWrite)
	UWallet* wallet;

private:
	PlayerStates state;
	
};
