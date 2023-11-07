// Fill out your copyright notice in the Description page of Project Settings.


#include "CD_PlayerState.h"

ACD_PlayerState::ACD_PlayerState(){
	this->state = PlayerStates::Normal;
	this->wallet = NewObject<UWallet>(UWallet::StaticClass());
	this->PlayerSpeed = 500;
}

PlayerStates ACD_PlayerState::GetPlayerState() {
	return this->state;
}

void ACD_PlayerState::SetPlayerState(PlayerStates NewState) {
	this->state = NewState;
}

float ACD_PlayerState::GetPlayerSpeed() {
	return this->PlayerSpeed;
}

void ACD_PlayerState::SetPlayerSpeed(float NewSpeed) {
	this->PlayerSpeed = NewSpeed;
}
